#include "j1App.h"
#include "j1Textures.h"
#include "j1Render.h"
#include "j1Player.h"
#include "j1Particles.h"
#include "j1Audio.h"
#include "SDL/include/SDL_timer.h"
#include <math.h>

j1Particles::j1Particles()
{
	name.create("particles");

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
		active[i] = nullptr;

	// Projectile
	Projectile.anim.PushBack({ 0,0,16,16 }, 0.15, 0, 0);
	Projectile.anim.PushBack({ 17,0,16,16 }, 0.15, 0, 0);
	Projectile.anim.PushBack({ 34,0,16,16 }, 0.15, 0, 0);
	Projectile.anim.PushBack({ 51,0,16,16 }, 0.15, 0, 0);
	Projectile.life = 800;

	// Projectile flip
	Projectile_flip.anim.PushBack({ 0,0,16,16 }, 0.15, 0, 0);
	Projectile_flip.anim.PushBack({ 51,0,16,16 }, 0.15, 0, 0);
	Projectile_flip.anim.PushBack({ 34,0,16,16 }, 0.15, 0, 0);
	Projectile_flip.anim.PushBack({ 17,0,16,16 }, 0.15, 0, 0);
	Projectile_flip.life = 800;

	// Projectile explosion
	Projectile_explosion.anim.PushBack({ 0,17,18,17 }, 0.2, 0, 0);
	Projectile_explosion.anim.PushBack({ 19,17,20,19 }, 0.2, 0, 0);
	Projectile_explosion.anim.PushBack({ 40,17,23,21 }, 0.2, 0, 0);
	Projectile_explosion.anim.PushBack({ 64,17,25,24 }, 0.2, 0, 0);
	Projectile_explosion.anim.loop = false;
	Projectile_explosion.life = 300;

	// Jump particle
	jump_particle.anim.PushBack({ 0,41,38,10 }, 0.2, 0, 0);
	jump_particle.anim.PushBack({ 44,41,42,10 }, 0.2, 0, 0);
	jump_particle.anim.PushBack({ 92,41,46,6 }, 0.2, 0, 0);
	jump_particle.anim.PushBack({ 144,41,46,4 }, 0.2, 0, 0);
	jump_particle.anim.loop = false;
	jump_particle.life = 200;
}

j1Particles::~j1Particles()
{}

bool j1Particles::Awake(pugi::xml_node& config)
{
	// Player spritesheet
	spritesheet_projectiles = config.child("spritesheet").attribute("projectiles").as_string("");

	return true;
}

bool j1Particles::Start()
{
	LOG("Loading particles");

	// Load spritesheet
	graphics = App->tex->Load(spritesheet_projectiles.GetString());
	

	return true;
}

// Unload assets
bool j1Particles::CleanUp()
{
	LOG("Unloading particles");
	
	App->tex->UnLoad(graphics);

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] != nullptr)
		{
			delete active[i];
			active[i] = nullptr;
		}
	}

	return true;
}

bool j1Particles::Update(float dt)
{
	BROFILER_CATEGORY("UpdateParticles", Profiler::Color::PaleVioletRed)

	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		Particle* p = active[i];

		if (p == nullptr)
			continue;

		if (p->Update() == false || hitobject == true)
		{
			hitobject = false;
			delete p;
			active[i] = nullptr;

			hitobject = false;
			if (explosion == true && isjumping == false)
			{
				App->audio->PlayFx(4, 0);
				
				if (explosion_solid == true)
				{
					App->particles->Projectile_explosion.speed.x = 0;
					explosion_solid = false;
				}
				else
				{
					if (explosion_right == true)
					{
						App->particles->Projectile_explosion.speed.x = (6 * dt * 60);
					}
					else
					{
						App->particles->Projectile_explosion.speed.x = -(6 * dt * 60);
					}
				}

				AddParticle(Projectile_explosion, p->position.x, p->position.y, NO_COLLIDER);
				explosion = false;
			}
		}
		else if (SDL_GetTicks() >= p->born)
		{
			App->render->Blit(graphics, p->position.x, p->position.y, &(p->anim.GetCurrentFrame(dt)));

			if (p->fx_played == false)
			{
				p->fx_played = true;
				//App->audio->PlayFx(p->fx);
			}
		}
	}

	return true;
}

void j1Particles::AddParticle(const Particle& particle, int x, int y, COLLIDER_TYPE collider_type, Uint32 delay,float dt)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		if (active[i] == nullptr)
		{
			Particle* p = new Particle(particle);
			p->born = SDL_GetTicks() + delay;
			p->position.x = x;
			p->position.y = y;
			if (collider_type != COLLIDER_NONE)
				p->collider = App->colliders->AddCollider(p->anim.GetCurrentFrame(dt), collider_type, this);
			active[i] = p;
			break;
		}
	}
}

void j1Particles::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ACTIVE_PARTICLES; ++i)
	{
		// Always destroy particles that collide
		if (active[i] != nullptr && active[i]->collider == c1)
		{
			if (c1->type == COLLIDER_PLAYER_SHOT && c2->type == COLLIDER_WALL)
			{
				//App->audio->PlayFx(4, 0);
				//App->particles->AddParticle(Projectile_explosion, active[i]->position.x, active[i]->position.y, NO_COLLIDER);
				explosion_solid = true;
				hitobject = true;
				break;
			}

			if (c1->type == COLLIDER_PLAYER_SHOT && c2->type == COLLIDER_ENEMY)
			{
				//App->audio->PlayFx(4, 0);
				//App->particles->AddParticle(Projectile_explosion, active[i]->position.x, active[i]->position.y, NO_COLLIDER);
				explosion_solid = true;
				hitobject = true;
				break;
			}

			// Always destroy particles that collide
			/*if (active[i] != nullptr && active[i]->collider == c1)
			{
				App->particles->AddParticle(Projectile_explosion, active[i]->position.x, active[i]->position.y, NO_COLLIDER);

				delete active[i];
				active[i] = nullptr;
				break;
			}*/
			break;
		}
	}
}


// -------------------------------------------------------------
// -------------------------------------------------------------

Particle::Particle()
{
	position.SetToZero();
	speed.SetToZero();
}

Particle::Particle(const Particle& p) :
	anim(p.anim), position(p.position), speed(p.speed),
	fx(p.fx), born(p.born), life(p.life)
{}

Particle::~Particle()
{
	if (collider != nullptr)
		collider->to_delete = true;
}

bool Particle::Update()
{
	BROFILER_CATEGORY("UpdateParticlesStruct", Profiler::Color::BurlyWood)

	bool ret = true;

	if (life > 0)
	{
		if ((SDL_GetTicks() - born) > life)
			ret = false;
	}
	else
		if (anim.Finished())
			ret = false;

	position.x += speed.x;
	position.y += speed.y;
	collider->SetPos(position.x, position.y);

	return ret;
}



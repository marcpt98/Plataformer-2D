#include "j1Window.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Scene.h"
#include "j1Map.h"
#include "j1App.h"
#include "j1FadeToBlack.h"
#include "j1Particles.h"
#include "Animation.h"
#include<stdio.h>
#include "j1Colliders.h"
#include "p2Log.h"
#include "j1EntityManager.h"
#include "j1Entity.h"
#include "Enemy_Slime.h"


Enemy_Slime::Enemy_Slime(int posx, int posy) : j1Entity(entityType::LAND_ENEMY)
{
	name.create("slime");

	actualState = ST_SLIME_IDLE;

	position.x = posx;
	position.y = posy;

	// Ghost follow
	idle.PushBack({ 0, 0, 56, 28 }, 0.1, 0, 0);
	idle.PushBack({ 60, 0, 56, 28 }, 0.1, 0, 0);
	idle.PushBack({ 120, 0, 56, 28 }, 0.1, 0, 0);
	idle.PushBack({ 180, 0, 56, 26 }, 0.1, 0, 0);
	idle.PushBack({ 240, 0, 52, 24 }, 0.1, 0, 0);
	idle.PushBack({ 296, 0, 52, 24 }, 0.1, 0, 0);
	idle.PushBack({ 352, 0, 48, 24 }, 0.1, 0, 0);
	idle.PushBack({ 404, 0, 52, 22 }, 0.1, 0, 0);

	// Ghost dead
	dead.PushBack({ 50, 92, 60, 60 }, 0.1, 0, 0);
	dead.PushBack({ 112, 92, 58, 82 }, 0.1, 0, 0);
	dead.PushBack({ 172, 92, 30, 34 }, 0.1, 0, 0);
	dead.PushBack({ 204, 92, 20, 24 }, 0.1, 0, 0);
	dead.PushBack({ 226, 92, 40, 36 }, 0.1, 0, 0);
	dead.PushBack({ 268, 92, 34, 36 }, 0.1, 0, 0);
	dead.loop = false;
}

Enemy_Slime::~Enemy_Slime()
{}

bool Enemy_Slime::Start()
{
	// Add ghost collider
	ghost_collider = App->colliders->AddCollider({ position.x,position.y, 40, 53 }, COLLIDER_ENEMY, this);

	return true;
}

bool Enemy_Slime::CleanUp()
{

	return true;
}

bool Enemy_Slime::Update(float dt)
{
	BROFILER_CATEGORY("UpdateGhost", Profiler::Color::BlanchedAlmond);

	// Ghost colliders
	ghost_collider->SetPos(position.x, position.y);

	CheckAnimation(dt);

	// Print ghost
	if (blit == false)
	{
		App->render->Blit(App->entity->slime_graphics, position.x + current_animation->pivotx[current_animation->returnCurrentFrame()], position.y + current_animation->pivoty[current_animation->returnCurrentFrame()], &(current_animation->GetCurrentFrame(dt)), 1.0f);
	}
	else
	{
		App->render->BlitWithScale(App->entity->slime_graphics, position.x + fixBlit + (-current_animation->pivotx[current_animation->returnCurrentFrame()]), position.y + current_animation->pivoty[current_animation->returnCurrentFrame()], &(current_animation->GetCurrentFrame(dt)), -1, 1.0f, 1, TOP_RIGHT);
	}

	return true;
}

bool Enemy_Slime::PostUpdate(float dt)
{
	BROFILER_CATEGORY("PostupdateGhost", Profiler::Color::BurlyWood)

		return true;
}

void Enemy_Slime::CheckAnimation(float dt)
{
	if (slime_dead == false)
	{
		current_animation = &idle;
		dead.Reset();
	}
	if (slime_dead == true)
	{
		current_animation = &dead;

		if (SDL_GetTicks() > dead_slime_animation_finish + deadSlimeDelay)
		{
			// TODO: Delete entity
			count_slime_dead = false;
			slime_dead = false;
		}
	}
}

void Enemy_Slime::OnCollision(Collider* c1, Collider* c2)
{
	if (ghost_collider == c1 && c2->type == COLLIDER_PLAYER_SHOT)
	{
		if (count_slime_dead == false)
		{
			dead_slime_animation_finish = SDL_GetTicks();
			App->audio->PlayFx(5, 0);
			slime_dead = true;
			count_slime_dead = true;
		}

	}
}

void Enemy_Slime::Pathfinding(float dt)
{


}
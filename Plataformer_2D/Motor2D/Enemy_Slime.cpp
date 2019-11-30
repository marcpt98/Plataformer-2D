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
#include "j1PathFinding.h"


Enemy_Slime::Enemy_Slime(int posx, int posy) : j1Entity(entityType::LAND_ENEMY)
{
	LoadConfigInfo();

	name.create("slime");

	actualState = ST_SLIME_IDLE;

	position.x = posx;
	position.y = posy;

	// Slime follow
	idle.PushBack({ 0, 0, 56, 28 }, 0.1, 0, 0);
	idle.PushBack({ 60, 0, 56, 28 }, 0.1, 0, 0);
	idle.PushBack({ 120, 0, 56, 28 }, 0.1, 0, 0);
	idle.PushBack({ 180, 0, 56, 26 }, 0.1, 0, 0);
	idle.PushBack({ 240, 0, 52, 24 }, 0.1, 0, 0);
	idle.PushBack({ 296, 0, 52, 24 }, 0.1, 0, 0);
	idle.PushBack({ 352, 0, 48, 24 }, 0.1, 0, 0);
	idle.PushBack({ 404, 0, 52, 22 }, 0.1, 0, 0);

	// Slime dead
	dead.PushBack({ 0,76,56,26 }, 0.15, 0, 0);
	dead.PushBack({ 60,76,56,28 }, 0.15, 0, -1);
	dead.PushBack({ 120,76,56,32 }, 0.15, 0, -5);
	dead.PushBack({ 180,76,60,18 }, 0.15, 0, 10);
	dead.PushBack({ 244,76,62,4 }, 0.15, 0, 21);
	dead.loop = false;
}

Enemy_Slime::~Enemy_Slime()
{}

bool Enemy_Slime::Start()
{
	// Add slime collider
	collider = App->colliders->AddCollider({ position.x,position.y, width, high }, COLLIDER_ENEMY, this);
	graphics_debug_tex = App->tex->Load(debug_tex.GetString());

	return true;
}

bool Enemy_Slime::CleanUp()
{

	return true;
}

bool Enemy_Slime::Update(float dt)
{
	BROFILER_CATEGORY("UpdateGhost", Profiler::Color::BlanchedAlmond);

	lasPosition.x = position.x;

	// Gravity
	if (slime_dead == false)
	{
		position.y += (int)(gravity * dt * VELOCITY);
	}

		CheckAnimation(dt);
		Pathfinding(dt);
	

	// Slime colliders
	collider->SetPos(position.x, position.y);

	// Print slime
	if (blit == false)
	{
		App->render->Blit(App->entity->slime_graphics, position.x + current_animation->pivotx[current_animation->returnCurrentFrame()], position.y + current_animation->pivoty[current_animation->returnCurrentFrame()], &(current_animation->GetCurrentFrame(dt)), 1.0f);
	}
	else
	{
		App->render->BlitWithScale(App->entity->slime_graphics, position.x + fixBlit + (-current_animation->pivotx[current_animation->returnCurrentFrame()]), position.y + current_animation->pivoty[current_animation->returnCurrentFrame()], &(current_animation->GetCurrentFrame(dt)), -1, 1.0f, 1, TOP_RIGHT);
	}
	gravity = gGravity;
	return true;
}

bool Enemy_Slime::PostUpdate(float dt)
{
	BROFILER_CATEGORY("PostupdateSlime", Profiler::Color::BurlyWood)

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
			App->entity->DeleteEntity(this);
			count_slime_dead = false;
			slime_dead = false;
		}
	}

	if (actualState == ST_SLIME_FOLLOW_Down)
	{
		current_animation = &idle;
		position.y += (speed * VELOCITY * dt);
		if (App->entity->InfoPlayer()->position.x < position.x)
		{
			blit = false;
		}
		else
		{
			blit = true;
		}
	}
	if (actualState == ST_SLIME_FOLLOW_Backward)
	{
		current_animation = &idle;
		position.x -= (speed * VELOCITY * dt);
		if (App->entity->InfoPlayer()->position.x < position.x)
		{
			blit = false;
		}
		else
		{
			blit = true;
		}
	}
	if (actualState == ST_SLIME_FOLLOW_Forward)
	{
		current_animation = &idle;
		position.x += (2 * VELOCITY * dt);
		if (App->entity->InfoPlayer()->position.x < position.x)
		{
			blit = false;
		}
		else
		{
			blit = true;
		}
	}

	if (actualState == ST_SLIME_IDLE && slime_dead == false)
	{
		start += 1;

		if (start < 100)
		{
			blit = false;
			position.x -= 1;
		}
		else
		{
			blit = true;
			position.x += 1;
			if (start > 200)
			{
				start = 0;
			}
		}
	}
}

void Enemy_Slime::OnCollision(Collider* c1, Collider* c2)
{
	if (collider == c1 && c2->type == COLLIDER_FLOOR)
	{
		gravity = 0;

		if (position.y + high > c2->rect.y && position.x < (c2->rect.x + c2->rect.w) && (position.x + width) >(c2->rect.x))// over a floor collision  
		{
			position.y = c2->rect.y - high;
		}
	}

	if (collider == c1 && c2->type == COLLIDER_PLAYER_SHOT)
	{
		collider->to_delete = true;

		if (count_slime_dead == false)
		{
			dead_slime_animation_finish = SDL_GetTicks();
			App->audio->PlayFx(7, 0);
			slime_dead = true;
			count_slime_dead = true;
		}

	}
}

void Enemy_Slime::Pathfinding(float dt)
{
	BROFILER_CATEGORY("PathfindingSlime", Profiler::Color::HoneyDew)

	p = App->render->ScreenToWorld(x, y);   //Player position
	p = App->entity->InfoPlayer()->position;
	p = App->map->WorldToMap(p.x, p.y);

	origin = App->map->WorldToMap(position.x, position.y);	//Slime position

	if (origin != p && App->entity->InfoPlayer()->position.x - 300 < position.x && App->entity->InfoPlayer()->position.x + 300 > position.x && App->entity->InfoPlayer()->position.y - 400 < position.y && App->entity->InfoPlayer()->position.y + 400 > position.y && slime_dead == false)
	{
		App->path->CreatePath(origin, p);
		Follow_path(dt);
	}
	else
	{
		actualState = ST_SLIME_IDLE;
	}


	//Draw pathfinding
	if (App->colliders->debug == true) {

		lastpath = App->path->GetLastPath();

		for (uint i = 0; i < lastpath->Count(); ++i)
		{
			pos = App->map->MapToWorld(lastpath->At(i)->x, lastpath->At(i)->y);
			App->render->Blit(graphics_debug_tex, pos.x, pos.y);
		}
	}

}

void Enemy_Slime::Follow_path(float dt)
{
	path = App->path->GetLastPath();
	pos = App->map->MapToWorld(path->At(1)->x, path->At(1)->y);

	if (path->At(1) != NULL)
	{
		if (pos.x < position.x)
		{
			actualState = ST_SLIME_FOLLOW_Backward;
		}
		if (pos.x > position.x)
		{
			actualState = ST_SLIME_FOLLOW_Forward;
		}
		if (pos.y > position.y)
		{
			actualState = ST_SLIME_FOLLOW_Down;
		}
	}
}

bool Enemy_Slime::LoadConfigInfo()
{
	// Loading files from config
	pugi::xml_document	config_file;
	pugi::xml_node		config;
	config = App->LoadConfig(config_file);
	config = config.child("slime");

	// Slime width and high
	width = config.child("width").attribute("w").as_int();
	high = config.child("high").attribute("h").as_int();

	// Gravity
	gravity = config.child("gravity").attribute("g").as_float();

	// Ggravity
	gGravity = config.child("gGravity").attribute("g").as_float();

	// Slime speed
	speed = config.child("speed").attribute("s").as_float();

	// Fix blit
	fixBlit = config.child("fixBlit").attribute("fix").as_int();

	// Dead delay
	deadSlimeDelay = config.child("deadDelay").attribute("d").as_int();

	// Pathfinding
	debug_tex = config.child("Cross").attribute("c").as_string();

	return true;
}
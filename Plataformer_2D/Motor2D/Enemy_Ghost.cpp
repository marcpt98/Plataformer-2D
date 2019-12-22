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
#include "Enemy_Ghost.h"
#include "j1PathFinding.h"

Enemy_Ghost::Enemy_Ghost(int posx, int posy) : j1Entity(entityType::FLYING_ENEMY)
{
	LoadConfigInfo();

	name.create("ghost");

	actualState = ST_GHOST_IDLE;

	position.x = posx;
	position.y = posy;

	// Ghost idle
	idle.PushBack({ 0, 182, 48, 84 }, 0.1, 0, 0);
	idle.PushBack({ 50, 182, 56, 82 }, 0.1, 0, 0);
	idle.PushBack({ 108, 182, 52, 84 }, 0.1, 0, 0);
	idle.PushBack({ 162, 182, 48, 84 }, 0.1, 0, 0);
	idle.PushBack({ 212, 182, 48, 84 }, 0.1, 0, 0);
	idle.PushBack({ 262, 182, 49, 88 }, 0.1, 0, 0);
	idle.PushBack({ 314, 182, 47, 86 }, 0.1, 0, 0);

	// Ghost follow
	//follow.PushBack({ 0, 0, 48, 84 }, 0.1, 0, 0);
	//follow.PushBack({ 50, 0, 62, 84 }, 0.1, 0, 0);
	follow.PushBack({ 114, 0, 92, 84 }, 0.1, -30, 0);
	follow.PushBack({ 208, 0, 88, 86 }, 0.1, -30, 0);
	
	// Ghost dead
	dead.PushBack({ 50, 92, 60, 60 }, 0.1, 0, 0);
	dead.PushBack({ 112, 92, 58, 82 }, 0.1, 0, 0);
	dead.PushBack({ 172, 92, 30, 34 }, 0.1, 0, 0);
	dead.PushBack({ 204, 92, 20, 24 }, 0.1, 0, 0);
	dead.PushBack({ 226, 92, 40, 36 }, 0.1, 0, 0);
	dead.PushBack({ 268, 92, 34, 36 }, 0.1, 0, 0);
	dead.loop = false;

	pause.PushBack({ 0, 182, 48, 84 }, 0.1, 0, 0);
}

Enemy_Ghost::~Enemy_Ghost()
{}

bool Enemy_Ghost::Start()
{
	// Add ghost collider
	collider = App->colliders->AddCollider({ position.x,position.y, width, high }, COLLIDER_ENEMY, this);
	graphics_debug_tex = App->tex->Load(debug_tex.GetString());

	return true;
}

bool Enemy_Ghost::CleanUp()
{

	return true;
}

bool Enemy_Ghost::Update(float dt)
{
	BROFILER_CATEGORY("UpdateGhost", Profiler::Color::BlanchedAlmond);
	// Ghost colliders
	collider->SetPos(position.x, position.y);
	
	if (App->scene->pause == false)
	{
		CheckAnimation(dt);
		Pathfinding(dt);
	}

	if (App->scene->pause == true)
	{
		current_animation = &pause;
	}

	// Print ghost
	if (blit == false)
	{
		App->render->Blit(App->entity->ghost_graphics, position.x + current_animation->pivotx[current_animation->returnCurrentFrame()], position.y + current_animation->pivoty[current_animation->returnCurrentFrame()], &(current_animation->GetCurrentFrame(dt)), 1.0f);
	}
	else
	{
		App->render->BlitWithScale(App->entity->ghost_graphics, position.x + fixBlit + (-current_animation->pivotx[current_animation->returnCurrentFrame()]), position.y + current_animation->pivoty[current_animation->returnCurrentFrame()], &(current_animation->GetCurrentFrame(dt)), -1, 1.0f, 1, TOP_RIGHT);
	}

	return true;
}

bool Enemy_Ghost::PostUpdate(float dt)
{
	BROFILER_CATEGORY("PostupdateGhost", Profiler::Color::BurlyWood)

	return true;
}

void Enemy_Ghost::CheckAnimation(float dt)
{
	if (ghost_dead == false)
	{
		current_animation = &idle;
		dead.Reset();
	}
	if (ghost_dead == true)
	{
		current_animation = &dead;

		if (SDL_GetTicks() > dead_ghost_animation_finish + deadGhostDelay)
		{
			App->entity->DeleteEntity(this);
			count_ghost_dead = false;
			ghost_dead = false;
		}
	}

	if (actualState == ST_GHOST_FOLLOW_Down) 
	{
		current_animation = &follow;
		position.y += (speedy * VELOCITY * dt);
		if (App->entity->InfoPlayer()->position.x < position.x)
		{
			blit = false;
		}
		else
		{
			blit = true;
		}
	}
	if (actualState == ST_GHOST_FOLLOW_Up)
	{
		current_animation = &follow;
		position.y -= (speedy * VELOCITY * dt);
		if (App->entity->InfoPlayer()->position.x < position.x)
		{
			blit = false;
		}
		else
		{
			blit = true;
		}
	}
	if (actualState == ST_GHOST_FOLLOW_Backward)
	{
		current_animation = &follow;
		position.x -= (speedx * VELOCITY * dt);
		if (App->entity->InfoPlayer()->position.x < position.x)
		{
			blit = false;
		}
		else
		{
			blit = true;
		}
	}
	if (actualState == ST_GHOST_FOLLOW_Forward)
	{
		current_animation = &follow;
		position.x += (speedx * VELOCITY * dt);
		if (App->entity->InfoPlayer()->position.x < position.x)
		{
			blit = false;
		}
		else
		{
			blit = true;
		}
	}

	if (actualState == ST_GHOST_IDLE)
	{
		start +=1;
		
		if (going_up)
		{
			if (wave > 1.0f)
				going_up = false;
			else
				wave += 0.05f;
		}
		else
		{
			if (wave < -1.0f)
				going_up = true;
			else
				wave -= 0.05f;
		}

		position.y += int(3.0f * sinf(wave));

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

void Enemy_Ghost::OnCollision(Collider* c1, Collider* c2)
{
	if (collider == c1 && c2->type == COLLIDER_PLAYER_SHOT)
	{
		collider->to_delete = true;

		if (count_ghost_dead == false)
		{
			dead_ghost_animation_finish = SDL_GetTicks();
			App->audio->PlayFx(5, 0);
			ghost_dead = true;
			count_ghost_dead = true;
		}
	}
}

void Enemy_Ghost::Pathfinding(float dt)
{
	BROFILER_CATEGORY("PathfindingGhost", Profiler::Color::BlanchedAlmond)
	
	p = App->render->ScreenToWorld(x, y);   //Player position
	p = App->entity->InfoPlayer()->position;
	p = App->map->WorldToMap(p.x, p.y);

	origin = App->map->WorldToMap(position.x, position.y);	//Ghost position

	if (origin != p && App->entity->InfoPlayer()->position.x - 300 < position.x && App->entity->InfoPlayer()->position.x + 300 > position.x && App->entity->InfoPlayer()->position.y - 400 < position.y && App->entity->InfoPlayer()->position.y + 400 > position.y && ghost_dead == false)
	{
		if (ghost_playFx == false)
		{
			App->audio->PlayFx(6, 0);
			ghost_playFx = true;
		}
		App->path->CreatePath(origin, p);
		Follow_path(dt);
	}
	else 
	{
		actualState = ST_GHOST_IDLE;
		ghost_playFx = false;
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

void Enemy_Ghost::Follow_path(float dt)
{
	path = App->path->GetLastPath();
	pos = App->map->MapToWorld(path->At(1)->x, path->At(1)->y);

	if (path->At(1) != NULL)
	{
		if (pos.x < position.x) 
		{
			actualState = ST_GHOST_FOLLOW_Backward;
		}
		if (pos.x > position.x) 
		{
			actualState = ST_GHOST_FOLLOW_Forward;
		}
		if (pos.y > position.y) 
		{
			actualState = ST_GHOST_FOLLOW_Down;
		}
		if (pos.y < position.y) 
		{
			actualState = ST_GHOST_FOLLOW_Up;
		}
	}
}

bool Enemy_Ghost::LoadConfigInfo()
{
	// Loading files from config
	pugi::xml_document	config_file;
	pugi::xml_node		config;
	config = App->LoadConfig(config_file);
	config = config.child("ghost");

	// Ghost width and high
	width = config.child("width").attribute("w").as_int();
	high = config.child("high").attribute("h").as_int();
	
	// Ghost speed
	speedx = config.child("speedx").attribute("s").as_float();
	speedy = config.child("speedy").attribute("s").as_float();

	// Fix blit
	fixBlit = config.child("fixBlit").attribute("fix").as_int();

	// Dead delay
	deadGhostDelay = config.child("deadDelay").attribute("d").as_int();

	// Pathfinding
	debug_tex = config.child("Cross").attribute("c").as_string();
	
	// Ghost move idle
	wave = config.child("Wave").attribute("w").as_float();

	return true;
}
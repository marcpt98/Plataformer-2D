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

Enemy_Ghost::Enemy_Ghost(int posx, int posy) : j1Entity(entityType::FLYING_ENEMY)
{
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
	follow.PushBack({ 0, 0, 48, 84 }, 0.1, 0, 0);
	follow.PushBack({ 50, 0, 62, 84 }, 0.1, 0, 0);
	follow.PushBack({ 114, 0, 92, 84 }, 0.1, 0, 0);
	follow.PushBack({ 208, 0, 88, 86 }, 0.1, 0, 0);

	// Ghost dead
	dead.PushBack({ 50, 92, 60, 60 }, 0.1, 0, 0);
	dead.PushBack({ 112, 92, 58, 82 }, 0.1, 0, 0);
	dead.PushBack({ 172, 92, 30, 34 }, 0.1, 0, 0);
	dead.PushBack({ 204, 92, 20, 24 }, 0.1, 0, 0);
	dead.PushBack({ 226, 92, 40, 36 }, 0.1, 0, 0);
	dead.PushBack({ 268, 92, 34, 36 }, 0.1, 0, 0);
	dead.loop = false;
}

Enemy_Ghost::~Enemy_Ghost()
{}

bool Enemy_Ghost::Start()
{
	// Add ghost collider
	ghost_collider = App->colliders->AddCollider({ position.x,position.y, 40, 53 }, COLLIDER_ENEMY, this);

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
	ghost_collider->SetPos(position.x, position.y);

	CheckAnimation(dt);

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
			// TODO: Delete entity
			count_ghost_dead = false;
			ghost_dead = false;
		}
	}
}

void Enemy_Ghost::OnCollision(Collider* c1, Collider* c2)
{
	if (ghost_collider == c1 && c2->type == COLLIDER_PLAYER_SHOT)
	{
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


}
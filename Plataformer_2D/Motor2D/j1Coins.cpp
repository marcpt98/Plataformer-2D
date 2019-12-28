#include "j1Window.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Scene.h"
#include "j1Map.h"
#include "j1App.h"
#include "j1FadeToBlack.h"
#include "j1Player.h"
#include "j1Particles.h"
#include "Animation.h"
#include <stdio.h>
#include "j1Colliders.h"
#include "p2Log.h"
#include "j1EntityManager.h"
#include "j1Entity.h"
#include "j1CheckPoint.h"
#include "j1Coins.h"

j1Coins::j1Coins(int posx, int posy) : j1Entity(entityType::COIN)
{
	LoadConfigInfo();
	name.create("coin");

	// Idle animation
	idle.PushBack({ 0,0,28,32 }, 0.2, 0, 0);
	idle.PushBack({ 36,0,20,32 }, 0.2, 3, 0);
	idle.PushBack({ 72,0,12,32 }, 0.2, 5, 0);
	idle.PushBack({ 100,0,20,32 }, 0.2, 3, 0);
	idle.PushBack({ 128,0,26,32 }, 0.2, 0, 0);

	paused.PushBack({ 72,0,12,32 }, 0.2, 5, 0);

	position.x = posx;
	position.y = posy;

}

j1Coins::~j1Coins()
{}

bool j1Coins::Start()
{
	alive = true;
	// Add player collider
	collider = App->colliders->AddCollider({ position.x,position.y, 27, 32 }, COLLIDER_CHECKPOINT, this);

	return true;
}

bool j1Coins::CleanUp()
{

	return true;
}

bool j1Coins::Update(float dt)
{
	BROFILER_CATEGORY("UpdateCoins", Profiler::Color::Turquoise);

	CheckAnimation(dt);

	App->render->Blit(App->entity->coins_graphics, position.x + current_animation->pivotx[current_animation->returnCurrentFrame()], position.y + current_animation->pivoty[current_animation->returnCurrentFrame()], &(current_animation->GetCurrentFrame(dt)), 1.0f);

	return true;
}

bool j1Coins::PostUpdate(float dt)
{
	BROFILER_CATEGORY("PostupdateCoins", Profiler::Color::DarkTurquoise)

		return true;
}

void j1Coins::CheckAnimation(float dt)
{
	if (App->scene->pause == false)
	{
		current_animation = &idle;
	}
	else {
		current_animation = &paused;
	}
}

void j1Coins::OnCollision(Collider* c1, Collider* c2)
{

	if (collider == c1 && c2->type == COLLIDER_PLAYER)
	{
		App->scene->last_player_score = App->scene->player_score;
		App->scene->player_score = App->scene->player_score + 100;
		App->scene->diferent_score = true;
		collider->to_delete = true;
		App->audio->PlayFx(9, 0);
		App->entity->DeleteEntity(this);

	}


}

bool j1Coins::LoadConfigInfo()
{
	// Loading files from config
	pugi::xml_document	config_file;
	pugi::xml_node		config;
	config = App->LoadConfig(config_file);
	config = config.child("coin");


	return true;
}
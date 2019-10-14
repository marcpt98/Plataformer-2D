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
#include "Animation.h"
#include<stdio.h>
#include "j1Colliders.h"
#include "p2Log.h"

j1Player::j1Player() 
{ 
	name.create("player");

	graphics = NULL;
	current_animation = NULL;

	// Idle animation
	idle.PushBack({ 0,0,42,52 }, 0.2, 0, 0);
	idle.PushBack({ 44,0,40,54 }, 0.2, 2, -2);
	idle.PushBack({ 86,0,42,54 }, 0.2, 0, -2);
	idle.PushBack({ 130,0,44,52 }, 0.2, 0, 0);
	
	// Run animation
	run.PushBack({ 0,0,0,0 }, 0.2, 0, 0);
	run.PushBack({ 0,0,0,0 }, 0.2, 0, 0);
	run.PushBack({ 0,0,0,0 }, 0.2, 0, 0);
	run.PushBack({ 0,0,0,0 }, 0.2, 0, 0);

	// Jump animation
	jump.PushBack({ 0,0,0,0 }, 0.2, 0, 0);
	jump.PushBack({ 0,0,0,0 }, 0.2, 0, 0);
	jump.PushBack({ 0,0,0,0 }, 0.2, 0, 0);
	jump.PushBack({ 0,0,0,0 }, 0.2, 0, 0);

	// Special animation
	special.PushBack({ 0,0,0,0 }, 0.2, 0, 0);
	special.PushBack({ 0,0,0,0 }, 0.2, 0, 0);
	special.PushBack({ 0,0,0,0 }, 0.2, 0, 0);
	special.PushBack({ 0,0,0,0 }, 0.2, 0, 0);
}

j1Player::~j1Player()
{

}

bool j1Player::Awake(pugi::xml_node& config)
{
	LOG("Loading Player");

	bool ret = true;

	// Player initial position
	position.x = config.child("position").attribute("x").as_int();
	position.y = config.child("position").attribute("y").as_int();

	// Player spritesheet
	spritesheet = config.child("spritesheet").attribute("player").as_string("");

	return ret;
}

bool j1Player::Start() 
{
	current_animation = &idle;

	graphics = App->tex->Load(spritesheet.GetString());

	collider = App->colliders->AddCollider({ position.x,position.y, 35, 80 }, COLLIDER_PLAYER, this); //a collider to start

	return true;
}

bool j1Player::CleanUp() 
{

	App->tex->UnLoad(graphics);
	return true;

}

bool j1Player::Update(float dt) 
{
	App->player->position.y += 2;

	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		App->player->position.y -= 2;

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		App->player->position.x -= 2;

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		App->player->position.y += 2;

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		App->player->position.x += 2;

	collider->SetPos(position.x, position.y);

	App->render->Blit(graphics, position.x + current_animation->pivotx[current_animation->returnCurrentFrame()], position.y + current_animation->pivoty[current_animation->returnCurrentFrame()], &(current_animation->GetCurrentFrame()), 1.0f);
	
	return true;

}

bool j1Player::PostUpdate(float dt)
{
	return true;

}

void j1Player::OnCollision(Collider* c1, Collider* c2) {
	if (collider == c1 && c2->type == COLLIDER_WALL)
	{
		LOG("COLLIDERS WOOOOOOOOOOOOOOOOOOOOOORKS");


	}
	
	if (collider == c2 && c1->type == COLLIDER_WALL)
	{
		LOG("COLLIDERS WOOOOOOOOOOOOOOOOOOOOOORKS");

	}

	switch (c2->type)
	{
	case COLLIDER_WALL: //here we will put what happens when the colliders collide 
		LOG("COLLIDERS WOOOOOOOOOOOOOOOOOOOOOORKS");
		
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			position.y = position.y - 4;
			LOG("AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA");
		}
		else
		{
			LOG("BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBB");
			position.y = position.y - 2;
		}
		/*position = lastPosition;
		velocity.x = velocity.y = 0;
		if ((position.y < c2->rect.y) && (last_state == FALL))
		{
			//state = IDLE;
			position.y--;
		}*/
		break;
	case COLLIDER_DEATH:
		
		//App->scene->Reset_Camera(); we will make something to reset the camera maybe we can just make the camera follow the player
		break;
	default:
		break;
	}
}
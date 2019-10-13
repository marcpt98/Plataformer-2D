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

j1Player::j1Player() { 

	graphics = NULL;
	current_animation = NULL;

	position.x = 200;
	position.y = 550;

	idle.PushBack({ 0,0,42,52 });
	idle.PushBack({ 44,0,40,54 });
	idle.PushBack({ 86,0,42,54 });
	idle.PushBack({ 130,0,44,52 });
	idle.speed = 0.035f;

}

j1Player::~j1Player()
{

}

bool j1Player::Start() 
{
	current_animation = &idle;
	graphics = App->tex->Load("textures/Spritesheet_Character_1.png");
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
	if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		App->player->position.y -= 2;

	if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		App->player->position.x -= 2;

	if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		App->player->position.y += 2;

	if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		App->player->position.x += 2;

	collider->SetPos(position.x, position.y);

	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()), 1.0f);
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
		position.x = position.x+2;
		position.y = position.y-2;
		/*position = lastPosition;
		velocity.x = velocity.y = 0;
		if ((position.y < c2->rect.y) && (last_state == FALL))
		{
			//state = IDLE;
			position.y--;
		}*/
		break;
	case COLLIDER_DEATH:
		position.x = initial_x_position;
		position.y = initial_y_position;
		//App->scene->Reset_Camera(); we will make something to reset the camera maybe we can just make the camera follow the player
		break;
	default:
		break;
	}
}
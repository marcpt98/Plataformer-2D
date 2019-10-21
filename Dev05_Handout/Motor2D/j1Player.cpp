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
	run.PushBack({ 0,110,40,50 }, 0.2, 0, 0);
	run.PushBack({ 42,110,42,50 }, 0.2, 0, 0);
	run.PushBack({ 86,110,42,48 }, 0.2, 0, 0);
	run.PushBack({ 130,110,40,50 }, 0.2, 0, 0);
	run.PushBack({ 172,110,42,50 }, 0.2, 0, 0);
	run.PushBack({ 216,110,42,48 }, 0.2, 0, 0);

	// Jump animation
	jump.PushBack({ 0,161,42,52 }, 0.2, 0, 0);
	jump.PushBack({ 44,161,44,48 }, 0.2, 0, 0);
	jump.PushBack({ 90,161,46,48 }, 0.2, 0, 0);
	jump.PushBack({ 138,161,40,60 }, 0.2, 0, 0);
	jump.PushBack({ 180,161,42,54 }, 0.2, 0, 0);
	jump.PushBack({ 224,161,44,54 }, 0.2, 0, 0);
	jump.PushBack({ 270,161,46,48 }, 0.2, 0, 0);
	jump.PushBack({ 318,161,40,52 }, 0.2, 0, 0);

	// Death animation
	death.PushBack({ 0,444,44,56 }, 0.15, 0, 0);
	death.PushBack({ 46,444,50,58 }, 0.15, 0, 0);
	death.PushBack({ 98,444,52,38 }, 0.15, 0, 20);
	death.PushBack({ 152,444,58,22 }, 0.15, 0, 30);
	death.PushBack({ 212,444,70,24 }, 0.15, 0, 30);
	death.PushBack({ 284,444,50,26 }, 0.15, 0, 30);
	death.PushBack({ 336,444,30,30 }, 0.15, 0, 25);
	death.PushBack({ 374,444,18,16 }, 0.15, 0, 25);
}

j1Player::~j1Player()
{}

bool j1Player::Awake(pugi::xml_node& config)
{
	LOG("Loading Player");

	bool ret = true;

	// Player position
	position.x = config.child("position").attribute("x").as_int();
	position.y = config.child("position").attribute("y").as_int();

	// Player initial position
	iPosition.x = config.child("iPosition").attribute("x").as_int();
	iPosition.y = config.child("iPosition").attribute("y").as_int();

	// Player spritesheet
	spritesheet = config.child("spritesheet").attribute("player").as_string("");

	// Player speed
	speed = config.child("speed").attribute("s").as_float();

	// Gravity
	gravity = config.child("gravity").attribute("g").as_int();

	// Jump force
	jumpF = config.child("jumpF").attribute("j").as_float();

	// Fix blit
	fixBlit = config.child("fixBlit").attribute("fix").as_float();

	return ret;
}

bool j1Player::Start() 
{
	// Load spritesheet
	graphics = App->tex->Load(spritesheet.GetString());

	// Add player collider
	collider = App->colliders->AddCollider({ position.x,position.y, 40, 53 }, COLLIDER_PLAYER, this); //a collider to start COLLIDER PLAYER

	
	// Set initial position
	position.x = iPosition.x;
	position.y = iPosition.y;

	return true;
}

bool j1Player::CleanUp() 
{
	App->tex->UnLoad(graphics);

	return true;
}

bool j1Player::Update(float dt) 
{

	// Gravity
	if (godMode == true)
	{
		position.y = position.y;
	}
	else
	{
		lasPosition.x = position.x;
		lasPosition.y = position.y;
		position.y = position.y + gravity;
	}

	CheckInputState();
	CheckAnimation();

	// Player colliders
	collider->SetPos(position.x, position.y);

	// Print player
	if (blit == false)
	{
		App->render->Blit(graphics, position.x + current_animation->pivotx[current_animation->returnCurrentFrame()], position.y + current_animation->pivoty[current_animation->returnCurrentFrame()], &(current_animation->GetCurrentFrame()), 1.0f);
	}
	else
	{
		App->render->BlitWithScale(graphics, position.x + fixBlit + (-current_animation->pivotx[current_animation->returnCurrentFrame()]), position.y + current_animation->pivoty[current_animation->returnCurrentFrame()], &(current_animation->GetCurrentFrame()), -1, 1.0f, 1, TOP_RIGHT);
	}
	return true;
}

bool j1Player::PostUpdate(float dt)
{
	return true;

}

void j1Player::CheckInputState()
{
	// God mode
	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		if (godMode == false)
		{
			collider->to_delete = true;
			godMode = true;
		}
		else if (godMode == true)
		{
			collider = App->colliders->AddCollider({ position.x,position.y, 35, 53 }, COLLIDER_PLAYER, this);
			godMode = false;
		}
	}

	if (godMode == true)
	{
		actualState = ST_IDLE;

		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			position.y = position.y - speed;
		}
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			position.y = position.y + speed;
		}
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			position.x = position.x - speed;
		}
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			position.x = position.x + speed;
		}
	}

	// Without god mode
	else
	{
		// Player controllers
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && dead_animation == false)
		{
			actualState = ST_JUMP;
			if (canJump1 == true) 
			{
				energyJump = jumpF;
			}

			// Reset animations
			idle.Reset();
			run.Reset();
			death.Reset();
		}

		else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && canJump1 == true && dead_animation == false)
		{
			actualState = ST_RUN;
			position.x = position.x - speed;
			blit = true;

			// Reset animations
			idle.Reset();
			jump.Reset();
			death.Reset();
		}

		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && canJump1 == true && dead_animation == false)
		{
			actualState = ST_RUN;
			position.x = position.x + speed;
			blit = false;

			// Reset animations
			idle.Reset();
			jump.Reset();
			death.Reset();
		}
		else if (canJump1 == true && App->input->GetKey(SDL_SCANCODE_D) == NULL && App->input->GetKey(SDL_SCANCODE_A) == NULL && App->input->GetKey(SDL_SCANCODE_SPACE) == NULL && dead_animation==false)
		{
			actualState = ST_IDLE;

			// Reset animations
			run.Reset();
			jump.Reset();
			death.Reset();
		}
		else if (dead_animation == true)
		{
			actualState = ST_DEAD;
		}
	}
}

void j1Player::CheckAnimation()
{
	goingdown = true;
	canjumpPlat = false;
	if (actualState == ST_JUMP)
	{
		canJump1 = false;
		current_animation = &jump;
		if (energyJump < gravity) {
			energyJump += 0.5;
			position.y = position.y + energyJump;
			if (energyJump < 0) { canjumpPlat = true; }
			if (energyJump > 0) { goingdown = true; }
		}
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			position.x = position.x - speed;
			blit = true;
		}
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			position.x = position.x + speed;
			blit = false;
		}
	}

	if (actualState == ST_RUN)
	{
		current_animation = &run;
	}

	if (actualState == ST_IDLE)
	{
		current_animation = &idle;
	}

	if (actualState == ST_DEAD) 
	{
		current_animation = &death;
	}
}





void j1Player::OnCollision(Collider* c1, Collider* c2) {
	if (collider == c1 && c2->type == COLLIDER_WALL)
	{
		position.y = lasPosition.y;
		canJump1 = true;
	}

	if (collider == c1 && c2->type == COLLIDER_PLATAFORM)
	{
		if ((position.y + 50) < c2->rect.y || (c2->rect.y + 1) && canjumpPlat == false) {
			position.y = lasPosition.y;
			canJump1 = true;
		}
		else if ((position.y + 50) > c2->rect.y && goingdown == true) {
			position.y = position.y++;
		}
		if (goingdown == true && canjumpPlat == false && (position.y + 50) > c2->rect.y) {
			position.y = position.y + gravity;
		}
	}

	if (collider == c1 && c2->type == COLLIDER_DEATH)
	{
		dead_animation = true;
		position.y = lasPosition.y;
		
		if (count_dead == false)
		{
			dead_animation_finish = SDL_GetTicks();
			count_dead = true;
		}
		if (SDL_GetTicks() > dead_animation_finish + 800)
		{
			dead = true;
			dead_animation = false;
			count_dead = false;
		}
	}

	/*
	switch (c2->type)
	{
	case COLLIDER_WALL: // what happens when colliders collide 
		
			
		position.y = position.y - gravity;

		/*position = lastPosition;
		velocity.x = velocity.y = 0;
		if ((position.y < c2->rect.y) && (last_state == FALL))
		{
			//state = IDLE;
			position.y--;
		}
		break;
	case COLLIDER_DEATH:
		
		//App->scene->Reset_Camera(); we will make something to reset the camera maybe we can just make the camera follow the player
		break;
	default:
		break;*/
	
}
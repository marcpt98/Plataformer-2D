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
	return true;

}

bool j1Player::CleanUp() 
{

	App->tex->UnLoad(graphics);
	return true;

}

bool j1Player::Update(float dt) 
{

	App->render->Blit(graphics, position.x, position.y, &(current_animation->GetCurrentFrame()), 1.0f);
	return true;

}

bool j1Player::PostUpdate(float dt)
{
	return true;

}
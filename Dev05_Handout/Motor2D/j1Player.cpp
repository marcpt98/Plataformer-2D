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
#include<stdio.h>

j1Player::j1Player() { 

	position.x = 200;
	position.y = 400;

}

j1Player::~j1Player()
{

}

bool j1Player::Start() 
{

	graphics = App->tex->Load("textures/test.png");
	return true;

}

bool j1Player::CleanUp() 
{

	App->tex->UnLoad(graphics);
	return true;

}

bool j1Player::Update(float dt) 
{

	App->render->Blit(graphics, position.x, position.y);//this still need to pass the diferents animations of the character
	return true;

}

bool j1Player::PostUpdate(float dt)
{
	return true;

}
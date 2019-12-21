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

j1CheckPoint::j1CheckPoint(int posx, int posy) : j1Entity(entityType::CHECKPOINT)
{
	LoadConfigInfo();
	name.create("checkPoint");

	// Idle animation
	idle.PushBack({ 0,0,67,85 }, 0.14, 0, 0);
	idle.PushBack({ 67,0,66,85 }, 0.1, 0, 0);
	idle.PushBack({ 133,0,67,85 }, 0.14, 0, 0);

	idle_no_check.PushBack({ 200,0,19,85 }, 0.14, 0, 0);

	position.x = posx;
	position.y = posy;

	// Initializing variables
	actualState = ST_NO_CHECK;
}

j1CheckPoint::~j1CheckPoint()
{}

bool j1CheckPoint::Start()
{
	savecheck = false; 
	// Load Fx 
	current_animation = &idle_no_check; 

	// Add player collider
	collider = App->colliders->AddCollider({ position.x,position.y, 30, 90 }, COLLIDER_CHECKPOINT, this); 

	return true;
}

bool j1CheckPoint::CleanUp()
{

	return true;
}

bool j1CheckPoint::Update(float dt)
{
	BROFILER_CATEGORY("Updatej1CheckPoint", Profiler::Color::Pink);

	CheckAnimation(dt);

	App->render->Blit(App->entity->checkPoint_graphics, position.x + current_animation->pivotx[current_animation->returnCurrentFrame()], position.y + current_animation->pivoty[current_animation->returnCurrentFrame()], &(current_animation->GetCurrentFrame(dt)), 1.0f);
	
	return true;
}

bool j1CheckPoint::PostUpdate(float dt)
{
	BROFILER_CATEGORY("Postupdatej1CheckPoint", Profiler::Color::HotPink)

		return true;
}

void j1CheckPoint::CheckAnimation(float dt)
{
	if (savecheck == true) {
		current_animation = &idle;
	}
	
}

void j1CheckPoint::OnCollision(Collider* c1, Collider* c2)
{
	
	if (collider == c1 && c2->type == COLLIDER_PLAYER && c1->rect.x <= (c2->rect.x+c2->rect.w+5) && (c1->rect.x+c1->rect.w-5) >= c2->rect.x)
	{
		App->want_save = true;
		App->scene->CheckPoint = true;
		savecheck = true;
	}

}

bool j1CheckPoint::LoadConfigInfo()
{
	// Loading files from config
	pugi::xml_document	config_file;
	pugi::xml_node		config;
	config = App->LoadConfig(config_file);
	config = config.child("checkPoint");


	return true;
}
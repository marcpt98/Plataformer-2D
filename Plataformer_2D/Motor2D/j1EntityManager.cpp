#include "j1App.h"
#include "j1EntityManager.h"
#include "j1Entity.h"
#include<stdio.h>
#include "p2Log.h"

j1EntityManager::j1EntityManager()
{}

j1EntityManager::~j1EntityManager()
{}

bool j1EntityManager::Awake(pugi::xml_node& config)
{
	LOG("Loading Entity");

	bool ret = true;

	

	return ret;
}

bool j1EntityManager::Start()
{
	

	return true;
}

bool j1EntityManager::CleanUp()
{
	

	return true;
}

bool j1EntityManager::Update(float dt)
{
	BROFILER_CATEGORY("UpdateEntity", Profiler::Color::Bisque);



	return true;
}

bool j1EntityManager::PostUpdate(float dt)
{
	BROFILER_CATEGORY("PostupdateEntity", Profiler::Color::Azure)

	

	return true;
}

/*j1Entity* j1EntityManager::CreateEntity(Entity::Types type)
{
	
	return ret;
}*/

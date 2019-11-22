#include "j1App.h"
#include "j1EntityManager.h"
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

	/*accumulated_time += dt;
	if (accumulated_time >= update_ms_cycle)
		do_logic = true;
	UpdateAll(dt, do_logic);
	if (do_logic == true) {
		accumulated_time = 0.0f;
		do_logic = false;
	}*/

	return true;
}

bool j1EntityManager::PostUpdate(float dt)
{
	BROFILER_CATEGORY("PostupdateEntity", Profiler::Color::Azure)

	

	return true;
}

/*Entity* j1EntityManager::CreateEntity(Entity::Types type)
{
	static_assert(Entity::Types::unknown == 5, "code needs update");
	Entity* ret = nullptr;
	switch (type) {
	case Entity::Types::npc: ret = new NPC(); break;
	case Entity::Types::player: ret = new Player(); break;
	}
	if (ret != nullptr)
		entities.push_back(ret);
	return ret;
}*/
#include "j1App.h"
#include "j1EntityManager.h"
#include "j1Entity.h"
#include "j1Player.h"
#include "Enemy_Slime.h"
#include "Enemy_Ghost.h"
#include<stdio.h>
#include "p2Log.h"
#include "j1Textures.h"

j1EntityManager::j1EntityManager()
{
	name.create("entity_manager");
}

j1EntityManager::~j1EntityManager()
{}

bool j1EntityManager::Awake(pugi::xml_node& config)
{
	LOG("Loading EntityManager");

	bool ret = true;

	// Entities spritesheets
	player = config.child("spritesheet_player").attribute("player").as_string("");
	ghost = config.child("spritesheet_ghost").attribute("ghost").as_string("");
	slime = config.child("spritesheet_slime").attribute("slime").as_string("");

	return ret;
}

bool j1EntityManager::Start()
{
	player_graphics = App->tex->Load(player.GetString());
	ghost_graphics = App->tex->Load(ghost.GetString());
	slime_graphics = App->tex->Load(slime.GetString());

	return true;
}

bool j1EntityManager::CleanUp()
{
	p2List_item<j1Entity*>* entities_list = entities.start;

	while (entities_list != nullptr)
	{
		entities_list->data->CleanUp();
		RELEASE(entities_list->data);
		entities_list = entities_list->next;
	}
	entities.clear();

	return true;
}

bool j1EntityManager::Update(float dt)
{
	BROFILER_CATEGORY("UpdateEntity", Profiler::Color::Bisque);

	p2List_item<j1Entity*>* entities_list = entities.start;
	while (entities_list) 
	{
		entities_list->data->Update(dt);
		entities_list = entities_list->next;
	}

	return true;
}

bool j1EntityManager::PostUpdate(float dt)
{
	BROFILER_CATEGORY("PostupdateEntity", Profiler::Color::Azure)

	return true;
}

j1Entity* j1EntityManager::CreateEntity(j1Entity::entityType type, int posx, int posy)
{
	j1Entity* ret = nullptr;

	switch (type) 
	{
	case j1Entity::entityType::PLAYER: ret = new j1Player(posx, posy); break;
	case j1Entity::entityType::FLYING_ENEMY: ret = new Enemy_Ghost(posx, posy); break;
	case j1Entity::entityType::LAND_ENEMY: ret = new Enemy_Slime(posx, posy); break;
	}

	if (ret != nullptr) 
	{
		entities.add(ret);
		entities.end->data->Start();
	}
	return ret;
}

// Save Game State
bool j1EntityManager::save(pugi::xml_node& savegame)
{
	p2List_item<j1Entity*>* entities_list = entities.start;
	while (entities_list) {
		pugi::xml_node entity = savegame.append_child("Entity");
		entities_list->data->save(entity);
		entities_list = entities_list->next;
	}

	return true;
}

// Load Game State
bool j1EntityManager::load(pugi::xml_node& savegame)
{
	CleanUp();

	pugi::xml_node entity;

	for (entity = savegame.child("Entity"); entity; entity = entity.next_sibling("Entity"))
	{
		j1Entity::entityType entity_type;
		p2SString type(entity.attribute("type").as_string());
		if (type == "player")
		{
			entity_type = j1Entity::entityType::PLAYER;
		}
		if (type == "ghost")
		{
			entity_type = j1Entity::entityType::FLYING_ENEMY;
		}
		if (type == "slime")
		{
			entity_type = j1Entity::entityType::LAND_ENEMY;
		}
		CreateEntity(entity_type, entity.child("position").attribute("pos.x").as_int(), entity.child("position").attribute("pos.y").as_int());
	}

	p2List_item<j1Entity*>* entities_list = entities.start;
	while (entities_list) 
	{
		entities_list->data->load(entity);
		entities_list = entities_list->next;
	}

	return true;
}

bool j1EntityManager::DeleteEntity(j1Entity* entity)
{
	entity->CleanUp();
	entities.del(entities.At(entities.find(entity)));

	return true;
}

j1Entity* j1EntityManager::InfoPlayer() {

	p2List_item<j1Entity*>* entitilist = entities.start;
	while (entitilist) {
		if (entitilist->data->name == "player") {
			return entitilist->data;
		}
		entitilist = entitilist->next;
	}
	return NULL;
}
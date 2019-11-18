#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Colliders.h"
#include "j1Player.h"
#include "j1Particles.h"
#include "p2Log.h"
#include "j1Scene.h"
#include "j1Enemy.h"
#include "Enemy_Ghost.h"

#define SPAWN_MARGIN 50

j1Enemy::j1Enemy()
{
	name.create("enemy");
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

// Destructor
j1Enemy::~j1Enemy()
{
}

bool j1Enemy::Awake(pugi::xml_node& config)
{
	bool ret = true;

	LOG("Loading Ghost enemy");
	spritesheetGhost = config.child("spritesheet").attribute("ghost").as_string("");

	return ret;
}


bool j1Enemy::Start()
{
	// Load spritesheet
	graphicsGhost = App->tex->Load(spritesheetGhost.GetString());

	// Enemies
	if (App->scene->currentMap == 0)
	{
		AddEnemy(ENEMY_TYPES::GHOST, 350, 550);
	}
	if (App->scene->currentMap == 1)
	{
		AddEnemy(ENEMY_TYPES::GHOST, 500, 400);
	}

	return true;
}

// Called before quitting
bool j1Enemy::CleanUp()
{
	App->tex->UnLoad(graphicsGhost);
	
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			delete enemies[i];
			enemies[i] = nullptr;
		}
	}

	return true;
}

bool j1Enemy::PreUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type != ENEMY_TYPES::NO_TYPE)
		{
			if (queue[i].x * 1 < App->render->camera.x + (App->render->camera.w * 1) + SPAWN_MARGIN)
			{
				SpawnEnemy(queue[i]);
				queue[i].type = ENEMY_TYPES::NO_TYPE;
			}
		}
	}

	return true;
}

// Called before render is available
bool j1Enemy::Update(float dt)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		if (enemies[i] != nullptr) enemies[i]->Draw(graphicsGhost);
	return true;
}

bool j1Enemy::PostUpdate()
{
	// check camera position to decide what to spawn
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr)
		{
			if (enemies[i]->position.x * 1 < (App->render->camera.x) - SPAWN_MARGIN)
			{
				
				delete enemies[i];
				enemies[i] = nullptr;
			}
		}
	}

	return true;
}

bool j1Enemy::AddEnemy(ENEMY_TYPES type, int x, int y)
{
	bool ret = false;

	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (queue[i].type == ENEMY_TYPES::NO_TYPE)
		{
			queue[i].type = type;
			queue[i].x = x;
			queue[i].y = y;
			ret = true;
			break;
		}
	}

	return ret;
}

void j1Enemy::SpawnEnemy(const EnemyInfo& info)
{
	// find room for the new enemy
	uint i = 0;
	for (;  enemies[i] != nullptr && i < MAX_ENEMIES; ++i);

	if (i != MAX_ENEMIES)
	{
		switch (info.type)
		{
		case ENEMY_TYPES::GHOST:
			enemies[i] = new Enemy_Ghost(info.x, info.y);
			break;
		}
	}
}

void j1Enemy::OnCollision(Collider* c1, Collider* c2)
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
	{
		if (enemies[i] != nullptr && enemies[i]->GetCollider() == c1)
		{
			delete enemies[i];
			enemies[i] = nullptr;

			break;
		}
	}
}

void j1Enemy::Save(pugi::xml_node& data) const
{
	

}

void j1Enemy::Load(pugi::xml_node& data)
{
	
	//position.x = data.child("position").attribute("x").as_int();
	//position.y = data.child("position").attribute("y").as_int();
}




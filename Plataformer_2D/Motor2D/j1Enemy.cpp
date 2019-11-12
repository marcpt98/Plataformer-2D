#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Colliders.h"
#include "j1Player.h"
#include "p2Log.h"
#include "j1Scene.h"
#include "j1Enemy.h"

j1Enemy::j1Enemy()
{
	for (uint i = 0; i < MAX_ENEMIES; ++i)
		enemies[i] = nullptr;
}

// Destructor
j1Enemy::~j1Enemy()
{
}

bool j1Enemy::Start()
{

	

	return true;
}

bool j1Enemy::PreUpdate()
{
	
	return true;
}

// Called before render is available
bool j1Enemy::Update(float dt)
{
	return true;
}

bool j1Enemy::PostUpdate()
{
	return true;
}

// Called before quitting
bool j1Enemy::CleanUp()
{
	return true;
}

bool j1Enemy::AddEnemy(ENEMY_TYPES type, int x, int y)
{
	bool ret = false;


	return ret;
}

void j1Enemy::SpawnEnemy(const EnemyInfo& info)
{
	
	
}

void j1Enemy::OnCollision(Collider* c1, Collider* c2)
{
	
}

void j1Enemy::Save(pugi::xml_node& data) const
{
	

}

void j1Enemy::Load(pugi::xml_node& data)
{
	/*
	position.x = data.child("position").attribute("x").as_int();
	position.y = data.child("position").attribute("y").as_int();*/
}




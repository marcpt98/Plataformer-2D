#ifndef __j1Enemy_H__
#define __j1Enemy_H__

#include "j1Module.h"
#define MAX_ENEMIES 10

enum ENEMY_TYPES
{
	NO_TYPE,
	FLYING,
	GROUND,	
};

class Enemy;

struct EnemyInfo
{
	ENEMY_TYPES type = ENEMY_TYPES::NO_TYPE;
	int x, y;
};

class j1Enemy : public j1Module
{
public:

	j1Enemy();
	~j1Enemy();

	bool Start();
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();
	bool CleanUp();
	void OnCollision(Collider* c1, Collider* c2);
	bool AddEnemy(ENEMY_TYPES type, int x, int y);
	void j1Enemy::Save(pugi::xml_node& data)const;
	void j1Enemy::Load(pugi::xml_node& data);
private:

	void SpawnEnemy(const EnemyInfo& info);

private:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
};



#endif // __j1Enemy_H__
#ifndef __j1Enemy_H__
#define __j1Enemy_H__

#include "j1Module.h"
#include "Enemy_Ghost.h"

#define MAX_ENEMIES 10

enum ENEMY_TYPES
{
	NO_TYPE,
	GHOST,
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

	// Destructor
	~j1Enemy();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before quitting
	bool CleanUp();

	// Called before each loop iteration
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Collisions
	void OnCollision(Collider* c1, Collider* c2);
	
	// Add enemy
	bool AddEnemy(ENEMY_TYPES type, int x, int y);

	// Save and load enemy state
	void j1Enemy::Save(pugi::xml_node& data)const;
	void j1Enemy::Load(pugi::xml_node& data);
private:
	// Add an enemy
	void SpawnEnemy(const EnemyInfo& info);

private:

	EnemyInfo queue[MAX_ENEMIES];
	Enemy* enemies[MAX_ENEMIES];
	p2SString spritesheetGhost;
	SDL_Texture* graphicsGhost;
};



#endif // __j1Enemy_H__
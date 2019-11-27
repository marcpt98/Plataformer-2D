#ifndef __ENEMY_GHOST_H__
#define __ENEMY_GHOST_H__

#include "j1Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include "j1Entity.h"

struct SDL_Texture;
struct Collider;

enum states_ghost
{
	ST_GHOST_IDLE,
	ST_GHOST_FOLLOW,
	ST_GHOST_DEAD
};

class Enemy_Ghost : public j1Entity
{
public:
	Enemy_Ghost(int posx, int posy);

	// Destructor
	~Enemy_Ghost();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate(float dt);

	// Called before quitting
	bool CleanUp();

	// Check ghost animation
	void CheckAnimation(float dt);

	// Load all config info
	bool LoadConfigInfo();
	
	// Collisions
	void OnCollision(Collider* c1, Collider* c2);

	// Pathfinding
	void Pathfinding(float dt);

public:
	// Size
	int ghost_width;
	int ghost_high;

	// Animations
	states_ghost	actualState;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation follow;
	Animation dead;
	bool ghost_dead = false;

	// Blit
	bool blit = false;
	int fixBlit;

	// Speed
	float speed;

	// Dead
	bool count_ghost_dead = false;
	int dead_ghost_animation_finish;
	int deadGhostDelay;

};

#endif // __ENEMY_GHOST_H__

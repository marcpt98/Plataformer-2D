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
	
	// Collisions
	void OnCollision(Collider* c1, Collider* c2);

	// Pathfinding
	void Pathfinding(float dt);

public:
	int ghost_width = 40;
	int ghost_high = 53;

	// Animations
	states_ghost	actualState;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation follow;
	Animation dead;
	bool ghost_dead = false;

	// Blit
	bool blit = false;
	int fixBlit = 40;

	// Speed
	float speed = 3;

	// Dead
	bool count_ghost_dead = false;
	int dead_ghost_animation_finish = 0;
	int deadGhostDelay = 800;
};

#endif // __ENEMY_GHOST_H__

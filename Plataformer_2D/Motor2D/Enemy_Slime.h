#ifndef __ENEMY_SLIME_H__
#define __ENEMY_SLIME_H__

#include "j1Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include "j1Entity.h"


struct SDL_Texture;
struct Collider;

enum states_slime
{
	ST_SLIME_IDLE,
	ST_SLIME_FOLLOW,
	ST_SLIME_DEAD
};

class Enemy_Slime: public j1Entity
{
public:
	Enemy_Slime(int posx, int posy);

	// Destructor
	~Enemy_Slime();

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
	states_slime actualState;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation follow;
	Animation dead;
	bool slime_dead = false;

	// Blit
	bool blit = false;
	int fixBlit = 40;

	// Speed
	float speed = 3;

	// Dead
	bool count_slime_dead = false;
	int dead_slime_animation_finish = 0;
	int deadSlimeDelay = 800;
};


#endif // __ENEMY_SLIME_H__

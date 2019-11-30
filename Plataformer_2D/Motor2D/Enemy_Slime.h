#ifndef __ENEMY_SLIME_H__
#define __ENEMY_SLIME_H__

#include "j1Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include "j1Entity.h"

#define VELOCITY 60

struct SDL_Texture;
struct Collider;

enum states_slime
{
	ST_SLIME_IDLE,
	ST_SLIME_FOLLOW_Forward,
	ST_SLIME_FOLLOW_Backward,
	ST_SLIME_FOLLOW_Down,
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

	// Check slime animation
	void CheckAnimation(float dt);

	// Load all config info
	bool LoadConfigInfo();

	// Collisions
	void OnCollision(Collider* c1, Collider* c2);

	// Pathfinding
	void Pathfinding(float dt);
	void Follow_path(float dt);

public:
	// Size
	int slime_width;
	int slime_high;
	
	// Gravity
	float gravity;

	// Animations
	states_slime actualState;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation follow;
	Animation dead;
	bool slime_dead = false;

	// Blit
	bool blit = false;
	int fixBlit;

	// Speed
	float speed;

	// Dead
	bool count_slime_dead = false;
	int dead_slime_animation_finish;
	int deadSlimeDelay;

	//Pathfinding
	p2SString debug_tex;
	SDL_Texture* graphics_debug_tex;
	int x;
	int y;
	iPoint p;
	iPoint origin;
	iPoint pos;
	const p2DynArray<iPoint>* lastpath;
	const p2DynArray<iPoint>* path;

	// Slime idle
	int start = 0;
};


#endif // __ENEMY_SLIME_H__

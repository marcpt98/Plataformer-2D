#ifndef __j1Player_H__
#define __j1Player_H__

#include "j1Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "p2DynArray.h"


struct SDL_Texture;
struct Collider;

enum states
{
	ST_IDLE,
	ST_RUN,
	ST_JUMP,
	ST_JUMPRUN,
	ST_FALL
};

class j1Player : public j1Module
{
public:
	
	j1Player();
	
	// Destructor
	~j1Player();

	// Called before render is available
	bool Awake(pugi::xml_node& config);
	
	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate(float dt);

	// Called before quitting
	bool CleanUp();

	// Collisions
	void OnCollision(Collider* c1, Collider* c2);

public:
	SDL_Texture* graphics = nullptr;
	iPoint position;
	
	// Animations
	p2SString spritesheet;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation run;
	Animation jump;
	Animation special;
	
	// Colliders
	Collider* collider = nullptr;
	Collider* collider2 = nullptr;
	bool showcolliders = false;

	// Gravity
	float gravity;

	// Speed
	float speed;

	// Jump force
	bool canJump1 = false;
	float jumpF;
	float energyJump;
	
	// Stats machine
	void CheckInputState();
	void CheckAnimation();
	states	actualState;
	
	// Player blit
	bool	blit = false;	
	int		fixBlit;

	// God mode
	bool godMode = false;


};

#endif // __j1Player_H__
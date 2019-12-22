#ifndef __j1Coins_H__
#define __j1Coins_H__

#include "j1Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include "j1Entity.h"

struct SDL_Texture;
struct Collider;


enum Coin_states
{
	ST_FLYING,
	ST_DYING
};

class j1Coins : public j1Entity
{
public:

	j1Coins(int posx, int posy);

	// Destructor
	~j1Coins();

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

	// Load all config info
	bool LoadConfigInfo();

	//State machine
	void CheckAnimation(float dt);

public:
	Coin_states actualState;

	//Animations
	Animation* current_animation = nullptr;
	Animation idle;

};

#endif // __j1Coins_H__
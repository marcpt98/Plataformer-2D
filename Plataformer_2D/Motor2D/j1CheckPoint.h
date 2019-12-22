#ifndef __j1CheckPoint_H__
#define __j1CheckPoint_H__

#include "j1Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include "j1Entity.h"

struct SDL_Texture;
struct Collider;

enum CheckPoint_states
{
	ST_NO_CHECK,
	ST_CHECK
};

class j1CheckPoint : public j1Entity
{
public:

	j1CheckPoint(int posx, int posy);

	// Destructor
	~j1CheckPoint();

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
	CheckPoint_states actualState;
	bool savecheck; 
	bool savefx = false;

	//Animations
	Animation* current_animation = nullptr;
	Animation idle;
	Animation idle_no_check;
};

#endif // __j1CheckPoint_H__
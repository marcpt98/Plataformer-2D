#ifndef __j1Player_H__
#define __j1Player_H__

#include "j1Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "p2DynArray.h"


struct SDL_Texture;
struct Collider;

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
	int initial_x_position = 200;
	int initial_y_position = 530;

	SDL_Texture* graphics = nullptr;
	iPoint position;
	
	// Animations
	p2SString spritesheet;
	Animation* current_animation = nullptr;
	Animation idle;
	
	// Colliders
	Collider* collider = nullptr;
	Collider* collider2 = nullptr;
};

#endif // __j1Player_H__
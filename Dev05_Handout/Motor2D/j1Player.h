#ifndef __j1Player_H__
#define __j1Player_H__

#include "j1Module.h"
//#include "Animation.h"
#include "p2Point.h"
#include "p2DynArray.h"

class j1Player : public j1Module
{
public:
	j1Player();
	~j1Player();

	bool Start();
	bool Update(float dt);
	bool PostUpdate(float dt);
	bool CleanUp();
public:

	SDL_Texture* graphics = nullptr;
	iPoint position;
};

#endif // __j1Player_H__
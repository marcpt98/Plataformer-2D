#ifndef __j1EntityManager_H__
#define __j1EntityManager_H__

#include "PugiXml/src/pugixml.hpp"
#include "j1Module.h"
#include "p2List.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include "j1Entity.h"

struct SDL_Texture;
struct Collider;

enum class Types
{
	PLAYER,
	ENEMY,
	UNKNOWN
};

class j1EntityManager : public j1Module
{
public:

	j1EntityManager();

	// Destructor
	~j1EntityManager();

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

public:
	p2List<j1Entity*> entities;
	pugi::xml_node node;
	SDL_Texture* player = nullptr;
	SDL_Texture* ghost = nullptr;
	
};
#endif // __j1EntityManager_H__
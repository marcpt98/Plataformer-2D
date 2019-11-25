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

enum class entityType
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

	// Create a new entity
	j1Entity* CreateEntity(j1Entity::entityType type, int posx = 0, int posy = 0);

	// Save and load position
	bool save(pugi::xml_node& data);
	bool load(pugi::xml_node& data);

public:
	// Load entities textures
	p2SString player;
	SDL_Texture* player_graphics;

	p2SString ghost;
	SDL_Texture* ghost_graphics;

	p2SString slime;
	SDL_Texture* slime_graphics;

	p2List<j1Entity*> entities;
};
#endif // __j1EntityManager_H__
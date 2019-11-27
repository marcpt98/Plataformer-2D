#ifndef __j1Entity_H__
#define __j1Entity_H__

#include "p2Point.h"
#include "Animation.h"
#include "p2Log.h"
#include "j1App.h"

class j1Entity : public j1Module
{

public:

	enum entityType
	{
		NO_TYPE,
		PLAYER,
		FLYING_ENEMY,
		LAND_ENEMY,
	};

	entityType type;

	j1Entity(entityType type);

	~j1Entity();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before quitting
	bool CleanUp();

	// Save and load position
	bool save(pugi::xml_node& data);

public:
	// Player
	iPoint position;
	iPoint lasPosition;
	Collider* collider = nullptr;
	bool player_godMode = false;

	// Colliders
	bool to_delete;
};

#endif // __j1Entity_H__

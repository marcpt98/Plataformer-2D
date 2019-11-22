#ifndef __j1Entity_H__
#define __j1Entity_H__

#include "p2Point.h"
#include "Animation.h"
#include "p2Log.h"
#include "j1App.h"

class j1Entity : public j1Module
{

public:

	enum Types
	{
		NO_TYPE,
		PLAYER,
		FLYING_ENEMY,
		LAND_ENEMY,
	};

	Types type;

	j1Entity(Types type);

	~j1Entity();

	// Called before quitting
	bool CleanUp();

	// Save and load position
	bool save(pugi::xml_node& data);
	bool load(pugi::xml_node& data);

public:
	iPoint position;
	bool to_delete = false;

};

#endif // __j1Entity_H__

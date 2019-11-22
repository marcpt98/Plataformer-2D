#ifndef __j1EntityManager_H__
#define __j1EntityManager_H__

#include "j1Module.h"
#include "p2Point.h"
#include "p2DynArray.h"

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
	
};





#endif // __j1EntityManager_H__

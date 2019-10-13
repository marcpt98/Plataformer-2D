#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;

// Different maps that the game can load
enum MapNames
{
	hello3 = 0,
	hello4 = 1
};


class j1Scene : public j1Module
{
public:

	j1Scene();

	// Destructor
	virtual ~j1Scene();

	// Called before render is available
	bool Awake(pugi::xml_node& config);

	// Called before the first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Say which map has to be loaded
	bool LevelName(int time);


	p2List<p2SString*> map_names;
	int currentMap;

private:
};

#endif // __j1SCENE_H__
#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"

struct SDL_Texture;

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

	// Say which map and music has to be loaded
	bool LevelName(int time);

	// Create entities when level loads
	bool createEntities();

	// Save and Load
	bool load(pugi::xml_node&);
	bool save(pugi::xml_node&);

	p2List<p2SString*> map_names;
	int currentMap;
	p2List<p2SString*> music_names;
	
	bool lowfps = false;
	bool canbehighfps = false;
	bool highfps = false;
	
	// Player
	bool player_map_next = false;
	bool player_dead = false;

	// Maps and music
	p2SString* map_1 = nullptr;
	p2SString* map_2 = nullptr;
	p2SString* music_1 = nullptr;
	p2SString* music_2 = nullptr;
};

#endif // __j1SCENE_H__
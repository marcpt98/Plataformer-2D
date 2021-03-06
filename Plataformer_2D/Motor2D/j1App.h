#ifndef __j1APP_H__
#define __j1APP_H__

#include "p2List.h"
#include "j1Module.h"
#include "j1PerfTimer.h"
#include "j1Timer.h"
#include "Brofiler/Brofiler.h"
#include "PugiXml\src\pugixml.hpp"

// Modules
class j1Window;
class j1Input;
class j1Render;
class j1Textures;
class j1Audio;
class j1FadeToBlack;
class j1Scene;
class j1Map;
class j1Colliders;
class j1Particles;
class j1PathFinding;
class j1EntityManager;
class j1Entity;
class j1Fonts;
class j1Gui;
class j1SceneUI;
class j1Console;

class j1App
{
public:

	// Constructor
	j1App(int argc, char* args[]);

	// Destructor
	virtual ~j1App();

	// Called before render is available
	bool Awake();

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update();

	// Called before quitting
	bool CleanUp();

	// Add a new module to handle
	void AddModule(j1Module* module);

	// Exposing some properties for reading
	int GetArgc() const;
	const char* GetArgv(int index) const;
	const char* GetTitle() const;
	const char* GetOrganization() const;

	// Load config file
	pugi::xml_node LoadConfig(pugi::xml_document&) const;

private:
	// Call modules before each loop iteration
	void PrepareUpdate();

	// Call modules before each loop iteration
	void FinishUpdate();

	// Call modules before each loop iteration
	bool PreUpdate();

	// Call modules on each loop iteration
	bool DoUpdate();

	// Call modules after each loop iteration
	bool PostUpdate();

public:

	// Modules
	j1Window*			win;
	j1Input*			input;
	j1Render*			render;
	j1Textures*			tex;
	j1Audio*			audio;
	j1FadeToBlack*		fade;
	j1Scene*			scene;
	j1Map*				map;
	j1Colliders*		colliders;
	j1Particles*		particles;
	j1PathFinding*		path;
	j1EntityManager*	entity;
	j1Fonts*			font;
	j1Gui*				gui;
	j1SceneUI*			sceneui;
	j1Console*			console;

private:

	p2List<j1Module*>	modules;
	uint				frames;
	
	int					argc;
	char**				args;

	p2SString			title;
	p2SString			organization;
public:
	// Save and load
	bool	want_save = false;
	bool	want_load = false;
	pugi::xml_document save_game_doc;
	pugi::xml_node save_game_nod;
	bool load();
	bool save();
	bool LoadSaveGame();

	j1PerfTimer			ptimer;
	j1PerfTimer			timewaits;
	uint64				frame_count = 0;
	j1Timer				startup_time;
	j1Timer				frame_time;
	j1Timer				last_sec_frame_time;
	uint32				last_sec_frame_count = 0u;
	uint32				prev_last_sec_frame_count = 0u;
	uint32				framerate30 = 0u;
	uint32				framerate60 = 0u;
	uint32				framerate = 0u;
	float				dt;
	
};

extern j1App* App; // No student is asking me about that ... odd :-S

#endif
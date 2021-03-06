#ifndef __j1SCENE_H__
#define __j1SCENE_H__

#include "j1Module.h"
#include "UI_element.h"

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

	// Preparing scene intro
	bool PrepSceneIntro();

	// Create entities when level loads
	bool createEntities();

	// Save and Load
	bool load(pugi::xml_node&);
	bool save(pugi::xml_node&);

	//Ui events
	//bool OnUIEvent(UI_element* element, event_type event_type);

public:
	p2List<p2SString*> map_names;
	int currentMap;
	int introMap;
	p2List<p2SString*> music_names;
	
	bool lowfps = false;
	bool canbehighfps = false;
	bool highfps = false;
	
	// Player
	bool player_map_next = false;
	bool player_dead = false;
	bool firsttime = false;
	int player_score;
	int last_player_score;
	int timer_pts;
	bool diferent_coins = false;
	int timer_coins;
	int score_lives = 0;
	bool more_lives = false;

	// Maps and music
	p2SString* map_1 = nullptr;
	p2SString* map_2 = nullptr;
	p2SString* music_1 = nullptr;
	p2SString* music_2 = nullptr;
	p2SString* music_scene_intro = nullptr;

	bool CheckPoint = false;
	bool pause = false;

	bool sceneintro = true;
	int lives = 0;

	int timertime = 0;
	uint timer = 0;
	//UI_text* time_text;

	UI_text* score = nullptr;
	bool diferent_score = false;
	int coin_number = 0;
	UI_text* coin_counter = nullptr;
private:
	// Pathfinding
	SDL_Texture* debug_tex;	
};

#endif // __j1SCENE_H__
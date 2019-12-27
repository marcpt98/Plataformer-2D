#ifndef __j1SCENE_UI_H__
#define __j1SCENE_UI_H__

#include "j1Module.h"
#include "p2List.h"

class j1SceneUI :public j1Module
{
public:
	j1SceneUI();

	// Destructor
	virtual ~j1SceneUI();

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	bool OnUIEvent(UI_element* element, event_type event_type);

	// Add UI menus
	bool Addsceneintro_UI();
	bool Addingame_UI();
	bool Addpause_UI();
	bool Addsettings_UI();
	bool Addcredits_UI();
	bool Addlicence_UI();
	
	// Delete UI menus
	bool Deletesceneintro_UI();
	bool Deleteingame_UI();
	bool Deletepause_UI();
	bool Deletesettings_UI();
	bool Deletecredits_UI();
	bool Deletelicence_UI();

	// Extra
	bool back_intro_UI();
	bool delete_intro_UI();
	bool createtimelives();
	bool deletetimelives();

public:
	// Scene Intro
	UI_image* background = nullptr;
	UI_image* title = nullptr;
	UI_button* play_button = nullptr;
	UI_button* load_button = nullptr;
	UI_button* settings_button = nullptr;
	UI_button* credits_button = nullptr;
	UI_button* webpage_button = nullptr;
	UI_button* exit_button = nullptr;
	bool exit = false;

	// Settings
	UI_window* window_settings = nullptr;
	UI_element* music = nullptr;
	UI_element* fx = nullptr;
	UI_element* cap = nullptr;
	UI_button* exit_settings = nullptr;

	// Credits
	UI_window* window_credits = nullptr;
	UI_button* exit_credits = nullptr;
	UI_text* text_1 = nullptr;
	UI_text* text_2 = nullptr;
	UI_text* text_3 = nullptr;
	UI_text* text_4 = nullptr;
	UI_button* licence_button = nullptr;
	
	// Licence
	UI_window* window_licence = nullptr;
	UI_button* exit_licence = nullptr;
	UI_text* text_5 = nullptr;
	UI_image* licence = nullptr;

	// In game
	UI_image* player_face1 = nullptr;
	UI_image* player_face2 = nullptr;
	UI_image* player_face3 = nullptr;
	UI_image* sand = nullptr;
	UI_image* time_1 = nullptr;
	UI_image* time_2 = nullptr;
	UI_image* time_3 = nullptr;
	UI_image* time_4 = nullptr;
	UI_image* time_5 = nullptr;
	UI_image* time_6 = nullptr;
	UI_image* time_7 = nullptr;
	UI_image* time_8 = nullptr;
	UI_image* time_9 = nullptr;
	UI_image* time_10 = nullptr;

	// Pause
	bool pause_UI = false;
	UI_window* window_pause = nullptr;
	UI_button* save_button = nullptr;
	UI_button* exit_pause = nullptr;
	UI_button* load_ingame = nullptr;
	UI_button* settings_ingame = nullptr;
	UI_button* exit_intro = nullptr;
};

#endif // __j1SCENE_UI_H__

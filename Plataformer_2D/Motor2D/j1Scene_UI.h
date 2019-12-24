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

public:
	// Scene Intro
	UI_element* background;
	UI_element* title;
	UI_element* play_button;
	UI_element* load_button;
	UI_element* settings_button;
	UI_element* credits_button;
	UI_element* exit_button;
	bool exit = false;
	

	// In game
	UI_element* live1;
	UI_element* live2;

	// Settings
	UI_element* window_settings;
	UI_element* music;
	UI_element* fx;
	UI_element* cap;
	UI_element* exit_settings;

	// Credits
	UI_element* window_credits;
	UI_element* exit_credits;
	UI_element* text_1;
	UI_element* text_2;
	UI_element* text_3;
	UI_element* text_4;
	UI_element* text_5;
	UI_element* licence_button;
	
	// Licence
	UI_element* window_licence;
	UI_element* exit_licence;
	UI_element* text_6;
	UI_element* text_7;
	UI_element* text_8;
	UI_element* text_9;
	UI_element* text_10;
	UI_element* text_11;
	UI_element* text_12;
	UI_element* text_13;
	UI_element* text_14;
	UI_element* text_15;
	UI_element* text_16;
	UI_element* text_17;
	UI_element* text_18;
	UI_element* text_19;
	UI_element* text_20;
	UI_element* text_21;

	// Pause
	UI_element* live3;
};

#endif // __j1SCENE_UI_H__

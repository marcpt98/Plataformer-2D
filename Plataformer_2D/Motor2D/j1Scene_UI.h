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
	
	// Delete UI menus
	bool Deletesceneintro_UI();
	bool Deleteingame_UI();
	bool Deletepause_UI();

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

	// Pause
	UI_element* live3;
};

#endif // __j1SCENE_UI_H__

#ifndef __j1SCENE_UI_H__
#define __j1SCENE_UI_H__

#include "j1Module.h"
#include "p2List.h"

class UI_ingame;

enum UI_types
{
	MENU_INGAME,
	MENU_PAUSE
};

struct UI
{
	UI(UI_types id) : id(id)
	{}

	p2List<UI_element*> elements;
	UI_types id;
};

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

	// UI menus
	UI_ingame* Addingame_UI();

public:
	p2List<UI*> UI_type;
};

#endif // __j1SCENE_UI_H__

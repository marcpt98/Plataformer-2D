#ifndef __UI_ELEMENT__
#define __UI_ELEMENT__

#include "j1Module.h"
#include "p2Point.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Gui.h"

struct SDL_Texture;

enum element_type
{
	TEXT,
	IMAGE,
	BUTTON,
	WINDOW,
	SLIDER,
	INPUTBOX
};

enum UI_element_state
{
	STANDBY,
	MOUSEOVER,
	CLICKED,
};

enum UI_element_action
{
	START,
	LOAD,
	LOAD_INGAME,
	SAVE,
	SETTINGS,
	SETTINGS_INGAME,
	EXIT_SETTINGS_INGAME,
	CREDITS,
	EXIT,
	EXIT_SETTINGS,
	EXIT_CREDITS,
	LICENCE,
	EXIT_LICENCE,
	EXIT_PAUSE,
	EXIT_MENU,
	WEBPAGE,
	SLIDER_BUTTON,
	SLIDER_FX_BUTTON,
	SLIDER_BAR,
	CAP
};

class UI_element :public j1Module
{
public:

	UI_element()
	{}

	UI_element(int x, int y, element_type type, SDL_Rect section, j1Module* callback, SDL_Texture* texture = nullptr) : localPosition({ x, y }), element_type(type), section(section), callback(callback), texture(texture)
	{}

	virtual ~UI_element()
	{
		if (texture != nullptr && texture != App->gui->GetAtlas())
		{
			App->tex->UnLoad(texture);
			texture = nullptr;
		}
	}

	virtual void setOutlined(bool isOutlined)
	{}

	iPoint calculateAbsolutePosition() const
	{
		if (parent != nullptr)
			return (localPosition + parent->calculateAbsolutePosition());
		else
			return localPosition;
	}

	virtual void BlitElement()
	{}

public:
	int positionwow;
	SDL_Texture* texture = nullptr;
	iPoint localPosition;
	SDL_Rect section;
	element_type element_type;
	UI_element_action element_action;
	j1Module* callback = nullptr;
	UI_element* parent = nullptr;
	bool hovering = false;
	UI_element_state state = STANDBY;
};

#endif // !__UI_ELEMENT__

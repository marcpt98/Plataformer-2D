#ifndef __UI_BUTTON__
#define __UI_BUTTON__
#include "UI_element.h"
#include "UI_Text.h"

enum button_type
{
	LINK,
	CHECKBOX
};

class UI_button : public UI_element
{
public:

	UI_button()
	{}

	UI_button(int x, int y, SDL_Texture* texture, SDL_Rect standby, SDL_Rect OnMouse, SDL_Rect OnClick, button_type type, j1Module* callback) : UI_element(x, y, element_type::BUTTON, standby, callback, texture),
		OnMouse(OnMouse),
		Tick(OnMouse),
		OnClick(OnClick),
		type(type),
		trala(x)
	{
	}

	~UI_button()
	{}

	void BlitElement();
	void ChangeVolume();
public:

	SDL_Rect OnMouse;
	SDL_Rect Tick;
	SDL_Rect OnClick;
	button_type type = LINK;
	bool tick = false;
	bool clicked = false;
	int newposition = 0;
	int save_position = 0;
	int trala;
	int x, y;
	float musicvolume = 0;
	float fxvolume = 0;
};


#endif // __UI_BUTTON__


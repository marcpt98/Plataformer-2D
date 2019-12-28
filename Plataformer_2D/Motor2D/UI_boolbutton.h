#ifndef __UI_BOOLBUTTON__
#define __UI_BOOLBUTTON__
#include "UI_element.h"

class UI_boolbutton : public UI_element
{
public:

	UI_boolbutton()
	{}

	UI_boolbutton(int x, int y, SDL_Texture* texture, SDL_Rect booltrue, SDL_Rect boolfalse, j1Module* callback) : UI_element(x, y, element_type::BUTTON, boolfalse, callback, texture),
		boolfalse(boolfalse),
		booltrue(booltrue)
	{}

	~UI_boolbutton()
	{}

	void BlitElement();

public:

	UI_text* text = nullptr;
	SDL_Rect booltrue;
	SDL_Rect boolfalse;
};


#endif // __UI_BUTTON__




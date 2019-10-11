#ifndef __J1FADETOBLACK_H__
#define __J1FADETOBLACK_H__

#include "j1Module.h"
#include "SDL\include\SDL_rect.h"

class j1FadeToBlack : public j1Module
{
public:
	j1FadeToBlack();
	~j1FadeToBlack();

	bool Start();
	bool Update();
	bool FadeToBlack(pugi::xml_document	map_off, pugi::xml_document	map_on, float time = 2.0f);

private:

	enum fade_step
	{
		none,
		fade_to_black,
		fade_from_black
	} current_step = fade_step::none;

	Uint32 start_time = 0;
	Uint32 total_time = 0;
	SDL_Rect screen;

	pugi::xml_document*	off_map = nullptr;
	pugi::xml_document* on_map = nullptr;
};

#endif //__J1FADETOBLACK_H__

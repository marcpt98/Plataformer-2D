#ifndef  _MODULE_FADETOBLACK_
#define _MODULE_FADETOBLACK_

#include "j1Module.h"
#include "SDL\include\SDL_rect.h"

enum ListOfMapNames;

class j1FadeToBlack : public j1Module
{
public:

	j1FadeToBlack();

	// Destructor
	virtual ~j1FadeToBlack();

	// Called before render is avalible
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

	// FadeToBlack
	bool FadeToBlack(float time);

private:


public:

private:
	enum fade_step
	{
		none,
		fade_to_black,
		fade_from_black
	} current_step = fade_step::none;


	uint start_time = 0;
	uint total_time = 0;
	SDL_Rect screen;
};
#endif // _MODULE_FADETOBLACK_

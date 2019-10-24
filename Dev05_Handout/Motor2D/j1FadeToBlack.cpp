#include <math.h>
#include "p2Log.h"
#include "j1App.h"
#include "j1FadeToBlack.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Map.h"
#include "j1Window.h"
#include "SDL/include/SDL_render.h"
#include "SDL/include/SDL_timer.h"

// Constructor
j1FadeToBlack::j1FadeToBlack()
{
	name.create("fadetoblack");
}

// Destructor
j1FadeToBlack::~j1FadeToBlack()
{}

bool j1FadeToBlack::Awake(pugi::xml_node&)
{
	bool ret = true;

	screen = { 0, 0, App->win->width * App->win->scale, App->win->height * App->win->scale };

	return ret;
}

// Load assets
bool j1FadeToBlack::Start()
{
	LOG("Preparing Fade Screen");
	SDL_SetRenderDrawBlendMode(App->render->renderer, SDL_BLENDMODE_BLEND);
	return true;
}

// Update: draw background
bool j1FadeToBlack::Update(float dt)
{
	if (current_step == fade_step::none)
		return true;
	Uint32 now = SDL_GetTicks() - start_time;
	float normalized = MIN(1.0f, (float)now / (float)total_time);

	switch (current_step)
	{
		case fade_step::fade_to_black:
		{
			if (now >= total_time)
			{
				total_time += total_time;
				start_time = SDL_GetTicks();
				current_step = fade_step::fade_from_black;
			}
	} break;
	
		case fade_step::fade_from_black:
		{
			normalized = 1.0f - normalized;
	
			if (now >= total_time)
				current_step = fade_step::none;
		} break;
	}

	// Finally render the black square with alpha on the screen
	SDL_SetRenderDrawColor(App->render->renderer, 0, 0, 0, (Uint8)(normalized * 255.0f));
	SDL_RenderFillRect(App->render->renderer, &screen);

	return true;
}

// Fade to black. At mid point deactivate one module, then activate the other
bool j1FadeToBlack::FadeToBlack(float time)
{
	bool ret = false;
	
	if (current_step == fade_step::none)
	{
		current_step = fade_step::fade_to_black;
		start_time = SDL_GetTicks();
		total_time = (Uint32)(time * 0.5f * 1000.0f);
		ret = true;
	}

	return ret;
}

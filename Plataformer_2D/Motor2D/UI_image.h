#ifndef __UI_IMAGE__

#include "UI_element.h"

struct SDL_Rect;

class UI_image : public UI_element
{
public:

	UI_image()
	{}

	UI_image(SDL_Texture* texture, int x, int y, SDL_Rect section, j1Module* callback) : UI_element(x, y, element_type::IMAGE, section, callback, texture)
	{}

	~UI_image()
	{}

	void BlitElement();

};

#endif // !__UI_IMAGE__

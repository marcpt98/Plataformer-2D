#ifndef __UI_SLIDER__

#include "UI_element.h"


struct SDL_Rect;

class UI_slider : public UI_element
{
public:

	UI_slider()
	{}

	UI_slider(int x, int y, SDL_Texture* texture,UI_button* button, j1Module* callback, SDL_Rect image_bar) : UI_element(x, y, element_type::SLIDER , image_bar, callback, texture),
		image_bar(image_bar),
		slider_button(button)
	{
	}
	~UI_slider()
	{}

	void setOutlined(bool isOutlined);
	void BlitElement();
	void ChangeVolume();
private:
	
public:

	UI_text* text = nullptr;
	SDL_Rect OnMouse;
	SDL_Rect Tick;
	SDL_Rect OnClick;
	SDL_Rect image_bar;
	UI_button* slider_button = nullptr;
	int position = 394;
	int x, y;
};

#endif // __UI_IMAGE__

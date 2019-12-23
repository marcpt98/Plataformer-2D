#ifndef __UI_TEXT__
#define __UI_TEXT__

#include "UI_element.h"
#include "SDL/include/SDL_pixels.h"

struct _TTF_Font;

class UI_text : public UI_element
{
public:

	UI_text()
	{}

	UI_text(char* text, int x, int y, _TTF_Font* font, SDL_Color color, j1Module* callback) : UI_element(x, y, element_type::TEXT, { 0, 0, 0, 0 }, callback, nullptr),
		text(text),
		font(font),
		color(color)
	{
		createTexture();
	}

	~UI_text();

	void createTexture();
	void setColor(SDL_Color newColor);

	p2SString getText() const;
	void setText(const char* string);
	void setText(const p2SString string);

	void BlitElement();

public:

	SDL_Color color;
	uint tex_width;
	uint tex_height;

private:

	p2SString text = nullptr;
	_TTF_Font* font = nullptr;
};

#endif // __UI_TEXT__

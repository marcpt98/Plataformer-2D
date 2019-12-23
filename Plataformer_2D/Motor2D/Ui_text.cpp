#include "UI_Text.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Render.h"

UI_text::~UI_text()
{}

void UI_text::createTexture()
{
	if (texture != nullptr)
	{
		App->tex->UnLoad(texture);
		texture = nullptr;
	}

	texture = App->font->Print(text.GetString(), color, font);
	App->tex->GetSize(texture, tex_width, tex_height);
	section.w = tex_width;
	section.h = tex_height;
}

void UI_text::setColor(SDL_Color newColor)
{
	color = newColor;
	createTexture();
}

void UI_text::BlitElement()
{
	iPoint globalPos = calculateAbsolutePosition();

	App->render->Blit(texture, globalPos.x, globalPos.y, NULL, false);
}

p2SString UI_text::getText() const
{
	return text;
}

void UI_text::setText(const char* string)
{
	text = string;
	createTexture();
}

void UI_text::setText(const p2SString string)
{
	text = string;
	createTexture();
}
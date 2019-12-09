#include "UI_Text.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Render.h"

UI_text::~UI_text()
{
	if (outline != nullptr)
	{
		App->tex->UnLoad(outline);
		outline = nullptr;
	}
}

void UI_text::createTexture()
{
	if (texture != nullptr)
	{
		App->tex->UnLoad(texture);
		texture = nullptr;
	}
	if (outline != nullptr)
	{
		App->tex->UnLoad(outline);
		outline = nullptr;
	}

	uint outline_width, outline_height;
	if (outlined)
	{
		
		outline = App->font->Print(text.GetString(), outline_color, font); //Outlined texture
		App->tex->GetSize(outline, outline_width, outline_height);
	}


	texture = App->font->Print(text.GetString(), color, font); //Normal texture
	App->tex->GetSize(texture, tex_width, tex_height);
	section.w = tex_width;
	section.h = tex_height;

	if (outlined)
	{
		outline_offset.x = tex_width - outline_width;
		outline_offset.x /= 2;
		outline_offset.y = outline_offset.x;
	}

}

void UI_text::setColor(SDL_Color newColor)
{
	color = newColor;
	createTexture();
}

void UI_text::setOutlineColor(SDL_Color newColor)
{
	outline_color = newColor;
	if (outlined)
		createTexture();
}

void UI_text::BlitElement()
{
	iPoint globalPos = calculateAbsolutePosition();

	if (outlined)
		App->render->Blit(outline, globalPos.x + outline_offset.x, globalPos.y + outline_offset.y, NULL, false, 0.5f);
	App->render->Blit(texture, globalPos.x, globalPos.y, NULL, false, 0.5f);
}

void UI_text::setOutlined(bool isOutlined)
{
	if (isOutlined != outlined)
	{
		outlined = isOutlined;
		createTexture();
	}
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

int UI_text::getLength() const
{
	return text.Length();
}
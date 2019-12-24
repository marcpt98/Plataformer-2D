#include "j1App.h"
#include "UI_Window.h"
#include "j1App.h"
#include "j1Render.h"
#include "p2Defs.h"
#include "j1Gui.h"
#include "j1Render.h"

UI_window::UI_window()
{}

UI_window::~UI_window()
{}

void UI_window::appendChild(int x, int y, UI_element* child)
{
	child->localPosition = { x, y };
	child->parent = this;
	content.add(child);

}

void UI_window::appendChildAtCenter(UI_element* child)
{
	iPoint child_pos(section.w / 2, section.h / 2);
	child_pos.x -= child->section.w / 2;
	child_pos.y -= child->section.h / 2;
	child->localPosition = { child_pos.x, child_pos.y };
	child->parent = this;
	content.add(child);
}

void UI_window::BlitElement()
{
	iPoint globalPos = calculateAbsolutePosition();
	App->render->Blit(texture, globalPos.x, globalPos.y, &section, false);

	for (p2List_item<UI_element*>* item = content.start; item; item = item->next)
	{
		item->data->BlitElement();
	}
}
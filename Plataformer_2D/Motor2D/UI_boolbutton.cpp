#include "UI_Button.h"
#include "j1App.h"
#include "j1Render.h"
#include "UI_boolbutton.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Scene_UI.h"

void UI_boolbutton::setOutlined(bool isOutlined)
{
	if (text != nullptr)
		text->setOutlined(isOutlined);
}

void UI_boolbutton::appendChild(int x, int y, UI_element* child)
{
	child->localPosition = { x, y };
	child->parent = this;
	text = (UI_text*)child;
}

void UI_boolbutton::appendChildAtCenter(UI_element* child)
{
	iPoint child_pos(section.w / 2, section.h / 2);
	child_pos.x -= child->section.w / 2;
	child_pos.y -= child->section.h / 2;
	child->localPosition = { child_pos.x, child_pos.y };
	child->parent = this;
	text = (UI_text*)child;
}

void UI_boolbutton::BlitElement()
{
	iPoint globalPos = calculateAbsolutePosition();

	if (App->sceneui->iscap == true)
	{
		App->render->Blit(texture, globalPos.x, globalPos.y, &booltrue, false);
	}
	else
	{
		App->render->Blit(texture, globalPos.x, globalPos.y, &boolfalse, false);
	}
}
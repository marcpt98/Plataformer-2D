#include "UI_Button.h"
#include "j1App.h"
#include "j1Render.h"
#include "UI_Button.h"
#include "j1App.h"
#include "j1Scene_UI.h"
#include "j1Render.h"
#include "j1Input.h"
#include "p2Log.h"
#include "j1Audio.h"

void UI_button::setOutlined(bool isOutlined)
{
	if (text != nullptr)
		text->setOutlined(isOutlined);
}

void UI_button::appendChild(int x, int y, UI_element* child)
{
	child->localPosition = { x, y };
	child->parent = this;
	text = (UI_text*)child;
}

void UI_button::appendChildAtCenter(UI_element* child)
{
	iPoint child_pos(section.w / 2, section.h / 2);
	child_pos.x -= child->section.w / 2;
	child_pos.y -= child->section.h / 2;
	child->localPosition = { child_pos.x, child_pos.y };
	child->parent = this;
	text = (UI_text*)child;
}

void UI_button::BlitElement()
{
	
	iPoint globalPos = calculateAbsolutePosition();
	
	App->input->GetMousePosition(x, y);
	ChangeVolume();
	switch (state)
	{
	case STANDBY:
		if (element_action != SLIDER_BUTTON && element_action != SLIDER_FX_BUTTON) {
			App->render->Blit(texture, globalPos.x, globalPos.y, &section, false);
		}
		else {
			App->render->Blit(texture, localPosition.x, globalPos.y, &section, false);
		}
		break;
	case MOUSEOVER:
		if (element_action != SLIDER_BUTTON && element_action != SLIDER_FX_BUTTON) {
			App->render->Blit(texture, globalPos.x - 10, globalPos.y - 3, &OnMouse, false);
		}
		else {
			App->render->Blit(texture, localPosition.x, globalPos.y, &section, false);
		}
		break;
	case CLICKED:
		if (element_action != SLIDER_BUTTON && element_action != SLIDER_FX_BUTTON) {
			App->render->Blit(texture, globalPos.x, globalPos.y, &OnClick, false);
		}
		else {
			newposition = x;
			App->render->Blit(texture, localPosition.x -10, globalPos.y, &section, false);
		}
		break;
	}
}
void UI_button::ChangeVolume()
{
	if (App->sceneui->slider_volume == true && x > 206 && x < 760 && element_action == SLIDER_BUTTON)//206 760
	{
		localPosition.x = x-10;
		save_position = x;
		OnMouse.x = x;
		Tick.x = x;
		OnClick.x = x;
		iPoint  globalPos=calculateAbsolutePosition();
		LOG("position: %i", localPosition.x);//197 746
		musicvolume = (((localPosition.x - 197) * 1.) / 552);
		App->audio->setMusicVolume(musicvolume);
		LOG("position: %f", musicvolume);
	}

	if (App->sceneui->fx_volume == true && x > 206 && x < 760 && element_action == SLIDER_FX_BUTTON)//206 760
	{
		localPosition.x = x - 10;
		save_position = x;
		OnMouse.x = x;
		Tick.x = x;
		OnClick.x = x;
		iPoint  globalPos = calculateAbsolutePosition();
		LOG("position: %i", localPosition.x);//197 746
		fxvolume = (((localPosition.x-197) * 1.) / 552);
		App->audio->setFxVolume(fxvolume);
		LOG("position: %f", musicvolume);
	}
	
}//App->audio->setMusicVolume(0.2);


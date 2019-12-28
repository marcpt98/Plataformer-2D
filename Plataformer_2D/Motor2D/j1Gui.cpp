#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Textures.h"
#include "j1Fonts.h"
#include "j1Input.h"
#include "j1Gui.h"
#include "UI_element.h"
#include "UI_Image.h"
#include "UI_Text.h"
#include "UI_Button.h"
#include "UI_window.h"
#include "UI_slider.h"
#include "UI_boolbutton.h"
#include "j1Scene_UI.h"
#include "j1Scene.h"

j1Gui::j1Gui() : j1Module()
{
	name.create("gui");
}

// Destructor
j1Gui::~j1Gui()
{}

// Called before render is available
bool j1Gui::Awake(pugi::xml_node& conf)
{
	LOG("Loading GUI atlas");
	bool ret = true;

	atlas_file_name = conf.child("atlas").attribute("file").as_string("");
	scene_intro_name = conf.child("intro").attribute("file").as_string("");
	title_intro_name = conf.child("title").attribute("file").as_string("");
	licence_name = conf.child("licence").attribute("file").as_string("");
	addText_name = conf.child("text").attribute("file").as_string("");

	return ret;
}

// Called before the first frame
bool j1Gui::Start()
{
	atlas = App->tex->Load(atlas_file_name.GetString());
	scene_intro = App->tex->Load(scene_intro_name.GetString());
	title_intro = App->tex->Load(title_intro_name.GetString());
	licence = App->tex->Load(licence_name.GetString());
	addText = App->tex->Load(addText_name.GetString());

	return true;
}

// Update all guis
bool j1Gui::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdateGui", Profiler::Color::DarkOliveGreen)

	if (App->input->GetKey(SDL_SCANCODE_F8) == KEY_DOWN)
		UI_debug = !UI_debug;

	//Send events related to UI elements
	int x, y;
	App->input->GetMousePosition(x, y);
	int scale = App->win->GetScale();
	for (p2List_item<UI_element*>* item = UI_elements.start; item; item = item->next)
	{
		iPoint globalPos = item->data->calculateAbsolutePosition();
		
			if (x > globalPos.x && x < globalPos.x + item->data->section.w / scale && y > globalPos.y && y < globalPos.y + item->data->section.h / scale)
			{
				if (!item->data->hovering)
				{
					item->data->hovering = true;
					if (item->data->callback != nullptr)
						item->data->callback->OnUIEvent(item->data, MOUSE_ENTER);
				}
				else if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_DOWN)
				{
					if (item->data->callback != nullptr)
						item->data->callback->OnUIEvent(item->data, MOUSE_LEFT_CLICK);
				}
				else if (App->input->GetMouseButtonDown(SDL_BUTTON_LEFT) == KEY_UP)
				{
					App->sceneui->slider_volume = false;
					App->sceneui->fx_volume = false;
					if (item->data->callback != nullptr)
						item->data->callback->OnUIEvent(item->data, MOUSE_LEFT_RELEASE);
				}
				else if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_DOWN)
				{
					if (item->data->callback != nullptr)
						item->data->callback->OnUIEvent(item->data, MOUSE_RIGHT_CLICK);
				}
				else if (App->input->GetMouseButtonDown(SDL_BUTTON_RIGHT) == KEY_UP)
				{
					if (item->data->callback != nullptr)
						item->data->callback->OnUIEvent(item->data, MOUSE_RIGHT_RELEASE);
				}
		
				
			}
			else
			{
				if (item->data->hovering)
				{
					item->data->hovering = false;
					if (item->data->callback != nullptr)
						item->data->callback->OnUIEvent(item->data, MOUSE_LEAVE);
				}
			}
		
		
	}
	return true;
}

// Called after all Updates
bool j1Gui::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdateFadeToBlack", Profiler::Color::MediumSlateBlue)

	for (p2List_item<UI_element*>* item = UI_elements.start; item; item = item->next)
	{
		if (item->data->parent == nullptr)
			item->data->BlitElement();
	}

	return true;
}

// Called before quitting
bool j1Gui::CleanUp()
{
	LOG("Freeing GUI");

	p2List_item<UI_element*>* item;
	item = UI_elements.start;
	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	UI_elements.clear();

	return true;
}

// const getter for atlas
SDL_Texture* j1Gui::GetAtlas()
{
	return atlas;
}

// class Gui ---------------------------------------------------
UI_text* j1Gui::AddText(char* text, int x, int y, _TTF_Font* font, SDL_Color color, j1Module* callback)
{
	UI_text* ret = new UI_text(text, x, y, font, color, callback);
	UI_elements.add(ret);

	return ret;
}

UI_image* j1Gui::AddImage(SDL_Texture* texture, int x, int y, SDL_Rect section, j1Module* callback)
{
	UI_image* ret = new UI_image(texture, x, y, section, callback);
	UI_elements.add(ret);

	return ret;
}

UI_button* j1Gui::AddButton(int x, int y, SDL_Texture* texture, SDL_Rect standby, SDL_Rect OnMouse, SDL_Rect OnClick, j1Module* callback)
{
	SDL_Texture* usingTexture = (texture) ? texture : atlas;

	UI_button* ret = new UI_button(x, y, usingTexture, standby, OnMouse, OnClick, LINK, callback);
	UI_elements.add(ret);

	return ret;
}

UI_boolbutton* j1Gui::AddBoolButton(int x, int y, SDL_Texture* texture, SDL_Rect booltrue, SDL_Rect boolfalse, j1Module* callback)
{
	SDL_Texture* usingTexture = (texture) ? texture : atlas;

	UI_boolbutton* ret = new UI_boolbutton(x, y, usingTexture, boolfalse, booltrue, callback);
	UI_elements.add(ret);

	return ret;
}

UI_slider* j1Gui::AddSlider(int x, int y, SDL_Texture* texture,UI_button* button, j1Module* callback, SDL_Rect image_bar)
{
	SDL_Texture* usingTexture = (texture) ? texture : atlas;

	UI_slider* ret = new UI_slider(x, y, usingTexture,button,callback,image_bar);
	UI_elements.add(ret);

	return ret;
}

UI_window* j1Gui::AddWindow(SDL_Texture* texture, int x, int y, SDL_Rect section, j1Module* callback)
{
	UI_window* ret = new UI_window(texture, x, y, section, callback);
	UI_elements.add(ret);

	return ret;
}

bool j1Gui::UIDebugDraw()
{
	bool ret = true;
	for (p2List_item<UI_element*>* item = UI_elements.start; item; item = item->next)
	{
		if (item->data->element_type == IMAGE)
			App->render->DrawQuad({ item->data->localPosition.x,  item->data->localPosition.y, item->data->section.w, item->data->section.h }, 255, 0, 0, 60, true, false);

		else if (item->data->element_type == WINDOW)
			App->render->DrawQuad({ item->data->localPosition.x,  item->data->localPosition.y, item->data->section.w, item->data->section.h }, 255, 0, 0, 80, true, false);

		else
			App->render->DrawQuad({ item->data->localPosition.x,  item->data->localPosition.y, item->data->section.w, item->data->section.h }, 255, 0, 0, 100, true, false);
	}
	return ret;
}

bool j1Gui::DeleteGui(UI_element* gui)
{
	gui->CleanUp();
	UI_elements.del(UI_elements.At(UI_elements.find(gui)));
	
	return true;
}
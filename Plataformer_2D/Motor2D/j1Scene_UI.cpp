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
#include "j1Scene_UI.h"

j1SceneUI::j1SceneUI()
{
	name.create("sceneUI");
}

// Destructor
j1SceneUI::~j1SceneUI()
{}

bool j1SceneUI::Start()
{


	return true;
}

bool j1SceneUI::PreUpdate()
{

	return true;
}

bool j1SceneUI::PostUpdate()
{


	return true;
}

bool j1SceneUI::CleanUp()
{
	LOG("Freeing GUI");

	p2List_item<UI*>* item;
	item = UI_type.start;
	while (item != NULL)
	{
		RELEASE(item->data);
		item = item->next;
	}
	UI_type.clear();

	return true;
}

UI_ingame* j1SceneUI::Addingame_UI()
{
	UI* ingame_UI = new UI(MENU_INGAME);

	//UI_element* live1=App->gui->AddImage()
}
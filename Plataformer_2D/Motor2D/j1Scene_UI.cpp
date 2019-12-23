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
#include "j1EntityManager.h"
#include "j1Particles.h"
#include "j1Colliders.h"
#include "j1Map.h"
#include "j1Scene.h"

j1SceneUI::j1SceneUI()
{
	name.create("sceneUI");
}

// Destructor
j1SceneUI::~j1SceneUI()
{}

bool j1SceneUI::Start()
{
	App->scene->PrepSceneIntro();

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
	LOG("Freeing UI_type list");

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

bool j1SceneUI::Addingame_UI()
{
	// Elements of this UI
	live1 = App->gui->AddImage(App->gui->GetAtlas(), 10, 10, { 568,312,118,102 });
	live2 = App->gui->AddImage(App->gui->GetAtlas(), 100, 10, { 568,312,118,102 });
	
	return true;
}

bool j1SceneUI::Addpause_UI()
{
	// Elements of this UI
	live3 = App->gui->AddImage(App->gui->GetAtlas(), 10, 500, { 568,312,118,102 });

	return true;
}

bool j1SceneUI::Deleteingame_UI()
{
	App->gui->DeleteGui(live1);
	App->gui->DeleteGui(live2);

	return true;
}

bool j1SceneUI::Deletepause_UI()
{
	App->gui->DeleteGui(live3);

	return true;
}

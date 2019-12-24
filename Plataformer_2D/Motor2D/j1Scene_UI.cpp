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
#include "j1Audio.h"

j1SceneUI::j1SceneUI()
{
	name.create("sceneUI");

	exit = false;
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
	return true;
}

bool j1SceneUI::Addsceneintro_UI()
{
	App->scene->introMap = 1;

	// Elements of this UI
	background = App->gui->AddImage(App->gui->scene_intro, 0, 0, { 0,0,1056,792 });
	title = App->gui->AddImage(App->gui->title_intro, 200, 100, { 0,0,683,98 });
	play_button = App->gui->AddButton(400, 250, App->gui->GetAtlas(), {1,1,234,72}, {1,74,259,80}, {1,155,234,63}, this);
	play_button->element_action = START;
	load_button = App->gui->AddButton(400, 350, App->gui->GetAtlas(), { 802,1,234,72 }, { 801,74,259,80 }, { 801,155,234,63 }, this);
	load_button->element_action = LOAD;
	credits_button = App->gui->AddButton(350, 550, App->gui->GetAtlas(), { 1073,1,337,72 }, { 1072,74,357,80 }, { 1072,155,338,63 }, this);
	credits_button->element_action = CREDITS;
	settings_button = App->gui->AddButton(350, 450, App->gui->GetAtlas(), { 0,220,360,72 }, { 1,293,392,80 }, { 1,374,362,63 }, this);
	settings_button->element_action = SETTINGS;
	exit_button = App->gui->AddButton(400, 650, App->gui->GetAtlas(), { 535,1,234,71 }, { 535,73,258,80 }, { 535,154,234,63 }, this);
	exit_button->element_action = EXIT;

	return true;
}

bool j1SceneUI::Deletesceneintro_UI()
{
	App->gui->DeleteGui(background);
	App->gui->DeleteGui(title);
	App->gui->DeleteGui(play_button);
	App->gui->DeleteGui(load_button);
	App->gui->DeleteGui(credits_button);
	App->gui->DeleteGui(settings_button);
	App->gui->DeleteGui(exit_button);

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

//Ui events
bool j1SceneUI::OnUIEvent(UI_element* element, event_type event_type)
{
	if (event_type == MOUSE_ENTER || event_type == MOUSE_RIGHT_RELEASE)
	{
		element->state = MOUSEOVER;

	}
	else if (event_type == MOUSE_LEAVE)
	{
		element->state = STANDBY;

	}
	else if (event_type == MOUSE_LEFT_CLICK)
	{
		element->state = CLICKED;
	}
	else if (event_type == MOUSE_LEFT_RELEASE)
	{
		if (element->element_action == START)
		{
			App->scene->sceneintro = false;
			App->scene->introMap = 0;
			App->scene->currentMap = 0;
			App->scene->LevelName(0);
			Deletesceneintro_UI();
		}
		else if (element->element_action == LOAD)
		{
			App->scene->sceneintro = false;
			App->load();
			App->scene->introMap = 0;
			Deletesceneintro_UI();
		}
		else if (element->element_action == CREDITS)
		{
			
		}
		else if (element->element_action == SETTINGS)
		{

		}
		else if (element->element_action == EXIT)
		{
			exit = true;
		}
	}
	else if (event_type == MOUSE_RIGHT_CLICK)
	{
	}

	return true;
}

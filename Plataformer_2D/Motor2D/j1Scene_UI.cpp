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

bool j1SceneUI::Addsettings_UI()
{
	background = App->gui->AddImage(App->gui->scene_intro, 0, 0, { 0,0,1056,792 });
	title = App->gui->AddImage(App->gui->title_intro, 200, 100, { 0,0,683,98 });
	play_button = App->gui->AddButton(400, 250, App->gui->GetAtlas(), { 1,1,234,72 }, { 1,74,259,80 }, { 1,155,234,63 });
	load_button = App->gui->AddButton(400, 350, App->gui->GetAtlas(), { 802,1,234,72 }, { 801,74,259,80 }, { 801,155,234,63 });
	credits_button = App->gui->AddButton(350, 550, App->gui->GetAtlas(), { 1073,1,337,72 }, { 1072,74,357,80 }, { 1072,155,338,63 });
	settings_button = App->gui->AddButton(350, 450, App->gui->GetAtlas(), { 0,220,360,72 }, { 1,293,392,80 }, { 1,374,362,63 });
	exit_button = App->gui->AddButton(400, 650, App->gui->GetAtlas(), { 535,1,234,71 }, { 535,73,258,80 }, { 535,154,234,63 });

	window_settings = App->gui->AddWindow(App->gui->GetAtlas(), 100, 150, { 1,439,831,494 });
	music = App->gui->AddText("music", 420, 160, App->font->Load("fonts/ARCADECLASSIC.ttf", 70), { 255,255,255 });
	fx = App->gui->AddText("fx", 480, 340, App->font->Load("fonts/ARCADECLASSIC.ttf", 70), { 255,255,255 });
	cap = App->gui->AddText("cap   game   to   30fps", 140, 530, App->font->Load("fonts/ARCADECLASSIC.ttf", 70), { 255,255,255 });
	exit_settings = App->gui->AddButton(100, 150, App->gui->GetAtlas(), { 435,220,54,54 }, { 490,220,61,60 }, { 552,220,54,54 }, this);
	exit_settings->element_action = EXIT_SETTINGS;

	return true;
}

bool j1SceneUI::Deletesettings_UI()
{
	App->gui->DeleteGui(background);
	App->gui->DeleteGui(title);
	App->gui->DeleteGui(play_button);
	App->gui->DeleteGui(load_button);
	App->gui->DeleteGui(credits_button);
	App->gui->DeleteGui(settings_button);
	App->gui->DeleteGui(exit_button);

	App->gui->DeleteGui(window_settings);
	App->gui->DeleteGui(music);
	App->gui->DeleteGui(fx);
	App->gui->DeleteGui(cap);
	App->gui->DeleteGui(exit_settings);

	return true;
}

bool j1SceneUI::Addcredits_UI()
{
	background = App->gui->AddImage(App->gui->scene_intro, 0, 0, { 0,0,1056,792 });
	title = App->gui->AddImage(App->gui->title_intro, 200, 100, { 0,0,683,98 });
	play_button = App->gui->AddButton(400, 250, App->gui->GetAtlas(), { 1,1,234,72 }, { 1,74,259,80 }, { 1,155,234,63 });
	load_button = App->gui->AddButton(400, 350, App->gui->GetAtlas(), { 802,1,234,72 }, { 801,74,259,80 }, { 801,155,234,63 });
	credits_button = App->gui->AddButton(350, 550, App->gui->GetAtlas(), { 1073,1,337,72 }, { 1072,74,357,80 }, { 1072,155,338,63 });
	settings_button = App->gui->AddButton(350, 450, App->gui->GetAtlas(), { 0,220,360,72 }, { 1,293,392,80 }, { 1,374,362,63 });
	exit_button = App->gui->AddButton(400, 650, App->gui->GetAtlas(), { 535,1,234,71 }, { 535,73,258,80 }, { 535,154,234,63 });

	window_credits = App->gui->AddWindow(App->gui->GetAtlas(), 100, 150, { 1,439,831,494 });
	text_1 = App->gui->AddText("credits", 415, 160, App->font->Load("fonts/ARCADECLASSIC.ttf", 70), { 255,255,255 });
	text_2 = App->gui->AddText("game   made   by", 140, 250, App->font->Load("fonts/ARCADECLASSIC.ttf", 60), { 255,255,255 });
	text_3 = App->gui->AddText("marc   palma   turon", 140, 300, App->font->Load("fonts/ARCADECLASSIC.ttf", 50), { 255,255,255 });
	text_4 = App->gui->AddText("pol   de   la   torre   sole", 140, 340, App->font->Load("fonts/ARCADECLASSIC.ttf", 50), { 255,255,255 });
	licence_button = App->gui->AddButton(160, 480, App->gui->GetAtlas(), { 1042,219,337,72 }, { 1041,292,357,80 }, { 1041,373,338,63 }, this);
	licence_button->element_action = LICENCE;
	exit_credits = App->gui->AddButton(100, 150, App->gui->GetAtlas(), { 435,220,54,54 }, { 490,220,61,60 }, { 552,220,54,54 }, this);
	exit_credits->element_action = EXIT_CREDITS;

	return true;
}

bool j1SceneUI::Deletecredits_UI()
{
	App->gui->DeleteGui(background);
	App->gui->DeleteGui(title);
	App->gui->DeleteGui(play_button);
	App->gui->DeleteGui(load_button);
	App->gui->DeleteGui(credits_button);
	App->gui->DeleteGui(settings_button);
	App->gui->DeleteGui(exit_button);

	App->gui->DeleteGui(window_credits);
	App->gui->DeleteGui(text_1);
	App->gui->DeleteGui(text_2);
	App->gui->DeleteGui(text_3);
	App->gui->DeleteGui(text_4);
	App->gui->DeleteGui(licence_button);
	App->gui->DeleteGui(exit_credits);

	return true;
}

bool j1SceneUI::Addlicence_UI()
{
	background = App->gui->AddImage(App->gui->scene_intro, 0, 0, { 0,0,1056,792 });
	title = App->gui->AddImage(App->gui->title_intro, 200, 100, { 0,0,683,98 });
	play_button = App->gui->AddButton(400, 250, App->gui->GetAtlas(), { 1,1,234,72 }, { 1,74,259,80 }, { 1,155,234,63 });
	load_button = App->gui->AddButton(400, 350, App->gui->GetAtlas(), { 802,1,234,72 }, { 801,74,259,80 }, { 801,155,234,63 });
	credits_button = App->gui->AddButton(350, 550, App->gui->GetAtlas(), { 1073,1,337,72 }, { 1072,74,357,80 }, { 1072,155,338,63 });
	settings_button = App->gui->AddButton(350, 450, App->gui->GetAtlas(), { 0,220,360,72 }, { 1,293,392,80 }, { 1,374,362,63 });
	exit_button = App->gui->AddButton(400, 650, App->gui->GetAtlas(), { 535,1,234,71 }, { 535,73,258,80 }, { 535,154,234,63 });

	window_licence = App->gui->AddWindow(App->gui->GetAtlas(), 100, 150, { 1,439,831,494 });
	text_6 = App->gui->AddText("licence", 415, 160, App->font->Load("fonts/ARCADECLASSIC.ttf", 70), { 255,255,255 });
	text_7 = App->gui->AddText("//MIT License", 140, 220, App->font->Load("fonts/open_sans/OpenSans-ExtraBold.ttf", 15), { 255,255,255 });
	text_8 = App->gui->AddText("Copyright (c) [2019] [Pol de la Torre Solé and Marc Palma Turón]", 
		140, 245, App->font->Load("fonts/open_sans/OpenSans-ExtraBold.ttf", 15), { 255,255,255 });
	text_9 = App->gui->AddText("Permission is hereby granted, free of charge, to any person obtaining a copy of this software and",
		140, 270, App->font->Load("fonts/open_sans/OpenSans-ExtraBold.ttf", 15), { 255,255,255 });
	text_10 = App->gui->AddText("associated documentation files (the 'Software'), to deal in the Software without restriction,",
		140, 290, App->font->Load("fonts/open_sans/OpenSans-ExtraBold.ttf", 15), { 255,255,255 });
	text_11 = App->gui->AddText("including without limitation the rights to use, copy, modify, merge, publish, distribute, sublicense,",
		140, 310, App->font->Load("fonts/open_sans/OpenSans-ExtraBold.ttf", 15), { 255,255,255 });
	text_12 = App->gui->AddText("and/or sell copies of the Software, and to permit persons to whom the Software is furnished to do",
		140, 330, App->font->Load("fonts/open_sans/OpenSans-ExtraBold.ttf", 15), { 255,255,255 });
	text_13 = App->gui->AddText("so, subject to the following conditions:",
		140, 350, App->font->Load("fonts/open_sans/OpenSans-ExtraBold.ttf", 15), { 255,255,255 });
	text_14 = App->gui->AddText("The above copyright notice and this permission notice shall be included in all copies or",
		140, 370, App->font->Load("fonts/open_sans/OpenSans-ExtraBold.ttf", 15), { 255,255,255 });
	text_15 = App->gui->AddText("substantial portions of the Software.",
		140, 390, App->font->Load("fonts/open_sans/OpenSans-ExtraBold.ttf", 15), { 255,255,255 });
	text_16 = App->gui->AddText("THE SOFTWARE IS PROVIDED 'AS IS', WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,",
		140, 430, App->font->Load("fonts/open_sans/OpenSans-ExtraBold.ttf", 15), { 255,255,255 });
	text_17 = App->gui->AddText("INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR",
		140, 450, App->font->Load("fonts/open_sans/OpenSans-ExtraBold.ttf", 15), { 255,255,255 });
	text_18 = App->gui->AddText("PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE",
		140, 470, App->font->Load("fonts/open_sans/OpenSans-ExtraBold.ttf", 15), { 255,255,255 });
	text_19 = App->gui->AddText("LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT",
		140, 490, App->font->Load("fonts/open_sans/OpenSans-ExtraBold.ttf", 15), { 255,255,255 });
	text_20 = App->gui->AddText("OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR",
		140, 510, App->font->Load("fonts/open_sans/OpenSans-ExtraBold.ttf", 15), { 255,255,255 });
	text_21 = App->gui->AddText("OTHER DEALINGS IN THE SOFTWARE.//",
		140, 530, App->font->Load("fonts/open_sans/OpenSans-ExtraBold.ttf", 15), { 255,255,255 });


	exit_licence = App->gui->AddButton(100, 150, App->gui->GetAtlas(), { 435,220,54,54 }, { 490,220,61,60 }, { 552,220,54,54 }, this);
	exit_licence->element_action = EXIT_LICENCE;

	return true;
}

bool j1SceneUI::Deletelicence_UI()
{
	App->gui->DeleteGui(background);
	App->gui->DeleteGui(title);
	App->gui->DeleteGui(play_button);
	App->gui->DeleteGui(load_button);
	App->gui->DeleteGui(credits_button);
	App->gui->DeleteGui(settings_button);
	App->gui->DeleteGui(exit_button);

	App->gui->DeleteGui(window_licence);
	App->gui->DeleteGui(text_6);
	App->gui->DeleteGui(text_7);
	App->gui->DeleteGui(text_8);
	App->gui->DeleteGui(text_9);
	App->gui->DeleteGui(text_10);
	App->gui->DeleteGui(text_11);
	App->gui->DeleteGui(text_12);
	App->gui->DeleteGui(text_13);
	App->gui->DeleteGui(text_14);
	App->gui->DeleteGui(text_15);
	App->gui->DeleteGui(text_16);
	App->gui->DeleteGui(text_17);
	App->gui->DeleteGui(text_18);
	App->gui->DeleteGui(text_19);
	App->gui->DeleteGui(text_20);
	App->gui->DeleteGui(text_21);
	App->gui->DeleteGui(exit_licence);

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
		else if (element->element_action == SETTINGS)
		{
			Deletesceneintro_UI();
			Addsettings_UI();
		}
		else if (element->element_action == EXIT_SETTINGS)
		{
			Deletesettings_UI();
			Addsceneintro_UI();
		}
		else if (element->element_action == CREDITS)
		{
			Deletesceneintro_UI();
			Addcredits_UI();
		}
		else if (element->element_action == EXIT_CREDITS)
		{
			Deletecredits_UI();
			Addsceneintro_UI();
		}
		else if (element->element_action == LICENCE)
		{
			Deletecredits_UI();
			Addlicence_UI();
		}
		else if (element->element_action == EXIT_LICENCE)
		{
			Deletelicence_UI();
			Addcredits_UI();
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

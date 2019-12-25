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
	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && App->scene->sceneintro == false)
	{
		if (pause_UI == false)
		{
			App->scene->pause = true;
			App->audio->setMusicVolume(0.2);
			Addpause_UI();
			pause_UI = true;
		}
		else if (pause_UI == true)
		{
			App->scene->pause = false;
			App->audio->setMusicVolume(1);
			Deletepause_UI();
			pause_UI = false;
		}
	}

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
	window_settings = App->gui->AddWindow(App->gui->GetAtlas(), 100, 150, { 1,439,831,494 });
	music = App->gui->AddText("music", 425, 160, App->font->Load("fonts/ARCADECLASSIC.ttf", 60), { 255,255,255 });
	fx = App->gui->AddText("fx", 480, 340, App->font->Load("fonts/ARCADECLASSIC.ttf", 60), { 255,255,255 });
	cap = App->gui->AddText("cap   game   to   30fps", 140, 530, App->font->Load("fonts/ARCADECLASSIC.ttf", 60), { 255,255,255 });
	exit_settings = App->gui->AddButton(100, 150, App->gui->GetAtlas(), { 435,220,54,54 }, { 490,220,61,60 }, { 552,220,54,54 }, this);
	if (App->scene->sceneintro == true)
	{
		exit_settings->element_action = EXIT_SETTINGS;
	}
	else
	{
		exit_settings->element_action = EXIT_SETTINGS_INGAME;
	}

	return true;
}

bool j1SceneUI::Deletesettings_UI()
{
	App->gui->DeleteGui(window_settings);
	App->gui->DeleteGui(music);
	App->gui->DeleteGui(fx);
	App->gui->DeleteGui(cap);
	App->gui->DeleteGui(exit_settings);

	return true;
}

bool j1SceneUI::Addcredits_UI()
{
	window_credits = App->gui->AddWindow(App->gui->GetAtlas(), 100, 150, { 1,439,831,494 });
	text_1 = App->gui->AddText("credits", 415, 160, App->font->Load("fonts/ARCADECLASSIC.ttf", 60), { 255,255,255 });
	text_2 = App->gui->AddText("game   made   by", 140, 250, App->font->Load("fonts/ARCADECLASSIC.ttf", 50), { 255,255,255 });
	text_3 = App->gui->AddText("marc   palma   turon", 140, 300, App->font->Load("fonts/ARCADECLASSIC.ttf", 55), { 255,255,255 });
	text_4 = App->gui->AddText("pol   de   la   torre   sole", 140, 340, App->font->Load("fonts/ARCADECLASSIC.ttf", 55), { 255,255,255 });
	licence_button = App->gui->AddButton(160, 480, App->gui->GetAtlas(), { 1042,219,337,72 }, { 1041,292,357,80 }, { 1041,373,338,63 }, this);
	licence_button->element_action = LICENCE;
	exit_credits = App->gui->AddButton(100, 150, App->gui->GetAtlas(), { 435,220,54,54 }, { 490,220,61,60 }, { 552,220,54,54 }, this);
	exit_credits->element_action = EXIT_CREDITS;

	return true;
}

bool j1SceneUI::Deletecredits_UI()
{
	App->gui->DeleteGui(window_credits);
	App->gui->DeleteGui(text_1);
	delete(text_1);
	App->gui->DeleteGui(text_2);
	delete(text_2);
	App->gui->DeleteGui(text_3);
	delete(text_3);
	App->gui->DeleteGui(text_4);
	delete(text_4);
	App->gui->DeleteGui(licence_button);
	App->gui->DeleteGui(exit_credits);

	return true;
}

bool j1SceneUI::Addlicence_UI()
{
	window_licence = App->gui->AddWindow(App->gui->GetAtlas(), 100, 150, { 1,439,831,494 });
	text_5 = App->gui->AddText("licence", 415, 160, App->font->Load("fonts/ARCADECLASSIC.ttf", 60), { 255,255,255 });
	licence = App->gui->AddImage(App->gui->licence, 120, 250, { 0,0,788,345 });
	exit_licence = App->gui->AddButton(100, 150, App->gui->GetAtlas(), { 435,220,54,54 }, { 490,220,61,60 }, { 552,220,54,54 }, this);
	exit_licence->element_action = EXIT_LICENCE;

	return true;
}

bool j1SceneUI::Deletelicence_UI()
{
	App->gui->DeleteGui(window_licence);
	App->gui->DeleteGui(text_5);
	App->gui->DeleteGui(licence);
	App->gui->DeleteGui(exit_licence);

	return true;
}

bool j1SceneUI::back_intro_UI()
{
	background = App->gui->AddImage(App->gui->scene_intro, 0, 0, { 0,0,1056,792 });
	title = App->gui->AddImage(App->gui->title_intro, 200, 100, { 0,0,683,98 });
	play_button = App->gui->AddButton(400, 250, App->gui->GetAtlas(), { 1,1,234,72 }, { 1,74,259,80 }, { 1,155,234,63 });
	load_button = App->gui->AddButton(400, 350, App->gui->GetAtlas(), { 802,1,234,72 }, { 801,74,259,80 }, { 801,155,234,63 });
	credits_button = App->gui->AddButton(350, 550, App->gui->GetAtlas(), { 1073,1,337,72 }, { 1072,74,357,80 }, { 1072,155,338,63 });
	settings_button = App->gui->AddButton(350, 450, App->gui->GetAtlas(), { 0,220,360,72 }, { 1,293,392,80 }, { 1,374,362,63 });
	exit_button = App->gui->AddButton(400, 650, App->gui->GetAtlas(), { 535,1,234,71 }, { 535,73,258,80 }, { 535,154,234,63 });

	return true;
}

bool j1SceneUI::delete_intro_UI()
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
	if (App->scene->lives == 3)
	{
		player_face1 = App->gui->AddImage(App->gui->GetAtlas(), 30, 40, { 531,384,59,52 });
		player_face2 = App->gui->AddImage(App->gui->GetAtlas(), 100, 40, { 531,384,59,52 });
		player_face3 = App->gui->AddImage(App->gui->GetAtlas(), 170, 40, { 531,384,59,52 });
	}
	else if (App->scene->lives == 2)
	{
		player_face1 = App->gui->AddImage(App->gui->GetAtlas(), 30, 40, { 531,384,59,52 });
		player_face2 = App->gui->AddImage(App->gui->GetAtlas(), 100, 40, { 531,384,59,52 });
	}
	else if (App->scene->lives == 1)
	{
		player_face1 = App->gui->AddImage(App->gui->GetAtlas(), 30, 40, { 531,384,59,52 });
	}
	else if (App->scene->lives == 0)
	{
	}
	
	return true;
}

bool j1SceneUI::Deleteingame_UI()
{
	if (App->scene->lives == 3)
	{
		App->gui->DeleteGui(player_face1);
		App->gui->DeleteGui(player_face2);
		App->gui->DeleteGui(player_face3);
	}
	else if (App->scene->lives == 2)
	{
		App->gui->DeleteGui(player_face1);
		App->gui->DeleteGui(player_face2);
	}
	else if (App->scene->lives == 1)
	{
		App->gui->DeleteGui(player_face1);
	}
	else if (App->scene->lives == 0)
	{
	}

	return true;
}

bool j1SceneUI::Addpause_UI()
{
	// Elements of this UI
	window_pause = App->gui->AddWindow(App->gui->GetAtlas(), 300, 150, { 833,439,479,494 });
	exit_pause = App->gui->AddButton(300, 150, App->gui->GetAtlas(), { 435,220,54,54 }, { 490,220,61,60 }, { 552,220,54,54 }, this);
	exit_pause->element_action = EXIT_PAUSE;
	save_button = App->gui->AddButton(430, 220, App->gui->GetAtlas(), { 268,1,234,72 }, { 268,74,258,81 }, { 268,156,234,63 }, this);
	save_button->element_action = SAVE;
	load_ingame = App->gui->AddButton(430, 320, App->gui->GetAtlas(), { 802,1,234,72 }, { 801,74,259,80 }, { 801,155,234,63 }, this);
	load_ingame->element_action = LOAD_INGAME;
	settings_ingame = App->gui->AddButton(365, 420, App->gui->GetAtlas(), { 0,220,360,72 }, { 1,293,392,80 }, { 1,374,362,63 }, this);
	settings_ingame->element_action = SETTINGS_INGAME;
	exit_intro = App->gui->AddButton(430, 520, App->gui->GetAtlas(), { 535,1,234,71 }, { 535,73,258,80 }, { 535,154,234,63 }, this);
	exit_intro->element_action = EXIT_MENU;

	return true;
}

bool j1SceneUI::Deletepause_UI()
{
	App->gui->DeleteGui(window_pause);
	App->gui->DeleteGui(exit_pause);
	App->gui->DeleteGui(save_button);
	App->gui->DeleteGui(load_ingame);
	App->gui->DeleteGui(settings_ingame);
	App->gui->DeleteGui(exit_intro);

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
			App->scene->timertime = SDL_GetTicks();
			App->scene->timer = 600;
			App->scene->lives = 3;
			App->scene->player_score = 0;
			p2SString score_info("Score 0");
			App->scene->score->setText(score_info);
			Deletesceneintro_UI();
			Addingame_UI();
		}
		else if (element->element_action == LOAD)
		{
			App->scene->sceneintro = false;
			App->load();
			App->scene->introMap = 0;
			Deletesceneintro_UI();
			Addingame_UI();
			
			
		}
		else if (element->element_action == LOAD_INGAME)
		{
			App->load();
			Deleteingame_UI();
			Addingame_UI();
		}
		else if (element->element_action == SAVE)
		{
			App->save();
		}
		else if (element->element_action == SETTINGS)
		{
			Deletesceneintro_UI();
			back_intro_UI();
			Addsettings_UI();
		}
		else if (element->element_action == SETTINGS_INGAME)
		{
			Deletepause_UI();
			Addsettings_UI();
		}
		else if (element->element_action == EXIT_SETTINGS_INGAME)
		{
			Deletesettings_UI();
			Addpause_UI();
		}
		else if (element->element_action == EXIT_SETTINGS)
		{
			delete_intro_UI();
			Deletesettings_UI();
			Addsceneintro_UI();
		}
		else if (element->element_action == CREDITS)
		{
			Deletesceneintro_UI();
			back_intro_UI();
			Addcredits_UI();
		}
		else if (element->element_action == EXIT_CREDITS)
		{
			delete_intro_UI();
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
		else if (element->element_action == EXIT_PAUSE)
		{
			App->scene->pause = false;
			App->audio->setMusicVolume(1);
			Deletepause_UI();
			pause_UI = false;
		}
		else if (element->element_action == EXIT_MENU)
		{
			App->scene->sceneintro = true;
			App->scene->PrepSceneIntro();
			App->scene->pause = false;
			App->audio->setMusicVolume(1);
			Deletepause_UI();
			Deleteingame_UI();
			pause_UI = false;
		}
	}
	else if (event_type == MOUSE_RIGHT_CLICK)
	{
	}

	return true;
}

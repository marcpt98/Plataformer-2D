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
#include "UI_boolbutton.h"
#include "UI_window.h"
#include "UI_slider.h"
#include "j1Scene_UI.h"
#include "j1EntityManager.h"
#include "j1Particles.h"
#include "j1Colliders.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1Audio.h"
#include "j1Console.h"

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
	push_button = App->audio->LoadFX2("audio/fx/fx_push_button.wav");
	release_button = App->audio->LoadFX2("audio/fx/fx_release_button.wav");
	over_button = App->audio->LoadFX2("audio/fx/fx_over_button.wav");
	App->scene->PrepSceneIntro();

	return true;
}

bool j1SceneUI::PreUpdate()
{
	BROFILER_CATEGORY("PreUpdateSceneui", Profiler::Color::SeaShell)

		return true;
}

bool j1SceneUI::PostUpdate()
{
	BROFILER_CATEGORY("PostUpdateSceneui", Profiler::Color::DarkGoldenRod)

	if (App->gui->UI_debug)
		App->gui->UIDebugDraw();

	if (App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN && App->scene->sceneintro == false && App->sceneui->settings_open == false)
	{
		if (pause_UI == false)
		{
			App->scene->pause = true;
			Addpause_UI();
			pause_UI = true;
		}
		else if (pause_UI == true)
		{
			App->scene->pause = false;
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
	settings_button = App->gui->AddButton(340, 450, App->gui->GetAtlas(), { 0,220,360,72 }, { 1,293,392,80 }, { 1,374,362,63 }, this);
	settings_button->element_action = SETTINGS;
	webpage_button = App->gui->AddButton(25, 650, App->gui->GetAtlas(), { 749,336,106,88 }, { 627,327,118,99 }, { 862,338,102,84 }, this);
	webpage_button->element_action = WEBPAGE;
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
	App->gui->DeleteGui(webpage_button);
	App->gui->DeleteGui(exit_button);

	return true;
}

bool j1SceneUI::Addsettings_UI()
{
	settings_open = true;
	window_settings = App->gui->AddWindow(App->gui->GetAtlas(), 100, 150, { 1,439,831,494 });
	music = App->gui->AddImage(App->gui->addText, 425, 175, { 0,0,176,33 });
	fx = App->gui->AddImage(App->gui->addText, 480, 375, { 0,34,69,33 });
	cap = App->gui->AddImage(App->gui->addText, 135, 545, { 0,68,573,33 });
	exit_settings = App->gui->AddButton(100, 150, App->gui->GetAtlas(), { 435,220,54,54 }, { 490,220,61,60 }, { 552,220,54,54 }, this);
	cap_button = App->gui->AddBoolButton(720, 530, App->gui->GetAtlas(), { 440,312,63,63 }, { 504, 312, 63, 63 }, this);
	cap_button->element_action = CAP;
	slider_button = App->gui->AddButton(450, 235, App->gui->GetAtlas(), { 394 ,312, 45, 65 }, { 394 ,312, 45, 65 }, { 394, 312 ,45 ,65 }, this);
	slider_button->element_action = SLIDER_BUTTON;
	first_slider = App->gui->AddSlider(450, 250, App->gui->GetAtlas(), slider_button, nullptr, { 394,281,607,30 });// 394 281 607

	fx_slider = App->gui->AddButton(450, 435, App->gui->GetAtlas(), { 394 ,312, 45, 65 }, { 394 ,312, 45, 65 }, { 394, 312 ,45 ,65 }, this);
	fx_slider->element_action = SLIDER_FX_BUTTON;
	second_slider = App->gui->AddSlider(450, 450, App->gui->GetAtlas(), fx_slider, nullptr, { 394,281,607,30 });// 394 281 607
	
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
	settings_open = false;
	App->gui->DeleteGui(window_settings);
	App->gui->DeleteGui(music);
	App->gui->DeleteGui(fx);
	App->gui->DeleteGui(cap);
	App->gui->DeleteGui(exit_settings);
	App->gui->DeleteGui(cap_button);
	App->gui->DeleteGui(slider_button);
	App->gui->DeleteGui(first_slider);
	App->gui->DeleteGui(fx_slider);
	App->gui->DeleteGui(second_slider);
	return true;
}

bool j1SceneUI::Addcredits_UI()
{
	window_credits = App->gui->AddWindow(App->gui->GetAtlas(), 100, 150, { 1,439,831,494 });
	credits = App->gui->AddImage(App->gui->addText, 415, 170, { 0,102,247,33 });
	game_made = App->gui->AddImage(App->gui->addText, 140, 250, { 0,136,371,30 });
	marc = App->gui->AddImage(App->gui->addText, 140, 300, { 0,167,464,27 });
	pol = App->gui->AddImage(App->gui->addText, 140, 340, { 0,195,566,27 });
	licence_button = App->gui->AddButton(160, 480, App->gui->GetAtlas(), { 1042,219,337,72 }, { 1041,292,357,80 }, { 1041,373,338,63 }, this);
	licence_button->element_action = LICENCE;
	exit_credits = App->gui->AddButton(100, 150, App->gui->GetAtlas(), { 435,220,54,54 }, { 490,220,61,60 }, { 552,220,54,54 }, this);
	exit_credits->element_action = EXIT_CREDITS;

	return true;
}

bool j1SceneUI::Deletecredits_UI()
{
	App->gui->DeleteGui(window_credits);
	App->gui->DeleteGui(credits);
	App->gui->DeleteGui(game_made);
	App->gui->DeleteGui(marc);
	App->gui->DeleteGui(pol);
	App->gui->DeleteGui(licence_button);
	App->gui->DeleteGui(exit_credits);

	return true;
}

bool j1SceneUI::Addlicence_UI()
{
	window_licence = App->gui->AddWindow(App->gui->GetAtlas(), 100, 150, { 1,439,831,494 });
	licence_title = App->gui->AddImage(App->gui->addText, 415, 170, { 0,223,250,33 });
	licence = App->gui->AddImage(App->gui->licence, 120, 250, { 0,0,788,345 });
	exit_licence = App->gui->AddButton(100, 150, App->gui->GetAtlas(), { 435,220,54,54 }, { 490,220,61,60 }, { 552,220,54,54 }, this);
	exit_licence->element_action = EXIT_LICENCE;

	return true;
}

bool j1SceneUI::Deletelicence_UI()
{
	App->gui->DeleteGui(window_licence);
	App->gui->DeleteGui(licence_title);
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
	settings_button = App->gui->AddButton(340, 450, App->gui->GetAtlas(), { 0,220,360,72 }, { 1,293,392,80 }, { 1,374,362,63 });
	webpage_button = App->gui->AddButton(25, 650, App->gui->GetAtlas(), { 749,336,106,88 }, { 627,327,118,99 }, { 862,338,102,84 });
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
	App->gui->DeleteGui(webpage_button);
	App->gui->DeleteGui(exit_button);
	return true;
}

bool j1SceneUI::Addingame_UI()
{
	sand = App->gui->AddImage(App->gui->GetAtlas(), 500, 35, { 573,316,34,57 });

	// Elements of this UI
	createtimelives();
	createCOIN_ui();
	
	return true;
}

bool j1SceneUI::Deleteingame_UI()
{
	App->gui->DeleteGui(sand);

	deletetimelives();
	deleteCOIN_ui();
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
		App->audio->PlayFX2(over_button);
		element->state = MOUSEOVER;

	}
	else if (event_type == MOUSE_LEAVE)
	{
		element->state = STANDBY;

	}
	else if (event_type == MOUSE_LEFT_CLICK)
	{
		App->audio->PlayFX2(push_button);
		element->state = CLICKED;
	}
	else if (event_type == MOUSE_LEFT_RELEASE)
	{
		App->audio->PlayFX2(release_button);
		if (element->element_action == START)
		{
			App->scene->sceneintro = false;
			App->scene->introMap = 0;
			App->scene->currentMap = 0;
			App->scene->LevelName(0);
			App->scene->timertime = SDL_GetTicks();
			App->scene->timer = 300;
			App->scene->lives = 3;
			App->scene->player_score = 0;
			p2SString score_info("Score 0");
			App->scene->score->setText(score_info);
			App->scene->coin_number = 0;
			p2SString score_info2("x 0");
			App->scene->coin_counter->setText(score_info2);
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
		else if (element->element_action == CAP)
		{
			if (App->scene->lowfps == false) 
			{
				App->scene->highfps = false;
				App->scene->lowfps = true;
				App->scene->canbehighfps = true;
				iscap = true;
			}
			if (App->scene->highfps == true) 
			{
				App->scene->lowfps = false;
				iscap = false;
			}
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
			Deletepause_UI();
			pause_UI = false;
		}
		else if (element->element_action == EXIT_MENU)
		{
			App->scene->sceneintro = true;
			App->scene->PrepSceneIntro();
			App->scene->pause = false;
			Deletepause_UI();
			Deleteingame_UI();
			pause_UI = false;
		}
		else if (element->element_action == WEBPAGE)
		{
			ShellExecuteA(NULL, "open", "https://marcpt98.github.io/Plataformer-2D/", NULL, NULL, SW_SHOWNORMAL);
		}
	}
	if (element->element_action == SLIDER_BUTTON && event_type == MOUSE_LEFT_CLICK)
	{
		slider_volume = true;
	}
	if (element->element_action == SLIDER_FX_BUTTON && event_type == MOUSE_LEFT_CLICK)
	{
		fx_volume = true;
	}
	
	return true;
}

bool j1SceneUI::createtimelives()
{
	if (App->scene->lives == 3)
	{
		player_face1 = App->gui->AddImage(App->gui->GetAtlas(), 30, 40, { 531,384,59,52 });
		player_face2 = App->gui->AddImage(App->gui->GetAtlas(), 100, 40, { 531,384,59,52 });
		player_face3 = App->gui->AddImage(App->gui->GetAtlas(), 170, 40, { 531,384,59,52 });
		LOG("3");
	}
	else if (App->scene->lives == 2)
	{
		player_face1 = App->gui->AddImage(App->gui->GetAtlas(), 30, 40, { 531,384,59,52 });
		player_face2 = App->gui->AddImage(App->gui->GetAtlas(), 100, 40, { 531,384,59,52 });
		LOG("2");
	}
	else if (App->scene->lives == 1)
	{
		player_face1 = App->gui->AddImage(App->gui->GetAtlas(), 30, 40, { 531,384,59,52 });
		LOG("1");
	}
	else if (App->scene->lives == 0)
	{}

	if (App->scene->timer == 300)
	{
		time_1 = App->gui->AddImage(App->gui->GetAtlas(), 550, 52, { 597,386,26,27 });
		time_2 = App->gui->AddImage(App->gui->GetAtlas(), 568, 52, { 597,386,26,27 });
		time_3 = App->gui->AddImage(App->gui->GetAtlas(), 586, 52, { 597,386,26,27 });
		time_4 = App->gui->AddImage(App->gui->GetAtlas(), 604, 52, { 597,386,26,27 });
		time_5 = App->gui->AddImage(App->gui->GetAtlas(), 622, 52, { 597,386,26,27 });
		time_6 = App->gui->AddImage(App->gui->GetAtlas(), 640, 52, { 597,386,26,27 });
		time_7 = App->gui->AddImage(App->gui->GetAtlas(), 658, 52, { 597,386,26,27 });
		time_8 = App->gui->AddImage(App->gui->GetAtlas(), 676, 52, { 597,386,26,27 });
		time_9 = App->gui->AddImage(App->gui->GetAtlas(), 694, 52, { 597,386,26,27 });
		time_10 = App->gui->AddImage(App->gui->GetAtlas(), 712, 52, { 597,386,26,27 });
	}
	else if (App->scene->timer < 300 && App->scene->timer >= 270)
	{
		time_1 = App->gui->AddImage(App->gui->GetAtlas(), 550, 52, { 597,386,26,27 });
		time_2 = App->gui->AddImage(App->gui->GetAtlas(), 568, 52, { 597,386,26,27 });
		time_3 = App->gui->AddImage(App->gui->GetAtlas(), 586, 52, { 597,386,26,27 });
		time_4 = App->gui->AddImage(App->gui->GetAtlas(), 604, 52, { 597,386,26,27 });
		time_5 = App->gui->AddImage(App->gui->GetAtlas(), 622, 52, { 597,386,26,27 });
		time_6 = App->gui->AddImage(App->gui->GetAtlas(), 640, 52, { 597,386,26,27 });
		time_7 = App->gui->AddImage(App->gui->GetAtlas(), 658, 52, { 597,386,26,27 });
		time_8 = App->gui->AddImage(App->gui->GetAtlas(), 676, 52, { 597,386,26,27 });
		time_9 = App->gui->AddImage(App->gui->GetAtlas(), 694, 52, { 597,386,26,27 });
	}
	else if (App->scene->timer < 270 && App->scene->timer >= 240)
	{
		time_1 = App->gui->AddImage(App->gui->GetAtlas(), 550, 52, { 597,386,26,27 });
		time_2 = App->gui->AddImage(App->gui->GetAtlas(), 568, 52, { 597,386,26,27 });
		time_3 = App->gui->AddImage(App->gui->GetAtlas(), 586, 52, { 597,386,26,27 });
		time_4 = App->gui->AddImage(App->gui->GetAtlas(), 604, 52, { 597,386,26,27 });
		time_5 = App->gui->AddImage(App->gui->GetAtlas(), 622, 52, { 597,386,26,27 });
		time_6 = App->gui->AddImage(App->gui->GetAtlas(), 640, 52, { 597,386,26,27 });
		time_7 = App->gui->AddImage(App->gui->GetAtlas(), 658, 52, { 597,386,26,27 });
		time_8 = App->gui->AddImage(App->gui->GetAtlas(), 676, 52, { 597,386,26,27 });
	}
	else if (App->scene->timer < 240 && App->scene->timer >= 210)
	{
		time_1 = App->gui->AddImage(App->gui->GetAtlas(), 550, 52, { 597,386,26,27 });
		time_2 = App->gui->AddImage(App->gui->GetAtlas(), 568, 52, { 597,386,26,27 });
		time_3 = App->gui->AddImage(App->gui->GetAtlas(), 586, 52, { 597,386,26,27 });
		time_4 = App->gui->AddImage(App->gui->GetAtlas(), 604, 52, { 597,386,26,27 });
		time_5 = App->gui->AddImage(App->gui->GetAtlas(), 622, 52, { 597,386,26,27 });
		time_6 = App->gui->AddImage(App->gui->GetAtlas(), 640, 52, { 597,386,26,27 });
		time_7 = App->gui->AddImage(App->gui->GetAtlas(), 658, 52, { 597,386,26,27 });
	}
	else if (App->scene->timer < 210 && App->scene->timer >= 180)
	{
		time_1 = App->gui->AddImage(App->gui->GetAtlas(), 550, 52, { 597,386,26,27 });
		time_2 = App->gui->AddImage(App->gui->GetAtlas(), 568, 52, { 597,386,26,27 });
		time_3 = App->gui->AddImage(App->gui->GetAtlas(), 586, 52, { 597,386,26,27 });
		time_4 = App->gui->AddImage(App->gui->GetAtlas(), 604, 52, { 597,386,26,27 });
		time_5 = App->gui->AddImage(App->gui->GetAtlas(), 622, 52, { 597,386,26,27 });
		time_6 = App->gui->AddImage(App->gui->GetAtlas(), 640, 52, { 597,386,26,27 });
	}
	else if (App->scene->timer < 180 && App->scene->timer >= 150)
	{
		time_1 = App->gui->AddImage(App->gui->GetAtlas(), 550, 52, { 597,386,26,27 });
		time_2 = App->gui->AddImage(App->gui->GetAtlas(), 568, 52, { 597,386,26,27 });
		time_3 = App->gui->AddImage(App->gui->GetAtlas(), 586, 52, { 597,386,26,27 });
		time_4 = App->gui->AddImage(App->gui->GetAtlas(), 604, 52, { 597,386,26,27 });
		time_5 = App->gui->AddImage(App->gui->GetAtlas(), 622, 52, { 597,386,26,27 });
	}
	else if (App->scene->timer < 150 && App->scene->timer >= 120)
	{
		time_1 = App->gui->AddImage(App->gui->GetAtlas(), 550, 52, { 597,386,26,27 });
		time_2 = App->gui->AddImage(App->gui->GetAtlas(), 568, 52, { 597,386,26,27 });
		time_3 = App->gui->AddImage(App->gui->GetAtlas(), 586, 52, { 597,386,26,27 });
		time_4 = App->gui->AddImage(App->gui->GetAtlas(), 604, 52, { 597,386,26,27 });
	}
	else if (App->scene->timer < 120 && App->scene->timer >= 90)
	{
		time_1 = App->gui->AddImage(App->gui->GetAtlas(), 550, 52, { 597,386,26,27 });
		time_2 = App->gui->AddImage(App->gui->GetAtlas(), 568, 52, { 597,386,26,27 });
		time_3 = App->gui->AddImage(App->gui->GetAtlas(), 586, 52, { 597,386,26,27 });
	}
	else if (App->scene->timer < 90 && App->scene->timer >= 60)
	{
		time_1 = App->gui->AddImage(App->gui->GetAtlas(), 550, 52, { 597,386,26,27 });
		time_2 = App->gui->AddImage(App->gui->GetAtlas(), 568, 52, { 597,386,26,27 });
	}
	else if (App->scene->timer < 60 && App->scene->timer >= 30)
	{
		time_1 = App->gui->AddImage(App->gui->GetAtlas(), 550, 52, { 597,386,26,27 });
	}
	else if (App->scene->timer < 30 && App->scene->timer >= 0)
	{}

	return true;
}

bool j1SceneUI::deletetimelives()
{
	if (App->scene->lives == 3)
	{
		App->gui->DeleteGui(player_face1);
		App->gui->DeleteGui(player_face2);
		App->gui->DeleteGui(player_face3);
		LOG("3");
	}
	else if (App->scene->lives == 2)
	{
		App->gui->DeleteGui(player_face1);
		App->gui->DeleteGui(player_face2);
		LOG("2");
	}
	else if (App->scene->lives == 1)
	{
		App->gui->DeleteGui(player_face1);
		LOG("1");
	}
	else if (App->scene->lives == 0)
	{
	}

	if (App->scene->timer == 300)
	{
		App->gui->DeleteGui(time_1);
		App->gui->DeleteGui(time_2);
		App->gui->DeleteGui(time_3);
		App->gui->DeleteGui(time_4);
		App->gui->DeleteGui(time_5);
		App->gui->DeleteGui(time_6);
		App->gui->DeleteGui(time_7);
		App->gui->DeleteGui(time_8);
		App->gui->DeleteGui(time_9);
		App->gui->DeleteGui(time_10);
	}
	else if (App->scene->timer < 300 && App->scene->timer >= 270)
	{
		App->gui->DeleteGui(time_1);
		App->gui->DeleteGui(time_2);
		App->gui->DeleteGui(time_3);
		App->gui->DeleteGui(time_4);
		App->gui->DeleteGui(time_5);
		App->gui->DeleteGui(time_6);
		App->gui->DeleteGui(time_7);
		App->gui->DeleteGui(time_8);
		App->gui->DeleteGui(time_9);	
	}
	else if (App->scene->timer < 270 && App->scene->timer >= 240)
	{
		App->gui->DeleteGui(time_1);
		App->gui->DeleteGui(time_2);
		App->gui->DeleteGui(time_3);
		App->gui->DeleteGui(time_4);
		App->gui->DeleteGui(time_5);
		App->gui->DeleteGui(time_6);
		App->gui->DeleteGui(time_7);
		App->gui->DeleteGui(time_8);		
	}
	else if (App->scene->timer < 240 && App->scene->timer >= 210)
	{
		App->gui->DeleteGui(time_1);
		App->gui->DeleteGui(time_2);
		App->gui->DeleteGui(time_3);
		App->gui->DeleteGui(time_4);
		App->gui->DeleteGui(time_5);
		App->gui->DeleteGui(time_6);
		App->gui->DeleteGui(time_7);
	}
	else if (App->scene->timer < 210 && App->scene->timer >= 180)
	{
		App->gui->DeleteGui(time_1);
		App->gui->DeleteGui(time_2);
		App->gui->DeleteGui(time_3);
		App->gui->DeleteGui(time_4);
		App->gui->DeleteGui(time_5);
		App->gui->DeleteGui(time_6);
	}
	else if (App->scene->timer < 180 && App->scene->timer >= 150)
	{
		App->gui->DeleteGui(time_1);
		App->gui->DeleteGui(time_2);
		App->gui->DeleteGui(time_3);
		App->gui->DeleteGui(time_4);
		App->gui->DeleteGui(time_5);
	}
	else if (App->scene->timer < 150 && App->scene->timer >= 120)
	{
		App->gui->DeleteGui(time_1);
		App->gui->DeleteGui(time_2);
		App->gui->DeleteGui(time_3);
		App->gui->DeleteGui(time_4);
	}
	else if (App->scene->timer < 120 && App->scene->timer >= 90)
	{
		App->gui->DeleteGui(time_1);
		App->gui->DeleteGui(time_2);
		App->gui->DeleteGui(time_3);
	}
	else if (App->scene->timer < 90 && App->scene->timer >= 60)
	{
		App->gui->DeleteGui(time_1);
		App->gui->DeleteGui(time_2);
	}
	else if (App->scene->timer < 60 && App->scene->timer >= 30)
	{
		App->gui->DeleteGui(time_1);
	}
	else if (App->scene->timer < 30 && App->scene->timer >= 0)
	{}

	return true;
}

bool j1SceneUI::createCOIN_ui()
{
	coin = App->gui->AddImage(App->gui->GetAtlas(), 40, 105, { 490,382,40,49 });
	
	return true;
}

bool j1SceneUI::deleteCOIN_ui() 
{
	App->gui->DeleteGui(coin);
	return true;
}

bool j1SceneUI::reset() 
{
	bool ret = false;
	if (player_face1 != nullptr && player_face2 != nullptr && player_face3 != nullptr && time_1 != nullptr && sand != nullptr && time_2 != nullptr && time_3 != nullptr && time_4 != nullptr && time_5 != nullptr && time_6 != nullptr && time_7 != nullptr && time_8 != nullptr && time_9 != nullptr && time_10 != nullptr && coin != nullptr) 
	{
		ret = true;
	}

	return ret;
}
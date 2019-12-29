#include "j1Window.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Scene.h"
#include "j1Map.h"
#include "j1App.h"
#include "p2Log.h"
#include "j1Console.h"
#include "j1Fonts.h"
#include "j1Scene_UI.h"
#include "j1Gui.h"
#include "UI_element.h"
#include "UI_Image.h"


j1Console::j1Console()
{
	name.create("console");
}

j1Console::~j1Console()
{}

bool j1Console::Start()
{
	opened = false;
	Text_font = App->font->Load("fonts/ARCADECLASSIC.ttf", 20);
	textmax = 4;
	return true;
}

bool j1Console::CleanUp()
{

	return true;
}

bool j1Console::PreUpdate(float dt)
{

	return true;
}

bool j1Console::Update(float dt)
{
	if (App->input->GetKey(SDL_SCANCODE_GRAVE) == KEY_DOWN)
	{
		if (opened == false)
		{
			Open();
			textdistance = 5;
			opened = true;
		}
		else if (opened == true)
		{
			Close();
			opened = false;
		}
	}
	if (App->console->opened == true)
	{
		App->render->DrawQuad({ -App->render->camera.x, -App->render->camera.y + 160, App->win->width, 220 }, 0, 0, 0, 200);

		Checkinput();
	}

	return true;
}

bool j1Console::PostUpdate(float dt)
{
	
	return true;
}

void j1Console::Open()
{
	App->scene->pause = true;
	opened_text = App->gui->AddText("CONSOLE OPENED", 5, 170, Text_font, { 255, 255, 255, });
	insert_text = App->gui->AddText("INSERT TEXT HERE", 5, 345, Text_font, { 255, 255, 255, });
}

void j1Console::Close()
{
	App->scene->pause = false;

	if (opened_text != nullptr)
	{
		App->gui->DeleteGui(opened_text);
	}
	currenttext = 0;

	if (insert_text != nullptr)
	{
		App->gui->DeleteGui(insert_text);
	}
	if (text_1 != nullptr)
	{
		App->gui->DeleteGui(text_1);
		firstletter = false;

		text_1_god = false;
		text_1_quit = false;
		text_1_map = false;
		text_1_FPS = false;
		text_1_list = false;
	}
	if (text_2 != nullptr)
	{
		App->gui->DeleteGui(text_2);
		secondletter = false;

		text_2_god = false;
		text_2_quit = false;
		text_2_map = false;
		text_2_FPS = false;
		text_2_list = false;
	}
	if (text_3 != nullptr)
	{
		App->gui->DeleteGui(text_3);
		thirdletter = false;

		text_3_god = false;
		text_3_quit = false;
		text_3_map = false;
		text_3_FPS = false;
		text_3_list = false;
	}
	if (text_4 != nullptr)
	{
		App->gui->DeleteGui(text_4);
		forthletter = false;

		text_4_quit = false;
		text_4_map1 = false;
		text_4_map2 = false;
		text_4_FPS30 = false;
		text_4_FPS60 = false;
		text_4_list = false;
	}

	if (img_list != nullptr)
	{
		App->gui->DeleteGui(img_list);
		img_list = nullptr;
	}
}

bool j1Console::Checkinput()
{
	if (currenttext <= textmax)
	{
		if (App->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN)
		{
			if (forthletter == true)
			{
				App->gui->DeleteGui(text_4);
				forthletter = false;

				text_4_quit = false;
				text_4_map1 = false;
				text_4_map2 = false;
				text_4_FPS30 = false;
				text_4_FPS60 = false;
				text_4_list = false;

				currenttext--;
				textdistance -= 13;
			}
			else if (thirdletter == true)
			{
				App->gui->DeleteGui(text_3);
				thirdletter = false;

				text_3_god = false;
				text_3_quit = false;
				text_3_map = false;
				text_3_FPS = false;
				text_3_list = false;

				currenttext--;
				textdistance -= 13;
			}
			else if (secondletter == true)
			{
				App->gui->DeleteGui(text_2);
				secondletter = false;

				text_2_god = false;
				text_2_quit = false;
				text_2_map = false;
				text_2_FPS = false;
				text_2_list = false;

				currenttext--;
				textdistance -= 13;
			}
			else if (firstletter == true)
			{
				App->gui->DeleteGui(text_1);
				firstletter = false;

				text_1_god = false;
				text_1_quit = false;
				text_1_map = false;
				text_1_FPS = false;
				text_1_list = false;

				currenttext--;
				textdistance -= 13;

			}
		}
		
		if (App->input->GetKey(SDL_SCANCODE_RETURN) == KEY_DOWN)
		{
			if (text_1_god == true && text_2_god == true && text_3_god == true && forthletter == false)
			{
				godConsole = true;
			}
			else if (text_1_quit == true && text_2_quit == true && text_3_quit == true && text_4_quit == true)
			{
				App->sceneui->exit = true;
			}
			else if (text_1_map == true && text_2_map == true && text_3_map == true && text_4_map1 == true)
			{
				loadmap1();
			}
			else if (text_1_map == true && text_2_map == true && text_3_map == true && text_4_map2 == true)
			{
				loadmap2();
			}
			else if (text_1_FPS == true && text_2_FPS == true && text_3_FPS == true && text_4_FPS30 == true)
			{
				App->scene->highfps = false;
				App->scene->lowfps = true;
				App->scene->canbehighfps = true;
				App->sceneui->iscap = true;
			}
			else if (text_1_FPS == true && text_2_FPS == true && text_3_FPS == true && text_4_FPS60 == true)
			{
				App->scene->lowfps = false;
				App->sceneui->iscap = false;
			}
			else if (text_1_list == true && text_2_list == true && text_3_list == true && text_4_list == true)
			{
				if (img_list == nullptr)
				{
					img_list = App->gui->AddImage(App->gui->list, 5, 205, { 0,0,282,108 });
				}
			}
		}

		if (firstletter == false)
		{
			if (App->input->GetKey(SDL_SCANCODE_G) == KEY_DOWN)
			{
				if (insert_text != nullptr)
				{
					App->gui->DeleteGui(insert_text);
				}

				text_1 = App->gui->AddText("G", textdistance, 345, Text_font, { 255, 255, 255, });
				textdistance += 13;
				currenttext++;
				text_1_god = true;

				firstletter = true;
			}
			if (App->input->GetKey(SDL_SCANCODE_Q) == KEY_DOWN)
			{
				if (insert_text != nullptr)
				{
					App->gui->DeleteGui(insert_text);
				}

				text_1 = App->gui->AddText("Q", textdistance, 345, Text_font, { 255, 255, 255, });
				textdistance += 13;
				currenttext++;
				text_1_quit = true;

				firstletter = true;
			}
			if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN)
			{
				if (insert_text != nullptr)
				{
					App->gui->DeleteGui(insert_text);
				}

				text_1 = App->gui->AddText("M", textdistance, 345, Text_font, { 255, 255, 255, });
				textdistance += 13;
				currenttext++;
				text_1_map = true;

				firstletter = true;
			}
			if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN)
			{
				if (insert_text != nullptr)
				{
					App->gui->DeleteGui(insert_text);
				}

				text_1 = App->gui->AddText("F", textdistance, 345, Text_font, { 255, 255, 255, });
				textdistance += 13;
				currenttext++;
				text_1_FPS = true;

				firstletter = true;
			}
			if (App->input->GetKey(SDL_SCANCODE_L) == KEY_DOWN)
			{
				if (insert_text != nullptr)
				{
					App->gui->DeleteGui(insert_text);
				}

				text_1 = App->gui->AddText("L", textdistance, 345, Text_font, { 255, 255, 255, });
				textdistance += 13;
				currenttext++;
				text_1_list = true;

				firstletter = true;
			}
			
		}
		
		else if (secondletter == false)
		{
			if (App->input->GetKey(SDL_SCANCODE_O) == KEY_DOWN)
			{
				text_2 = App->gui->AddText("O", textdistance, 345, Text_font, { 255, 255, 255, });
				textdistance += 13;
				currenttext++;
				text_2_god = true;

				secondletter = true;
			}
			if (App->input->GetKey(SDL_SCANCODE_U) == KEY_DOWN)
			{
				text_2 = App->gui->AddText("U", textdistance, 345, Text_font, { 255, 255, 255, });
				textdistance += 13;
				currenttext++;
				text_2_quit = true;

				secondletter = true;
			}
			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_DOWN)
			{
				text_2 = App->gui->AddText("A", textdistance, 345, Text_font, { 255, 255, 255, });
				textdistance += 13;
				currenttext++;
				text_2_map = true;

				secondletter = true;
			}
			if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
			{
				text_2 = App->gui->AddText("P", textdistance, 345, Text_font, { 255, 255, 255, });
				textdistance += 13;
				currenttext++;
				text_2_FPS = true;

				secondletter = true;
			}
			if (App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)
			{
				text_2 = App->gui->AddText("I", textdistance, 345, Text_font, { 255, 255, 255, });
				textdistance += 13;
				currenttext++;
				text_2_list = true;

				secondletter = true;
			}
		}
		
		else if (thirdletter == false)
		{
			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_DOWN)
			{
				text_3 = App->gui->AddText("D", textdistance, 345, Text_font, { 255, 255, 255, });
				textdistance += 13;
				currenttext++;
				text_3_god = true;

				thirdletter = true;
			}
			if (App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)
			{
				text_3 = App->gui->AddText("I", textdistance, 345, Text_font, { 255, 255, 255, });
				textdistance += 13;
				currenttext++;
				text_3_quit = true;

				thirdletter = true;
			}
			if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
			{
				text_3 = App->gui->AddText("P", textdistance, 345, Text_font, { 255, 255, 255, });
				textdistance += 13;
				currenttext++;
				text_3_map = true;

				thirdletter = true;
			}
			if (App->input->GetKey(SDL_SCANCODE_S) == KEY_DOWN)
			{
				text_3 = App->gui->AddText("S", textdistance, 345, Text_font, { 255, 255, 255, });
				textdistance += 13;
				currenttext++;
				text_3_FPS = true;
				text_3_list = true;

				thirdletter = true;
			}
		}
		
		else if (forthletter == false)
		{
			if (App->input->GetKey(SDL_SCANCODE_T) == KEY_DOWN)
			{
				text_4 = App->gui->AddText("T", textdistance, 345, Text_font, { 255, 255, 255, });
				textdistance += 13;
				currenttext++;
				text_4_quit = true;
				text_4_list = true;

				forthletter = true;
			}
			if (App->input->GetKey(SDL_SCANCODE_1) == KEY_DOWN)
			{
				text_4 = App->gui->AddText("1", textdistance, 345, Text_font, { 255, 255, 255, });
				textdistance += 13;
				currenttext++;
				text_4_map1 = true;
				text_4_FPS30 = true;

				forthletter = true;
			}
			if (App->input->GetKey(SDL_SCANCODE_2) == KEY_DOWN)
			{
				text_4 = App->gui->AddText("2", textdistance, 345, Text_font, { 255, 255, 255, });
				textdistance += 13;
				currenttext++;
				text_4_map2 = true;
				text_4_FPS60 = true;

				forthletter = true;
			}
		}
	}

	return true;
}

bool j1Console::loadmap1()
{
	if (App->sceneui->level_2 == true)
	{
		App->sceneui->Deleteingame_UI();
		App->sceneui->level_2 = false;
	}
	App->sceneui->level_1 = true;

	if (App->scene->sceneintro == true)
	{
		App->sceneui->Deletesceneintro_UI();
	}
	App->scene->timertime = SDL_GetTicks();
	App->scene->timer = 300;
	App->scene->lives = 3;
	App->scene->player_score = 0;
	p2SString score_info("Score 0");
	App->scene->score->setText(score_info);
	LOG("CREAR");
	App->scene->coin_number = 0;
	p2SString score_info2("x 0");
	App->scene->coin_counter->setText(score_info2);
	App->scene->sceneintro = false;
	App->scene->currentMap = 0;
	App->scene->LevelName(0);
	App->sceneui->Addingame_UI();

	return true;
}

bool j1Console::loadmap2()
{
	if (App->sceneui->level_1 == true)
	{
		App->sceneui->Deleteingame_UI();
		App->sceneui->level_1 = false;
	}
	App->scene->timertime = SDL_GetTicks();
	App->scene->timer = 300;
	App->scene->lives = 3;

	App->scene->player_score = 0;
	p2SString score_info("Score 0");
	App->scene->score->setText(score_info);
	LOG("CREAR");
	App->scene->coin_number = 0;
	p2SString score_info2("x 0");
	App->scene->coin_counter->setText(score_info2);

	App->sceneui->level_2 = true;
	if (App->scene->sceneintro == true)
	{
		App->sceneui->Deletesceneintro_UI();
	}
	App->scene->sceneintro = false;
	App->scene->currentMap = 1;
	App->scene->LevelName(1);
	App->sceneui->Addingame_UI();

	return true;
}
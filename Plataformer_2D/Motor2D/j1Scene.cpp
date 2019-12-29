#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Input.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"
#include "j1Map.h"
#include "j1Scene.h"
#include "j1Player.h"
#include "j1Colliders.h"
#include "j1EntityManager.h"
#include "j1Particles.h"
#include "j1PathFinding.h"
#include "j1Gui.h"
#include "j1Fonts.h"
#include "UI_element.h"
#include "UI_Image.h"
#include "UI_text.h"
#include "j1Scene_UI.h"

j1Scene::j1Scene() : j1Module()
{
	name.create("scene");
}

// Destructor
j1Scene::~j1Scene()
{}

// Called before render is available
bool j1Scene::Awake(pugi::xml_node& config)
{
	LOG("Loading Scene");

	bool ret = true;

	for (pugi::xml_node map = config.child("map_name"); map; map = map.next_sibling("map_name"))
	{
		p2SString* data = new p2SString;

		data->create(map.attribute("name").as_string());
		map_names.add(data);
	}

	for (pugi::xml_node music = config.child("music_name"); music; music = music.next_sibling("music_name"))
	{
		p2SString* data = new p2SString;

		data->create(music.attribute("name").as_string());
		music_names.add(data);
	}

	map_1 = map_names[0];
	map_2 = map_names[1];
	music_1 = music_names[0];
	music_2 = music_names[1];
	music_scene_intro = music_names[2];

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	if (App->map->Load(map_1->GetString()) == true)
	{
		int w, h;
		uchar* data = NULL;
		if (App->map->CreateWalkabilityMap(w, h, &data))
			App->path->SetMap(w, h, data);

		RELEASE_ARRAY(data);
	}

	// Player
	currentMap = 0;
	createEntities();
	score_lives = 1000;
	player_score = 0;
	LOG("CREAR");
	//This is to reset the player score
	App->scene->firsttime = true;
	App->scene->score = App->gui->AddText("Hello World", 830, 50, App->font->Load("fonts/ARCADECLASSIC.ttf", 36), { 255, 255, 255, 255 }, this);
	App->scene->score->setOutlined(true);
	p2SString score_info("Score %i", App->scene->player_score);
	App->scene->score->setText(score_info);
	App->scene->score->BlitElement();
	
	App->scene->coin_counter = App->gui->AddText("Hello World", 100, 120, App->font->Load("fonts/ARCADECLASSIC.ttf", 20), { 255, 255, 255, 255 }, this);
	App->scene->coin_counter->setOutlined(true);
	p2SString score_info2("x %i", App->scene->coin_number);
	App->scene->coin_counter->setText(score_info2);
	App->scene->coin_counter->BlitElement();
	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	BROFILER_CATEGORY("PreupdateScene", Profiler::Color::Indigo)

	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	if (player_score >= score_lives && lives<3) {
		App->sceneui->deletetimelives();
		more_lives = true;
		LOG("%i", player_score); LOG("%i", score_lives);
		lives++;
		score_lives = score_lives + 1000;
		App->sceneui->createtimelives();
		
	}
	LOG("%i", lives);

	if (coin_counter == nullptr) {
		LOG("NULLPTR");
	}
	if (player_dead == true)
	{
		int a = 0;
	}
	BROFILER_CATEGORY("UpdateScene", Profiler::Color::Peru)
	if (/*firsttime == true &&*/ diferent_score == true)
	{
		LOG("DESTRUIR");
		App->gui->DeleteGui(score); 
		firsttime = false;
	}
	if (diferent_coins == true && player_dead == false)
	{
		App->gui->DeleteGui(coin_counter);
	}

	if (timer_pts == 1 && diferent_score == true || player_dead == true)
	{
		//App->gui->DeleteGui(score);
		timer_pts = 0;
	}
	if (player_dead == true)
	{
		App->gui->DeleteGui(score);
		App->gui->DeleteGui(coin_counter);
		
	}
	if (sceneintro == false && pause == false)
	{
		/*if (App->input->GetKey(SDL_SCANCODE_G) == KEY_REPEAT)
		{
			timer--;
		}*/
		if (SDL_GetTicks() - timertime >= 1000)
		{
			/*if (time_text != nullptr)
			{
				App->gui->DeleteGui(time_text);
			}*/
			/*time_text = App->gui->AddText("Hello World", 530, 50, App->font->Load("fonts/ARCADECLASSIC.ttf", 36), { 255, 255, 255, 255 }, this);
			time_text->setOutlined(true);
			p2SString timer_info("Time %i", timer);
			time_text->setText(timer_info);
			time_text->BlitElement();*/
			timertime = SDL_GetTicks();
			timer--;
		}
		if (timer < 300 && App->sceneui->time_10 != nullptr)
		{
			App->gui->DeleteGui(App->sceneui->time_10);
		}
		if (timer < 270 && App->sceneui->time_9 != nullptr)
		{
			App->gui->DeleteGui(App->sceneui->time_9);
		}
		if (timer < 240 && App->sceneui->time_8 != nullptr)
		{
			App->gui->DeleteGui(App->sceneui->time_8);
		}
		if (timer < 210 && App->sceneui->time_7 != nullptr)
		{
			App->gui->DeleteGui(App->sceneui->time_7);
		}
		if (timer < 180 && App->sceneui->time_6 != nullptr)
		{
			App->gui->DeleteGui(App->sceneui->time_6);
		}
		if (timer < 150 && App->sceneui->time_5 != nullptr)
		{
			App->gui->DeleteGui(App->sceneui->time_5);
		}
		if (timer < 120 && App->sceneui->time_4 != nullptr)
		{
			App->gui->DeleteGui(App->sceneui->time_4);
		}
		if (timer < 90 && App->sceneui->time_3 != nullptr)
		{
			App->gui->DeleteGui(App->sceneui->time_3);
		}
		if (timer < 60 && App->sceneui->time_2 != nullptr)
		{
			App->gui->DeleteGui(App->sceneui->time_2);
		}
		if (timer < 30 && App->sceneui->time_1 != nullptr)
		{
			App->gui->DeleteGui(App->sceneui->time_1);
		}

		if (timer <= 0)
		{
			sceneintro = true;
			PrepSceneIntro();
			App->sceneui->Deleteingame_UI();
		}
	}

	if (diferent_score == true || player_dead==true)
	{
		score = App->gui->AddText("Hello World", 830, 50, App->font->Load("fonts/ARCADECLASSIC.ttf", 36), { 255, 255, 255, 255 }, this);
		score->setOutlined(true);
		p2SString score_info("Score %i", player_score);
		score->setText(score_info);
		score->BlitElement();
		timer_pts++;
	}
	diferent_score = false;

	if (diferent_coins == true || player_dead == true)
	{
		coin_counter = App->gui->AddText("Hello World", 100, 120, App->font->Load("fonts/ARCADECLASSIC.ttf", 20), { 255, 255, 255, 255 }, this);
		coin_counter->setOutlined(true);
		p2SString score_info2("x %i", coin_number);
		coin_counter->setText(score_info2);
		coin_counter->BlitElement();
		timer_coins++;
	}
	diferent_coins = false;

	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
	{
		App->load();
		App->sceneui->Deleteingame_UI();
		App->sceneui->Addingame_UI();
	}

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->want_save = true;

	// Change map
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		if (App->sceneui->level_2 == true)
		{
			App->sceneui->Deleteingame_UI();
			App->sceneui->level_2 = false;
		}
		App->sceneui->level_1 = true;
		
		if (sceneintro == true)
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
		App->scene->coin_number= 0;
		p2SString score_info2("x 0");
		App->scene->coin_counter->setText(score_info2);
		sceneintro = false;
		currentMap = 0;
		LevelName(0);
		App->sceneui->Addingame_UI();
	}

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
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
		if (sceneintro == true)
		{
			App->sceneui->Deletesceneintro_UI();
		}
		sceneintro = false;
		currentMap = 1;
		LevelName(1);
		App->sceneui->Addingame_UI();
	}
	// Start from the beginning of the current level
	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN || player_dead == true && CheckPoint == false)
	{
		
		if (player_dead == true)
		{
			lives--;
		}

		App->sceneui->Deleteingame_UI();

		if (player_dead == false)
		{
			App->scene->timertime = SDL_GetTicks();
			App->scene->timer = 300;
			App->scene->lives = 3;
		}
		App->scene->player_score = 0;
		p2SString score_info("Score 0");
		App->scene->score->setText(score_info);

		App->scene->coin_number = 0;
		p2SString score_info2("x 0");
		App->scene->coin_counter->setText(score_info2);

		App->sceneui->Addingame_UI();
		if (sceneintro == true)
		{
			App->sceneui->Deletesceneintro_UI();
		}
		sceneintro = false;
		if (currentMap == 0)
		{
			LevelName(0);
		}
		if (currentMap == 1)
		{
			LevelName(1);
		}
		player_dead = false;
	}
	
	if (CheckPoint == true && player_dead == true)
	{
		App->load();
		player_dead = false;
	}

	if (player_map_next == true)
	{
		if (currentMap == 0)
		{
			currentMap = 1;
			LevelName(1);	
		}
		else if (currentMap == 1)
		{
			currentMap = 0;
			LevelName(0);
		}
		player_map_next = false;
	}

	if (sceneintro == false)
	{
		App->map->Draw();
	}

	if (canbehighfps == true) {
		highfps = true;
	}
	if (App->input->GetKey(SDL_SCANCODE_F11) == KEY_DOWN)
	{
		if (lowfps == false) {
			highfps = false;
			lowfps = true;
			canbehighfps = true;
		}
		if (highfps == true) {
			lowfps = false;
		}
	}

	//Live system
	if ((lives == 2  || lives == 1 || lives == 0) && App->sceneui->player_face3 != nullptr)
	{
		App->gui->DeleteGui(App->sceneui->player_face3);
	}
	if ((lives == 1 || lives == 0) && App->sceneui->player_face2 != nullptr)
	{
		App->gui->DeleteGui(App->sceneui->player_face2);
	}
	if (lives == 0 && App->sceneui->player_face1 != nullptr)
	{
		App->gui->DeleteGui(App->sceneui->player_face1);
	}
	if (lives == -1)
	{
		sceneintro = true;
		App->map->CleanUp();
		App->particles->CleanUp();
		App->colliders->CleanUp();
		App->entity->CleanUp();
		if (currentMap == 1) 
		{
			App->audio->UnloadMusic(music_1->GetString());
		}	
		if (currentMap == 0)
		{
			App->audio->UnloadMusic(music_2->GetString());
		}
		App->sceneui->Addsceneintro_UI();
		App->audio->PlayMusic(music_scene_intro->GetString());
		coin_number = 0;
		player_score = 0;
		App->gui->DeleteGui(score);
		//App->gui->DeleteGui(coin_counter);
		LOG("DESTRUIR");
		lives = 3;
	}
	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);
	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:%d,%d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count(),
					map_coordinates.x, map_coordinates.y);

	App->win->SetTitle(title.GetString());

	App->win->SetTitle(title.GetString());

	return true;
}

// Called each loop iteration
bool j1Scene::PostUpdate()
{
	BROFILER_CATEGORY("PreupdateScene", Profiler::Color::Snow)

	bool ret = true;

	if (App->sceneui->exit == true)
		ret = false;

	return ret;
}

// Called before quitting
bool j1Scene::CleanUp()
{
	LOG("Freeing scene");
	App->audio->CleanUp();

	return true;
}

// Say which map and music has to be loaded
bool j1Scene::LevelName(int pos)
{
	App->map->ChangeMapMusic(map_names[pos], music_names[pos]);

	return true;
}

bool j1Scene::createEntities()
{
	if (App->scene->currentMap == 0)
	{
		// Player
		App->entity->CreateEntity(j1Entity::entityType::PLAYER, 300, 0);

		// Ghost
		App->entity->CreateEntity(j1Entity::entityType::FLYING_ENEMY, 1850, 100);

		//Slime
		App->entity->CreateEntity(j1Entity::entityType::LAND_ENEMY, 1050, 550); 
		//App->entity->CreateEntity(j1Entity::entityType::LAND_ENEMY, 2950, 550);
		App->entity->CreateEntity(j1Entity::entityType::LAND_ENEMY, 3050, 100);
		App->entity->CreateEntity(j1Entity::entityType::LAND_ENEMY, 6000, 600);
		App->entity->CreateEntity(j1Entity::entityType::LAND_ENEMY, 5900, 600);

		//CheckPoints
		App->entity->CreateEntity(j1Entity::entityType::CHECKPOINT, 2300, 211);
		App->entity->CreateEntity(j1Entity::entityType::CHECKPOINT, 3850, 146);
		App->entity->CreateEntity(j1Entity::entityType::CHECKPOINT, 5106, 140);
		App->entity->CreateEntity(j1Entity::entityType::CHECKPOINT, 300, 594);

		//Coins
		App->entity->CreateEntity(j1Entity::entityType::COIN, 687, 550);
		App->entity->CreateEntity(j1Entity::entityType::COIN, 627, 550);
		App->entity->CreateEntity(j1Entity::entityType::COIN, 1460, 600);
		App->entity->CreateEntity(j1Entity::entityType::COIN, 1587, 550);
		App->entity->CreateEntity(j1Entity::entityType::COIN, 2087, 230);
		App->entity->CreateEntity(j1Entity::entityType::COIN, 2600, 430);
		App->entity->CreateEntity(j1Entity::entityType::COIN, 2660, 480);
		App->entity->CreateEntity(j1Entity::entityType::COIN, 3400, 290);
		App->entity->CreateEntity(j1Entity::entityType::COIN, 3650, 50);
		App->entity->CreateEntity(j1Entity::entityType::COIN, 4480, 150);
		App->entity->CreateEntity(j1Entity::entityType::COIN, 4580, 180);
		App->entity->CreateEntity(j1Entity::entityType::COIN, 4640, 290);
		App->entity->CreateEntity(j1Entity::entityType::COIN, 5310, 290);
	}
	if (App->scene->currentMap == 1)
	{
		// Player
		App->entity->CreateEntity(j1Entity::entityType::PLAYER, 300, 0);

		// Ghost
		App->entity->CreateEntity(j1Entity::entityType::FLYING_ENEMY, 2500, 150);
		App->entity->CreateEntity(j1Entity::entityType::FLYING_ENEMY, 6000, 200);

		//Slime
		App->entity->CreateEntity(j1Entity::entityType::LAND_ENEMY, 800, 440);
		App->entity->CreateEntity(j1Entity::entityType::LAND_ENEMY, 3690, 100);
		App->entity->CreateEntity(j1Entity::entityType::LAND_ENEMY, 5390, 600);

		//CheckPoints
		App->entity->CreateEntity(j1Entity::entityType::CHECKPOINT, 300, 520);
		App->entity->CreateEntity(j1Entity::entityType::CHECKPOINT, 2800, 431);
		App->entity->CreateEntity(j1Entity::entityType::CHECKPOINT, 3650, 110);
		App->entity->CreateEntity(j1Entity::entityType::CHECKPOINT, 5000, 105);

		//Coins
		App->entity->CreateEntity(j1Entity::entityType::COIN, 547, 450);
		App->entity->CreateEntity(j1Entity::entityType::COIN, 1085, 400);
		App->entity->CreateEntity(j1Entity::entityType::COIN, 1785, 340);
		App->entity->CreateEntity(j1Entity::entityType::COIN, 1705, 340);
		App->entity->CreateEntity(j1Entity::entityType::COIN, 2450, 340);
		App->entity->CreateEntity(j1Entity::entityType::COIN, 3105, 580);
		App->entity->CreateEntity(j1Entity::entityType::COIN, 3955, 450);
		App->entity->CreateEntity(j1Entity::entityType::COIN, 4355, 350);
		App->entity->CreateEntity(j1Entity::entityType::COIN, 4755, 250);
		App->entity->CreateEntity(j1Entity::entityType::COIN, 5055, 150);
		App->entity->CreateEntity(j1Entity::entityType::COIN, 5355, 450);
		App->entity->CreateEntity(j1Entity::entityType::COIN, 5635, 110);
		App->entity->CreateEntity(j1Entity::entityType::COIN, 6082, 270);
		App->entity->CreateEntity(j1Entity::entityType::COIN, 6082, 493);
		App->entity->CreateEntity(j1Entity::entityType::COIN, 6082, 493);
	}

	return true;
}

bool j1Scene::PrepSceneIntro()
{
	App->entity->CleanUp();
	App->particles->CleanUp();
	App->colliders->CleanUp();
	App->map->CleanUp();
	App->sceneui->Addsceneintro_UI();
	App->audio->PlayMusic(music_scene_intro->GetString());

	return true;
}

// Load Game State
bool j1Scene::load(pugi::xml_node& savegame)
{
	// Loading SECOND map from SCENE_INTRO
	if (introMap == 1 && savegame.child("map").attribute("actual").as_int() != 0)
	{
		currentMap = 1;
		App->audio->UnloadMusic(music_scene_intro->GetString());
		App->map->Load("Level_2.tmx");
		App->particles->Start();
		App->audio->PlayMusic(music_2->GetString());
	}

	// Loading FIRST map from SCENE_INTRO
	if (introMap == 1 && savegame.child("map").attribute("actual").as_int() != 1)
	{
		currentMap = 0;
		App->audio->UnloadMusic(music_scene_intro->GetString());
		App->map->Load("Level_1.tmx");
		App->particles->Start();
		App->audio->PlayMusic(music_1->GetString());
	}

	// Loading SECOND map from FIRST map
	if (currentMap == 0 && savegame.child("map").attribute("actual").as_int() != 0)
	{
		currentMap = 1;
		App->map->CleanUp();
		App->particles->CleanUp();
		App->audio->UnloadMusic(music_1->GetString());
		App->map->Load(map_2->GetString());
		App->particles->Start();
		App->audio->PlayMusic(music_2->GetString());
	}

	// Loading FIRST map from SECOND map
	if (currentMap == 1 && savegame.child("map").attribute("actual").as_int() != 1)
	{
		currentMap = 0;
		App->map->CleanUp();
		App->particles->CleanUp();
		App->audio->UnloadMusic(music_2->GetString());
		App->map->Load(map_1->GetString());
		App->particles->Start();
		App->audio->PlayMusic(music_1->GetString());
	}

	// Loading FIRST map from FIRST map
	if (currentMap == 0 && savegame.child("map").attribute("actual").as_int() == 0)
	{
		App->map->CleanUp();
		App->colliders->CleanUp();
		App->map->Load(map_1->GetString());
	}

	// Loading SECOND map from SECOND map
	if (currentMap == 1 && savegame.child("map").attribute("actual").as_int() == 1)
	{
		App->map->CleanUp();
		App->colliders->CleanUp();
		App->map->Load(map_2->GetString());
	}

	player_score = savegame.child("map2").attribute("points").as_int();
	coin_number = savegame.child("map5").attribute("coin_number").as_int();
	if (player_dead == true)
	{
		lives = savegame.child("map3").attribute("lives").as_int();
		if (more_lives == true)
		{
			//lives++;
			more_lives = false;
		}
		else 
		{
			lives--;
		}
		App->sceneui->Deleteingame_UI();
		App->sceneui->Addingame_UI();
	}
	else
	{
		lives = savegame.child("map3").attribute("lives").as_int();
	}
	timer = savegame.child("map4").attribute("timer").as_int();
	
	//This is to reset the player score
	App->gui->DeleteGui(score);
	score = App->gui->AddText("Hello World", 830, 50, App->font->Load("fonts/ARCADECLASSIC.ttf", 36), { 255, 255, 255, 255 }, this);
	score->setOutlined(true);
	p2SString score_info("Score %i", player_score);
	score->setText(score_info);
	score->BlitElement();
	LOG("CREAR");

	//This is to reset the player coins
	App->gui->DeleteGui(coin_counter);
	coin_counter = App->gui->AddText("Hello World", 100, 120, App->font->Load("fonts/ARCADECLASSIC.ttf", 20), { 255, 255, 255, 255 }, this);
	coin_counter->setOutlined(true);
	p2SString score_info2("x %i", coin_number);
	coin_counter->setText(score_info2);
	coin_counter->BlitElement();
	return true;
}

// Save Game State
bool j1Scene::save(pugi::xml_node& savegame)
{
	if (currentMap == 0)
	{
		savegame.append_child("map").append_attribute("actual").set_value(0);
	}
	if (currentMap == 1)
	{
		savegame.append_child("map").append_attribute("actual").set_value(1);
	}

	savegame.append_child("map2").append_attribute("points").set_value(player_score);
	savegame.append_child("map3").append_attribute("lives").set_value(lives);
	savegame.append_child("map4").append_attribute("timer").set_value(timer);
	savegame.append_child("map5").append_attribute("coin_number").set_value(coin_number);
	return true;
}
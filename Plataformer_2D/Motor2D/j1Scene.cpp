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

	App->sceneui->Addingame_UI();

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
	BROFILER_CATEGORY("UpdateScene", Profiler::Color::Peru)
	// Gui ---
	if (App->input->GetKey(SDL_SCANCODE_I) == KEY_DOWN)
	{
		App->gui->AddButton(100, 100, NULL, { 642,169,229,69 }, { 0,113,229,69 }, { 411,169,229,69 }, this);
		App->gui->AddText("Hello World", 200, 200, App->font->Load("fonts/open_sans/OpenSans-Regular.ttf", 25), { 255, 0, 0, 255 }, this);
	}

	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->want_load = true;

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->want_save = true;

	// Change map
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		sceneintro = false;
		currentMap = 0;
		LevelName(0);
	}

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		sceneintro = false;
		currentMap = 1;
		LevelName(1);
	}

	// Start from the beginning of the current level
	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN || player_dead == true && CheckPoint == false)
	{
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

	if (App->input->GetKey(SDL_SCANCODE_M) == KEY_DOWN)
	{
		sceneintro = true;
		PrepSceneIntro();
	}

	if (CheckPoint == true && player_dead == true)
	{
		App->want_load = true;
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

	//Game pause
	if (App->input->GetKey(SDL_SCANCODE_P) == KEY_DOWN)
	{
		if (pause == false) {
			pause = true;
			App->audio->setMusicVolume(0.2);
		}
		else {
			pause = false;
			App->audio->setMusicVolume(1);
		}
		
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

	if(App->input->GetKey(SDL_SCANCODE_ESCAPE) == KEY_DOWN)
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
	App->audio->PlayMusic(music_scene_intro->GetString());	// WE have to unload this song/////////////////////////////////////////////////////////////////////////////////////////////

	return true;
}

// Load Game State
bool j1Scene::load(pugi::xml_node& savegame)
{
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

	return true;
}


//Ui events
bool j1Scene::OnUIEvent(UI_element* element, event_type event_type)
{
	if (event_type == MOUSE_ENTER || event_type == MOUSE_LEFT_RELEASE || event_type == MOUSE_RIGHT_RELEASE)
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
	else if (event_type == MOUSE_RIGHT_CLICK)
	{
	}

	return true;
}

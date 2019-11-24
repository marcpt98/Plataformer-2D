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
#include "j1Enemy.h"
#include "j1Colliders.h"
#include "j1EntityManager.h"
#include "j1Particles.h"

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

	bool ret = true;

	return ret;
}

// Called before the first frame
bool j1Scene::Start()
{
	App->map->Load("Level_1.tmx");
	App->audio->PlayMusic("audio/music/music_level_1.ogg");

	// Player
	currentMap = 0;
	App->map->createEntities();

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



	if (App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->want_load = true;

	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->want_save = true;

	// Change map
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		currentMap = 0;
		LevelName(0);
	}

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		currentMap = 1;
		LevelName(1);
	}

	// Start from the beginning of the current level
	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN || player_dead == true)
	{
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

	App->map->Draw();

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

	int x, y;
	App->input->GetMousePosition(x, y);
	iPoint map_coordinates = App->map->WorldToMap(x - App->render->camera.x, y - App->render->camera.y);
	p2SString title("Map:%dx%d Tiles:%dx%d Tilesets:%d Tile:%d,%d",
					App->map->data.width, App->map->data.height,
					App->map->data.tile_width, App->map->data.tile_height,
					App->map->data.tilesets.count(),
					map_coordinates.x, map_coordinates.y);

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

// Load Game State
bool j1Scene::load(pugi::xml_node& savegame)
{
	// WE'LL PUT THIS ON CHANGEMAPMUSIC AND IT'LL NOT BE HARDCODED :)
	// Loading SECOND map from FIRST map
	if (currentMap == 0 && savegame.child("map").attribute("actual").as_int() != 0)
	{
		currentMap = 1;
		App->map->CleanUp();
		App->particles->CleanUp();
		App->audio->UnloadMusic("audio/music/music_level_2.ogg");
		App->map->Load("Level_2.tmx");
		App->particles->Start();
		App->audio->PlayMusic("audio/music/music_level_2.ogg");
	}

	// Loading FIRST map from SECOND map
	if (currentMap == 1 && savegame.child("map").attribute("actual").as_int() != 1)
	{
		currentMap = 0;
		App->map->CleanUp();
		App->particles->CleanUp();
		App->audio->UnloadMusic("audio/music/music_level_1.ogg");
		App->map->Load("Level_1.tmx");
		App->particles->Start();
		App->audio->PlayMusic("audio/music/music_level_1.ogg");
	}

	// Loading FIRST map from FIRST map
	if (currentMap == 0 && savegame.child("map").attribute("actual").as_int() == 0)
	{
		App->map->CleanUp();
		App->colliders->CleanUp();
		App->map->Load("Level_1.tmx");
	}

	// Loading SECOND map from SECOND map
	if (currentMap == 1 && savegame.child("map").attribute("actual").as_int() == 1)
	{
		App->map->CleanUp();
		App->colliders->CleanUp();
		App->map->Load("Level_2.tmx");
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


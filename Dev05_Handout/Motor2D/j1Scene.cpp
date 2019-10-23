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
	App->map->Load("hello3.tmx");
	App->audio->PlayMusic("audio/music/music_level_1.ogg");

	return true;
}

// Called each loop iteration
bool j1Scene::PreUpdate()
{
	return true;
}

// Called each loop iteration
bool j1Scene::Update(float dt)
{
	if(App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
		App->LoadGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_F6) == KEY_DOWN)
		App->SaveGame("save_game.xml");

	if(App->input->GetKey(SDL_SCANCODE_UP) == KEY_REPEAT)
		App->render->camera.y += 2;

	if(App->input->GetKey(SDL_SCANCODE_DOWN) == KEY_REPEAT)
		App->render->camera.y -= 2;

	if(App->input->GetKey(SDL_SCANCODE_LEFT) == KEY_REPEAT)
		App->render->camera.x += 2;

	if(App->input->GetKey(SDL_SCANCODE_RIGHT) == KEY_REPEAT)
		App->render->camera.x -= 2;

	// Change map
	if (App->input->GetKey(SDL_SCANCODE_F1) == KEY_DOWN)
	{
		LevelName(0);
		currentMap = 0;
	}

	if (App->input->GetKey(SDL_SCANCODE_F2) == KEY_DOWN)
	{
		LevelName(1);
		currentMap = 1;
	}

	// Start from the beginning of the current level
	if (App->input->GetKey(SDL_SCANCODE_F3) == KEY_DOWN || App->player->dead==true)
	{
		if (currentMap == 0)
		{
			LevelName(0);
		}
		if (currentMap == 1)
		{
			LevelName(1);
		}

		App->player->dead = false;
	}

	if (App->player->map_next == true)
	{
		if (currentMap == 0)
		{
			LevelName(1);
			currentMap = 1;
		}
		else if (currentMap == 1)
		{
			LevelName(0);
			currentMap = 0;
		}
		App->player->map_next = false;
	}

	App->map->Draw();

	// Show player and map colliders
	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
	{
		if (App->player->showcolliders == false)
		{
			App->player->showcolliders = true;
		}
		else if (App->player->showcolliders == true)
		{
			App->player->showcolliders = false;
		}
	}

	// Map limits for God mode
	if (App->player->godMode == true)
	{
		if (App->player->position.x < 0)
		{
			App->player->position.x = 0;
		}
		if (App->player->position.y < 0)
		{
			App->player->position.y = 0;
		}
		else if (App->player->position.y > 713)
		{
			App->player->position.y = 713;
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
bool j1Scene::LevelName(int time)
{
	App->map->ChangeMapMusic(map_names[time], music_names[time]);

	return true;
}


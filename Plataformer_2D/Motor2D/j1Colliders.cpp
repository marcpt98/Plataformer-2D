#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Colliders.h"
#include "j1Player.h"
#include "p2Log.h"
#include "j1Scene.h"
#include "j1EntityManager.h"

j1Colliders::j1Colliders()
{
	name.create("colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	// No colliders
	matrix[NO_COLLIDER][NO_COLLIDER] = false;
	matrix[NO_COLLIDER][COLLIDER_FLOOR] = false;
	matrix[NO_COLLIDER][COLLIDER_PLAYER] = false;
	matrix[NO_COLLIDER][COLLIDER_DEATH] = false;
	matrix[NO_COLLIDER][COLLIDER_PLATAFORM] = false;
	matrix[NO_COLLIDER][COLLIDER_WALL] = false;
	matrix[NO_COLLIDER][COLLIDER_NEXTMAP] = false;
	matrix[NO_COLLIDER][COLLIDER_PLAYER_SHOT] = false;
	matrix[NO_COLLIDER][COLLIDER_CORNER] = false;
	matrix[NO_COLLIDER][COLLIDER_ENEMY] = false;
	matrix[NO_COLLIDER][COLLIDER_LOW_CORNER] = false;
	matrix[NO_COLLIDER][COLLIDER_CHECKPOINT] = false;
	matrix[NO_COLLIDER][COLLIDER_COIN] = false;

	// Collider floor
	matrix[COLLIDER_FLOOR][COLLIDER_FLOOR] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_FLOOR][COLLIDER_DEATH] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_PLATAFORM] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_WALL] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_NEXTMAP] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_FLOOR][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_FLOOR][COLLIDER_CORNER] = false;
	matrix[COLLIDER_FLOOR][NO_COLLIDER] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_LOW_CORNER] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_CHECKPOINT] = false;
	matrix[COLLIDER_FLOOR][COLLIDER_COIN] = false;

	// Collider player
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_FLOOR] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_DEATH] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLATAFORM] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_NEXTMAP] = true;
	matrix[COLLIDER_FLOOR][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_CORNER] = true;
	matrix[COLLIDER_PLAYER][NO_COLLIDER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_LOW_CORNER] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_CHECKPOINT] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_COIN] = true;

	// Collider player shot
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_FLOOR] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_DEATH] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLATAFORM] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_NEXTMAP] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_CORNER] = false;
	matrix[COLLIDER_PLAYER_SHOT][NO_COLLIDER] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_LOW_CORNER] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_CHECKPOINT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_COIN] = false;

	// Collider enemy
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_FLOOR] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_DEATH] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLATAFORM] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_WALL] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_CORNER] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_NEXTMAP] = false;
	matrix[COLLIDER_ENEMY][NO_COLLIDER] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_LOW_CORNER] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_CHECKPOINT] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_COIN] = false;

	// Collider death
	matrix[COLLIDER_DEATH][COLLIDER_DEATH] = false;
	matrix[COLLIDER_DEATH][COLLIDER_FLOOR] = false;
	matrix[COLLIDER_DEATH][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_DEATH][COLLIDER_PLATAFORM] = false;
	matrix[COLLIDER_DEATH][COLLIDER_WALL] = false;
	matrix[COLLIDER_DEATH][COLLIDER_NEXTMAP] = false;
	matrix[COLLIDER_DEATH][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_DEATH][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_DEATH][COLLIDER_CORNER] = false;
	matrix[COLLIDER_DEATH][NO_COLLIDER] = false;
	matrix[COLLIDER_DEATH][COLLIDER_LOW_CORNER] = false;
	matrix[COLLIDER_DEATH][COLLIDER_CHECKPOINT] = false;
	matrix[COLLIDER_DEATH][COLLIDER_COIN] = false;

	// Collider wall
	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_FLOOR] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLATAFORM] = false;
	matrix[COLLIDER_WALL][COLLIDER_DEATH] = false;
	matrix[COLLIDER_WALL][COLLIDER_NEXTMAP] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_WALL][COLLIDER_CORNER] = false;
	matrix[COLLIDER_WALL][NO_COLLIDER] = false;
	matrix[COLLIDER_WALL][COLLIDER_LOW_CORNER] = false;
	matrix[COLLIDER_WALL][COLLIDER_CHECKPOINT] = false;
	matrix[COLLIDER_WALL][COLLIDER_COIN] = false;

	// Collider next map
	matrix[COLLIDER_NEXTMAP][COLLIDER_NEXTMAP] = false;
	matrix[COLLIDER_NEXTMAP][COLLIDER_DEATH] = false;
	matrix[COLLIDER_NEXTMAP][COLLIDER_FLOOR] = false;
	matrix[COLLIDER_NEXTMAP][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_NEXTMAP][COLLIDER_PLATAFORM] = false;
	matrix[COLLIDER_NEXTMAP][COLLIDER_WALL] = false;
	matrix[COLLIDER_NEXTMAP][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_NEXTMAP][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_NEXTMAP][COLLIDER_CORNER] = false;
	matrix[COLLIDER_NEXTMAP][NO_COLLIDER] = false;
	matrix[COLLIDER_NEXTMAP][COLLIDER_LOW_CORNER] = false;
	matrix[COLLIDER_NEXTMAP][COLLIDER_CHECKPOINT] = false;
	matrix[COLLIDER_NEXTMAP][COLLIDER_COIN] = false;

	// Collider CORNER
	matrix[COLLIDER_CORNER][COLLIDER_CORNER] = false;
	matrix[COLLIDER_CORNER][COLLIDER_DEATH] = false;
	matrix[COLLIDER_CORNER][COLLIDER_FLOOR] = false;
	matrix[COLLIDER_CORNER][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_CORNER][COLLIDER_PLATAFORM] = false;
	matrix[COLLIDER_CORNER][COLLIDER_WALL] = false;
	matrix[COLLIDER_CORNER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_CORNER][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_CORNER][COLLIDER_NEXTMAP] = false;
	matrix[COLLIDER_CORNER][COLLIDER_LOW_CORNER] = false;
	matrix[COLLIDER_CORNER][NO_COLLIDER] = false;
	matrix[COLLIDER_CORNER][COLLIDER_CHECKPOINT] = false;
	matrix[COLLIDER_CORNER][COLLIDER_COIN] = false;

	// Collider LOW_corner
	matrix[COLLIDER_LOW_CORNER][COLLIDER_LOW_CORNER] = false;
	matrix[COLLIDER_LOW_CORNER][COLLIDER_DEATH] = false;
	matrix[COLLIDER_LOW_CORNER][COLLIDER_FLOOR] = false;
	matrix[COLLIDER_LOW_CORNER][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_LOW_CORNER][COLLIDER_PLATAFORM] = false;
	matrix[COLLIDER_LOW_CORNER][COLLIDER_WALL] = false;
	matrix[COLLIDER_LOW_CORNER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_LOW_CORNER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_LOW_CORNER][COLLIDER_NEXTMAP] = false;
	matrix[COLLIDER_LOW_CORNER][NO_COLLIDER] = false;
	matrix[COLLIDER_LOW_CORNER][COLLIDER_CHECKPOINT] = false;
	matrix[COLLIDER_LOW_CORNER][COLLIDER_COIN] = false;

	//Collider for checkpoints
	matrix[COLLIDER_CHECKPOINT][COLLIDER_CHECKPOINT] = false;
	matrix[COLLIDER_CHECKPOINT][COLLIDER_DEATH] = false;
	matrix[COLLIDER_CHECKPOINT][COLLIDER_FLOOR] = false;
	matrix[COLLIDER_CHECKPOINT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_CHECKPOINT][COLLIDER_PLATAFORM] = false;
	matrix[COLLIDER_CHECKPOINT][COLLIDER_WALL] = false;
	matrix[COLLIDER_CHECKPOINT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_CHECKPOINT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_CHECKPOINT][COLLIDER_NEXTMAP] = false;
	matrix[COLLIDER_CHECKPOINT][NO_COLLIDER] = false;
	matrix[COLLIDER_CHECKPOINT][COLLIDER_LOW_CORNER] = false;
	matrix[COLLIDER_CHECKPOINT][COLLIDER_COIN] = false;

	//Collider for Coins
	matrix[COLLIDER_COIN][COLLIDER_COIN] = false;
	matrix[COLLIDER_COIN][COLLIDER_CHECKPOINT] = false;
	matrix[COLLIDER_COIN][COLLIDER_DEATH] = false;
	matrix[COLLIDER_COIN][COLLIDER_FLOOR] = false;
	matrix[COLLIDER_COIN][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_COIN][COLLIDER_PLATAFORM] = false;
	matrix[COLLIDER_COIN][COLLIDER_WALL] = false;
	matrix[COLLIDER_COIN][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_COIN][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_COIN][COLLIDER_NEXTMAP] = false;
	matrix[COLLIDER_COIN][NO_COLLIDER] = false;
	matrix[COLLIDER_COIN][COLLIDER_LOW_CORNER] = false;
}

// Destructor
j1Colliders::~j1Colliders()
{}

bool j1Colliders::PreUpdate()
{
	BROFILER_CATEGORY("PreupdateColliders", Profiler::Color::DarkViolet)

	bool ret = true;
	// Remove all colliders scheduled for deletion
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr && colliders[i]->to_delete == true)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	// Calculate collisions
	Collider* c1;
	Collider* c2;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		// skip empty colliders
		if (colliders[i] == nullptr)
			continue;

		c1 = colliders[i];
		if (c1->Enabled == false)
		{
			continue;
		}

		// avoid checking collisions already checked
		for (uint k = i + 1; k < MAX_COLLIDERS; ++k)
		{
			// skip empty colliders
			if (colliders[k] == nullptr)
				continue;

			c2 = colliders[k];
			if (c2->Enabled == false)
			{
				continue;
			}
			if (c1->CheckCollision(c2->rect) == true)
			{
				if (matrix[c1->type][c2->type] && c1->callback)
					c1->callback->OnCollision(c1, c2);                      

				if (matrix[c2->type][c1->type] && c2->callback)
					c2->callback->OnCollision(c2, c1);
			}
		}
	}
	
	return ret;
}

// Called before render is available
bool j1Colliders::Update(float dt)
{
	BROFILER_CATEGORY("UpdateColliders", Profiler::Color::DarkSlateBlue)

	bool ret = true;
	DebugDraw();

	return ret;
}

void j1Colliders::DebugDraw()
{
	
	if (App->input->GetKey(SDL_SCANCODE_F9) == KEY_DOWN)
		debug = !debug;

	if (debug == false)
		return;
	
	Uint8 alpha = 80;
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		
		if (colliders[i] == nullptr)
			continue;

		switch (colliders[i]->type)
		{

		case COLLIDER_NONE: // purple
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 255, alpha);
			break;

		case NO_COLLIDER: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;

		case COLLIDER_FLOOR: // blue
			App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			break;

		case COLLIDER_PLATAFORM: //purple
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;

		case COLLIDER_WALL: //turquesa
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;

		case COLLIDER_PLAYER: // green
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			break;

		case COLLIDER_PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;

		case COLLIDER_DEATH: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;

		case COLLIDER_NEXTMAP: // violet
			App->render->DrawQuad(colliders[i]->rect, 130, 5, 255, alpha);
			break;

		case COLLIDER_ENEMY: // dark slategray
			App->render->DrawQuad(colliders[i]->rect, 0,0,0, alpha);
			break;

		case COLLIDER_CORNER: // LIMA
			App->render->DrawQuad(colliders[i]->rect, 81, 255, 0, alpha);
			break;

		case COLLIDER_LOW_CORNER: // Pink
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 243, alpha);
			break;

		case COLLIDER_CHECKPOINT: // Pink
			App->render->DrawQuad(colliders[i]->rect, 255, 112, 0, alpha);
			break;

		case COLLIDER_COIN: // Gold
			App->render->DrawQuad(colliders[i]->rect, 241, 176, 14, alpha);
			break;
		}

	}
}

// Called before quitting
bool j1Colliders::CleanUp()
{
	LOG("Freeing all colliders");

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] != nullptr)
		{
			delete colliders[i];
			colliders[i] = nullptr;
		}
	}

	return true;
}

Collider* j1Colliders::AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback)
{
	Collider* ret = nullptr;

	for (uint i = 0; i < MAX_COLLIDERS; ++i)
	{
		if (colliders[i] == nullptr)
		{
			ret = colliders[i] = new Collider(rect, type, callback);
			break;
		}
	}

	return ret;
}

// -----------------------------------------------------

bool Collider::CheckCollision(const SDL_Rect& r) const
{
	if (r.x + r.w < rect.x || r.x > rect.x + rect.w || r.y + r.h < rect.y || r.y > rect.y + rect.h) {
		return false;
	}
	else {
		return true;
	}
}
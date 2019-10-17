#include "j1App.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Colliders.h"
#include "j1Player.h"
#include "p2Log.h"
#include "j1Scene.h"

j1Colliders::j1Colliders()
{
	for (uint i = 0; i < MAX_COLLIDERS; ++i)
		colliders[i] = nullptr;

	matrix[COLLIDER_WALL][COLLIDER_WALL] = false;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_WALL][COLLIDER_DEATH] = false;
	/*matrix[COLLIDER_WALL][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_WALL][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_WALL][COLLIDER_ENEMY_SHOT] = true;*/

	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_WALL] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_DEATH] = true;
	/*matrix[COLLIDER_PLAYER][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER][COLLIDER_ENEMY_SHOT] = true;*/

	matrix[COLLIDER_DEATH][COLLIDER_DEATH] = false;
	matrix[COLLIDER_DEATH][COLLIDER_WALL] = true;
	matrix[COLLIDER_DEATH][COLLIDER_PLAYER] = true;

	/*matrix[COLLIDER_ENEMY][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_ENEMY][COLLIDER_ENEMY_SHOT] = false;*/
	/*
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_WALL] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY] = true;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_PLAYER_SHOT] = false;
	matrix[COLLIDER_PLAYER_SHOT][COLLIDER_ENEMY_SHOT] = true;

	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_WALL] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY] = false;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_PLAYER_SHOT] = true;
	matrix[COLLIDER_ENEMY_SHOT][COLLIDER_ENEMY_SHOT] = false;
	
	matrix[NO_COLLIDER][COLLIDER_WALL] = false;
	matrix[NO_COLLIDER][COLLIDER_PLAYER] = false;
	matrix[NO_COLLIDER][COLLIDER_ENEMY] = false;
	matrix[NO_COLLIDER][COLLIDER_PLAYER_SHOT] = false;
	matrix[NO_COLLIDER][COLLIDER_ENEMY_SHOT] = false;
	*/
}

// Destructor
j1Colliders::~j1Colliders()
{}

bool j1Colliders::PreUpdate()
{
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
					c1->callback->OnCollision(c1, c2);                       // needs to change

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
	bool ret = true;
	DebugDraw();

	return ret;
}

void j1Colliders::DebugDraw()
{
	
	if (App->input->GetKey(SDL_SCANCODE_F5) == KEY_DOWN)
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
	
		case COLLIDER_NONE: // white
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 255, alpha);
			break;

		case COLLIDER_WALL: // blue
			if (App->player->showcolliders == true) {
				App->render->DrawQuad(colliders[i]->rect, 0, 0, 255, alpha);
			}
			break;

		case COLLIDER_PLAYER: // green
			if (App->player->showcolliders == true) {
				App->render->DrawQuad(colliders[i]->rect, 0, 255, 0, alpha);
			}
			break;

		case COLLIDER_DEATH: // NOT green
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;
			/*
		case COLLIDER_ENEMY: // red
			App->render->DrawQuad(colliders[i]->rect, 255, 0, 0, alpha);
			break;

		case COLLIDER_PLAYER_SHOT: // yellow
			App->render->DrawQuad(colliders[i]->rect, 255, 255, 0, alpha);
			break;

		case COLLIDER_ENEMY_SHOT: // magenta
			App->render->DrawQuad(colliders[i]->rect, 0, 255, 255, alpha);
			break;*/

		}

	}
	//App->render->DrawQuad(camera_window, 100, 100, 153, 70);
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
	// TODO 0: Return true if there is an overlap
	// between argument "r" and property "rect"

	/*
	return (r.x + r.w < rect.x || r.x + r.w > rect.x + rect.w || r.y + r.h < rect.y || r.y > rect.y + rect.h);
	return false;
	}*/

	if (r.x + r.w < rect.x || r.x > rect.x + rect.w || r.y + r.h < rect.y || r.y > rect.y + rect.h) {
		return false;
	}
	else {
		return true;
	}

	//return (rect.x < r.x + r.w && rect.x + rect.w > r.x && rect.y < r.y + r.h &&n rect.h + rect.y > r.y); another option that actually works

}
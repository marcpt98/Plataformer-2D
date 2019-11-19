#ifndef __j1Colliders_H__
#define __j1Colliders_H__

#define MAX_COLLIDERS 1000

#include "j1Module.h"

enum COLLIDER_TYPE
{
	COLLIDER_NONE = -1,
	COLLIDER_FLOOR,
	COLLIDER_PLATAFORM,
	COLLIDER_WALL,
	COLLIDER_PLAYER,
	COLLIDER_CORNER,
	COLLIDER_LOW_CORNER,
	COLLIDER_ENEMY,
	COLLIDER_DEATH,
	COLLIDER_NEXTMAP,
	COLLIDER_PLAYER_SHOT,
	COLLIDER_ENEMY_SHOT,
	NO_COLLIDER,

	COLLIDER_MAX
};

struct Collider
{
	SDL_Rect rect;
	bool to_delete = false;
	COLLIDER_TYPE type;
	j1Module* callback = nullptr;

	Collider(SDL_Rect rectangle, COLLIDER_TYPE type, j1Module* callback = nullptr) :
		rect(rectangle),
		type(type),
		callback(callback)
	{}

	void SetPos(int x, int y)
	{
		rect.x = x;
		rect.y = y;
	}
	void SetSize(int w, int h)
	{
		rect.w = w;
		rect.h = h;
	}

	bool CheckCollision(const SDL_Rect& r) const;
	bool Enabled = true;
};

class j1Colliders : public j1Module
{
public:
	j1Colliders();
	~j1Colliders();

	bool PreUpdate();
	bool Update(float dt);
	bool CleanUp();

	Collider* AddCollider(SDL_Rect rect, COLLIDER_TYPE type, j1Module* callback = nullptr);
	void DebugDraw();

private:

	Collider* colliders[MAX_COLLIDERS];
	bool matrix[COLLIDER_MAX][COLLIDER_MAX];
	bool debug = true;
};

#endif // __j1Colliders_H__*/


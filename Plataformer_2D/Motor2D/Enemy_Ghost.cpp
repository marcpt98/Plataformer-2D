#include "j1App.h"
#include "Enemy_Ghost.h"
#include "j1Colliders.h"

Enemy_Ghost::Enemy_Ghost(int x, int y) : Enemy(x, y)
{
	// Ghost idle
	idle.PushBack({ 0, 182, 48, 84 }, 0.1, 0, 0);
	idle.PushBack({ 50, 182, 56, 82 }, 0.1, 0, 0);
	idle.PushBack({ 108, 182, 52, 84 }, 0.1, 0, 0);
	idle.PushBack({ 162, 182, 48, 84 }, 0.1, 0, 0);
	idle.PushBack({ 212, 182, 48, 84 }, 0.1, 0, 0);
	idle.PushBack({ 262, 182, 49, 88 }, 0.1, 0, 0);
	idle.PushBack({ 314, 182, 47, 86 }, 0.1, 0, 0);

	animation = &idle;

	collider = App->colliders->AddCollider({ 0, 0, 50, 50 }, COLLIDER_TYPE::COLLIDER_ENEMY, (j1Module*)App->enemy);
}

void Enemy_Ghost::Move()
{
	/*if (going_up)
	{
		if (wave > 1.0f)
			going_up = false;
		else
			wave += 0.05f;
	}
	else
	{
		if (wave < -1.0f)
			going_up = true;
		else
			wave -= 0.05f;
	}

	position.y = original_y + int(25.0f * sinf(wave));
	position.x -= 1;*/
}

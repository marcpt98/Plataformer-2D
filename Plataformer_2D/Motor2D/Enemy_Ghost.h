#ifndef __ENEMY_GHOST_H__
#define __ENEMY_GHOST_H__

#include "Enemy.h"

class Enemy_Ghost : public Enemy
{
private:
	Animation idle;

public:

	Enemy_Ghost(int x, int y);

	void Move();

};

#endif // __ENEMY_GHOST_H__

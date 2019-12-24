#ifndef __j1Player_H__
#define __j1Player_H__

#include "j1Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "p2DynArray.h"
#include "j1Entity.h"

#define VELOCITY 60

struct SDL_Texture;
struct Collider;

enum states
{
	ST_IDLE,
	ST_RUN,
	ST_JUMP,
	ST_SHOOT,
	ST_DEAD,
	ST_DEADMONS
};

class j1Player : public j1Entity
{
public:

	j1Player(int posx, int posy);
	
	// Destructor
	~j1Player();
	
	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate(float dt);

	// Called before quitting
	bool CleanUp();

	// Collisions
	void OnCollision(Collider* c1, Collider* c2);

	// Load all config info
	bool LoadConfigInfo();

public:
	iPoint iPosition;
	
	// Animations
	Animation* current_animation = nullptr;
	Animation idle;
	Animation run;
	Animation jump;
	Animation special;
	Animation death;
	Animation grab;
	Animation shoot;
	Animation shoot_run;
	Animation pause;
	
	// Fx
	p2SString jumpFx;
	p2SString deadFx;
	p2SString throwrockFx;
	p2SString ballhitFx;
	p2SString ghostdeadFx;
	p2SString ghostfollowFx;
	//p2SString ghostkillFx;
	p2SString slimedeadFx;
	p2SString checkPoint;
	p2SString coin;
	//p2SString slimefollowFx;
	//p2SString slimekillFx;


	// Gravity
	float gravity;
	float igravity;
	bool fallingravity = false;
	float energyfalling;
	float timeAccelerationDelay;
	float acceleration;
	float maxAcceleration;
	
	// Speed
	float speed;
	float speedgm;

	// Jump force
	bool canJump1 = false;
	float jumpF;
	float energyJump;
	float incrementJ;
	float iJumpF;

	// Jump when grabbed
	float jumpG;
	float energyGrab;
	bool goright = false;
	bool goleft = false;
	bool grabFinish = false; 
	int timegrab;
	int timegrab2;
	bool controls = false;
	bool nojumpingleft = false;
	bool nojumpingright = false;
	float gGravity;
	
	// Stats machine
	void CheckInputState(float dt);
	void CheckAnimation(float dt);
	states	actualState;

	// God mode
	bool godMode = false;

	//Player interaction with plataform
	bool canjumpPlat = false;
	bool goingdown = false;

	// Player dead
	bool dead_animation = false;
	bool count_dead = false;
	int dead_animation_finish;
	int deadDelay;
	int deaddead = 0;

	// Player dead by monster
	bool dead_monster_animation = false;
	bool count_monster_dead = false;
	int dead_monster_animation_finish;
	bool pressspace = false;

	// Player grabing
	bool grabing = false;
	int timeGrabDelay;
	int slipping;

	// Player is grab_falling
	bool grab_falling = false;

	// Platforms
	int playerHeight;
	int playerHeight2;

	// Shoot
	int shoottime;
	bool shootfinish = false;
	bool isshooting = false;

	// Shoot run
	int shootruntime;
	bool shootrunfinish = false;
	bool isrunshooting = false;

	// Framerate new variables
	bool ground = false;
	
	//Lives System
	int current_lives;

	int number;
};

#endif // __j1Player_H__
#ifndef __j1Player_H__
#define __j1Player_H__

#include "j1Module.h"
#include "Animation.h"
#include "p2Point.h"
#include "p2DynArray.h"


struct SDL_Texture;
struct Collider;

enum states
{
	ST_IDLE,
	ST_RUN,
	ST_JUMP,
	ST_SHOOT,
	ST_DEAD
};

class j1Player : public j1Module
{
public:

	j1Player();
	
	// Destructor
	~j1Player();

	// Called before render is available
	bool Awake(pugi::xml_node& config);
	
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

	// Save and Load
	bool load(pugi::xml_node&);
	bool save(pugi::xml_node&);

public:
	SDL_Texture* graphics = nullptr;
	iPoint position;
	iPoint lasPosition;
	iPoint iPosition;
	
	// Animations
	p2SString spritesheet;
	Animation* current_animation = nullptr;
	Animation idle;
	Animation run;
	Animation jump;
	Animation special;
	Animation death;
	Animation grab;
	Animation shoot;
	Animation shoot_run;
	
	// Fx
	p2SString jumpFx;
	p2SString deadFx;
	p2SString throwrockFx;
	p2SString ballhitFx;

	// Colliders
	Collider* collider = nullptr;
	Collider* collider2 = nullptr;
	bool showcolliders = false;

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
	
	// Player blit
	bool	blit = false;	
	int		fixBlit;

	// God mode
	bool godMode = false;

	//Player interaction with plataform
	bool canjumpPlat = false;
	bool goingdown = false;

	// Player dead
	bool dead = false;
	int dead_timer;
	bool dead_animation = false;
	bool count_dead = false;
	int dead_animation_finish = 0;
	int deadDelay;

	// Player grabing
	bool grabing = false;
	int timeGrabDelay;
	int slipping;

	// Player is grab_falling
	bool grab_falling = false;

	// Next map
	bool map_next = false;

	// Platforms
	int playerHeight;
	int playerHeight2;

	// Shoot
	int shoottime = 0;
	bool shootfinish = false;
	bool isshooting = false;

	// Shoot run
	int shootruntime = 0;
	bool shootrunfinish = false;
	bool isrunshooting = false;

	// Interaction with enemy

};

#endif // __j1Player_H__
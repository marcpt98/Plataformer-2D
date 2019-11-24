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

	bool LoadConfigInfo(pugi::xml_node& config);

public:
	iPoint iPosition;

	int player_width = 40;
	int player_high = 53;
	
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
	
	// Fx
	p2SString jumpFx= "audio/fx/fx_jump.wav";
	p2SString deadFx= "audio/fx/fx_dead.wav";
	p2SString throwrockFx= "audio/fx/fx_trhowrock.wav";
	p2SString ballhitFx= "audio/fx/fx_ballhit.wav";
	p2SString ghostdeadFx= "audio/fx/fx_phantomdead.wav";

	// Gravity
	float gravity = 5;
	float igravity = 5;
	bool fallingravity = false;
	float energyfalling = 0;
	float timeAccelerationDelay = 500;
	float acceleration = 0.2;
	float maxAcceleration = 50;
	
	// Speed
	float speed = 1;
	float speedgm = 6;

	// Jump force
	bool canJump1 = false;
	float jumpF = -15;
	float energyJump;
	float incrementJ = 0.5;
	float iJumpF = -15;

	// Jump when grabbed
	float jumpG = -5;
	float energyGrab;
	bool goright = false;
	bool goleft = false;
	bool grabFinish = false; 
	int timegrab;
	int timegrab2;
	bool controls = false;
	bool nojumpingleft = false;
	bool nojumpingright = false;
	float gGravity = 4;
	
	// Stats machine
	void CheckInputState(float dt);
	void CheckAnimation(float dt);
	states	actualState;
	
	// Player blit
	bool	blit = false;	
	int		fixBlit = 40;

	// God mode
	bool godMode = false;

	//Player interaction with plataform
	bool canjumpPlat = false;
	bool goingdown = false;

	// Player dead
	bool dead_animation = false;
	bool count_dead = false;
	int dead_animation_finish = 0;
	int deadDelay = 800;

	// Player dead by monster
	bool dead_monster_animation = false;
	bool count_monster_dead = false;
	int dead_monster_animation_finish = 0;
	bool pressspace = false;

	// Player grabing
	bool grabing = false;
	int timeGrabDelay = 200;
	int slipping = 1;

	// Player is grab_falling
	bool grab_falling = false;

	// Platforms
	int playerHeight = 58;
	int playerHeight2 = 53;

	// Shoot
	int shoottime = 0;
	bool shootfinish = false;
	bool isshooting = false;

	// Shoot run
	int shootruntime = 0;
	bool shootrunfinish = false;
	bool isrunshooting = false;

	// Framerate new variables
	bool ground = false;
	
	int number = 0;
};

#endif // __j1Player_H__
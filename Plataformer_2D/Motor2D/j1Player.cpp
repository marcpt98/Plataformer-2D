#include "j1Window.h"
#include "j1Input.h"
#include "j1Render.h"
#include "j1Textures.h"
#include "j1Audio.h"
#include "j1Scene.h"
#include "j1Map.h"
#include "j1App.h"
#include "j1FadeToBlack.h"
#include "j1Player.h"
#include "j1Particles.h"
#include "Animation.h"
#include "j1Enemy.h"
#include<stdio.h>
#include "j1Colliders.h"
#include "p2Log.h"

j1Player::j1Player() 
{ 
	name.create("player");

	// Initializing variables
	actualState = ST_IDLE;
	dead_timer = 0;
	energyGrab = 0;
	energyJump = 0;
	energyfalling = 0;
	fixBlit = 0;
	gravity = 0;
	igravity = 0;
	incrementJ = 0;
	jumpF = 0;
	jumpG = 0;
	speed = 0;
	timegrab = 0;
	timegrab2 = 0;
	position.x = 0;
	position.y = 0;
	iPosition.x = 0;
	iPosition.y = 0;
	lasPosition.x = 0;
	lasPosition.y = 0;
	timeGrabDelay = 0;
	iJumpF = 0;
	gGravity = 0;
	slipping = 0;
	timeAccelerationDelay = 0;
	maxAcceleration = 0;
	acceleration = 0;
	playerHeight = 0;
	playerHeight2 = 0;
	deadDelay = 0;

	// Idle animation
	idle.PushBack({ 0,0,42,52 }, 0.2, 0, 0);
	idle.PushBack({ 44,0,40,54 }, 0.2, 2, -2);
	idle.PushBack({ 86,0,42,54 }, 0.2, 0, -2);
	idle.PushBack({ 130,0,44,52 }, 0.2, 0, 0);
	
	// Run animation
	run.PushBack({ 0,110,40,50 }, 0.2, 0, 4);
	run.PushBack({ 42,110,42,50 }, 0.2, 0, 4);
	run.PushBack({ 86,110,42,48 }, 0.2, 0, 4);
	run.PushBack({ 130,110,40,50 }, 0.2, 0, 4);
	run.PushBack({ 172,110,42,50 }, 0.2, 0, 4);
	run.PushBack({ 216,110,42,48 }, 0.2, 0, 4);

	// Jump animation
	jump.PushBack({ 0,161,42,52 }, 0.2, 0, 0);
	jump.PushBack({ 44,161,44,48 }, 0.2, 0, 0);
	jump.PushBack({ 90,161,46,48 }, 0.2, 0, 0);
	jump.PushBack({ 138,161,40,60 }, 0.2, 0, 0);
	jump.PushBack({ 180,161,42,54 }, 0.2, 0, 0);
	jump.PushBack({ 224,161,44,54 }, 0.2, 0, 0);
	jump.PushBack({ 270,161,46,48 }, 0.2, 0, 0);
	jump.PushBack({ 318,161,40,52 }, 0.2, 0, 0);
	jump.PushBack({ 90,161,46,48 }, 0.2, 0, 0);
	jump.loop = false;

	// Death animation
	death.PushBack({ 0,444,44,56 }, 0.15, 0, 0);
	death.PushBack({ 46,444,50,58 }, 0.15, 0, 0);
	death.PushBack({ 98,444,52,38 }, 0.15, 0, 20);
	death.PushBack({ 152,444,58,22 }, 0.15, 0, 30);
	death.PushBack({ 212,444,70,24 }, 0.15, 0, 30);
	death.PushBack({ 284,444,50,26 }, 0.15, 0, 30);
	death.PushBack({ 336,444,30,30 }, 0.15, 0, 25);
	death.PushBack({ 374,444,18,16 }, 0.15, 0, 25);

	// Grab animation
	grab.PushBack({ 0,389,45,50 }, 0.15, 0, 0);

	// Shoot animation
	shoot.PushBack({ 0,279,42,52 }, 0.2, 0, 0);
	shoot.PushBack({ 44,279,42,48 }, 0.2, 0, 4);
	shoot.PushBack({ 88,279,54,54 }, 0.2, 3, -1);
	shoot.PushBack({ 144,279,46,54 }, 0.2, 1, -1);
	shoot.loop = false;

	// Shoot running animation
	shoot_run.PushBack({ 0,334,42,50 }, 0.2, 0, 0);
	shoot_run.PushBack({ 44,334,54,54 }, 0.2, 0, -3);
	shoot_run.PushBack({ 100,334,46,54 }, 0.2, 0, -3);
	shoot_run.PushBack({ 148,334,42,50 }, 0.2, 0, -2);
	shoot_run.PushBack({ 192,334,42,52 }, 0.2, 0, 0);
	shoot_run.PushBack({ 236,334,40,54 }, 0.2, 0, -4);
	shoot_run.loop = false;
}

j1Player::~j1Player()
{}

bool j1Player::Awake(pugi::xml_node& config)
{
	LOG("Loading Player");

	bool ret = true;

	// Player position
	position.x = config.child("position").attribute("x").as_int();
	position.y = config.child("position").attribute("y").as_int();

	// Player initial position
	iPosition.x = config.child("iPosition").attribute("x").as_int();
	iPosition.y = config.child("iPosition").attribute("y").as_int();

	// Player spritesheet
	spritesheet = config.child("spritesheet").attribute("player").as_string("");

	// Play Fx
	jumpFx = config.child("fx_name").attribute("jump").as_string("");
	deadFx = config.child("fx_name2").attribute("dead").as_string("");
	throwrockFx = config.child("fx_name3").attribute("throwrock").as_string("");
	ballhitFx = config.child("fx_name4").attribute("ballhit").as_string("");
	
	// Player speed
	speed = config.child("speed").attribute("s").as_float();
	speedgm = config.child("speedgm").attribute("sgm").as_float();

	// Gravity
	gravity = config.child("gravity").attribute("g").as_float();

	// Gravity when grabbed
	gGravity = config.child("gGravity").attribute("g").as_float();

	// Initial Gravity
	igravity = config.child("igravity").attribute("g").as_float();

	// Acceleration
	acceleration = config.child("acceleration").attribute("a").as_float();

	// Gravity max acceleration
	maxAcceleration = config.child("maxAcceleration").attribute("max").as_float();

	// Initial jump force
	iJumpF= config.child("iJumpF").attribute("j").as_float();

	// Jump force
	jumpF = config.child("jumpF").attribute("j").as_float();
	
	// Jump force when grabbed
	jumpG = config.child("jumpG").attribute("g").as_float();

	// Slipping velocity
	slipping = config.child("slipping").attribute("s").as_int();

	// Grab time delay
	timeGrabDelay= config.child("timeGrabDelay").attribute("time").as_int();

	// Delay to activate gravity accelerated
	timeAccelerationDelay = config.child("timeAccelerationDelay").attribute("time").as_float();

	// Increment of jump force
	incrementJ = config.child("incrementJ").attribute("i").as_float();

	// Jumping on platform
	playerHeight = config.child("playerHeight").attribute("h").as_int();
	playerHeight2 = config.child("playerHeight2").attribute("h").as_int();

	// Dead delay
	deadDelay = config.child("deadDelay").attribute("d").as_int();
	
	// Fix blit
	fixBlit = config.child("fixBlit").attribute("fix").as_int();

	return ret;
}

bool j1Player::Start() 
{
	// Load Fx 
	App->audio->LoadFx(jumpFx.GetString());
	App->audio->LoadFx(deadFx.GetString());
	App->audio->LoadFx(throwrockFx.GetString());
	App->audio->LoadFx(ballhitFx.GetString());
	// Load spritesheet
	graphics = App->tex->Load(spritesheet.GetString());

	// Add player collider
	collider = App->colliders->AddCollider({ position.x,position.y, 40, 53 }, COLLIDER_PLAYER, this); //a collider to start COLLIDER PLAYER

	
	// Set initial position
	position.x = iPosition.x;
	position.y = iPosition.y;

	return true;
}

bool j1Player::CleanUp() 
{
	App->tex->UnLoad(graphics);
	App->audio->UnloadFx(jumpFx.GetString());
	App->audio->UnloadFx(deadFx.GetString());
	App->audio->UnloadFx(throwrockFx.GetString());
	App->audio->UnloadFx(ballhitFx.GetString());
	return true;
}

bool j1Player::Update(float dt) 
{
	// Gravity
	if (godMode == true)
	{
		position.y = position.y;
	}
	else
	{
		if (App->want_load == false)
		{
			lasPosition.x = position.x;
			lasPosition.y = position.y;
			position.y = position.y + gravity; 
		}
	}

	CheckInputState(dt);
	CheckAnimation(dt);

	// Player colliders
	collider->SetPos(position.x, position.y);

	// Print player
	if (blit == false)
	{
		App->render->Blit(graphics, position.x + current_animation->pivotx[current_animation->returnCurrentFrame()], position.y + current_animation->pivoty[current_animation->returnCurrentFrame()], &(current_animation->GetCurrentFrame()), 1.0f);
		App->particles->Projectile.speed.x = 6;
	}
	else
	{
		App->render->BlitWithScale(graphics, position.x + fixBlit + (-current_animation->pivotx[current_animation->returnCurrentFrame()]), position.y + current_animation->pivoty[current_animation->returnCurrentFrame()], &(current_animation->GetCurrentFrame()), -1, 1.0f, 1, TOP_RIGHT);
		App->particles->Projectile_flip.speed.x = -6;
	}

	if (App->particles->explosion_time_init == true)
	{
		App->particles->explosion_time = SDL_GetTicks();
		App->particles->explosion_time_init = false;
	}
	if (SDL_GetTicks() > App->particles->explosion_time + 1200)
	{
		App->particles->explosion_finish = false;
		App->particles->explosion_time_init = false;
	}

	return true;
}

bool j1Player::PostUpdate(float dt)
{
	return true;
}

void j1Player::CheckInputState(float dt)
{
	
	// God mode
	if (App->input->GetKey(SDL_SCANCODE_F10) == KEY_DOWN)
	{
		if (godMode == false)
		{
			collider->to_delete = true;
			collider = App->colliders->AddCollider({ position.x,position.y, 35, 53 }, NO_COLLIDER, this);
			godMode = true;
		}
		else if (godMode == true)
		{
			collider->to_delete = true;
			collider = App->colliders->AddCollider({ position.x,position.y, 35, 53 }, COLLIDER_PLAYER, this);
			godMode = false;
		}
	}

	if (godMode == true)
	{
		actualState = ST_IDLE;

		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			position.y = position.y - speedgm;
		}
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			position.y = position.y + speedgm;
		}
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			position.x = position.x - speedgm;
		}
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			position.x = position.x + speedgm;
		}
	}

	// Without god mode
	else
	{
		// Check grab time
		if (grabFinish == true)
		{
			timegrab = SDL_GetTicks();
			grabFinish = false;
		}
		if (SDL_GetTicks() > timegrab + timeGrabDelay)
		{
			grab_falling = false;
			gravity = igravity;
			grabing = false;
			goright = false;
			goleft = false;
			controls = false;
		}

		// Player controllers
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && dead_animation == false)
		{

			actualState = ST_JUMP;
			if (canJump1 == true)
			{
				energyJump = jumpF;
				energyGrab = jumpG;
			}

			// Reset animations
			idle.Reset();
			run.Reset();
			death.Reset();
			grab.Reset();
		}

		else if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN && dead_animation == false && controls == false && App->input->GetKey(SDL_SCANCODE_D) == NULL && App->input->GetKey(SDL_SCANCODE_A) == NULL && App->particles->explosion_finish == false)
		{
			App->particles->explosion_time_init = true;
			App->particles->explosion_finish = true;
			App->audio->PlayFx(3, 0);
			App->particles->explosion = false;
			App->particles->hitobject = false;

			if (blit == false)
			{
				App->particles->AddParticle(App->particles->Projectile, lasPosition.x + 10, lasPosition.y + 30, COLLIDER_PLAYER_SHOT);
				App->particles->explosion_right = true;
			}
			else
			{
				App->particles->AddParticle(App->particles->Projectile_flip, lasPosition.x + 10, lasPosition.y + 30, COLLIDER_PLAYER_SHOT);
				App->particles->explosion_right = false;
			}

			isshooting = true;

			if (shootfinish == false)
			{
				shoottime = SDL_GetTicks();
				shootfinish = true;
			}
		}

		else if (App->input->GetKey(SDL_SCANCODE_F) == KEY_DOWN && dead_animation == false && controls == false && App->particles->explosion_finish == false)
		{
			App->particles->explosion_time_init = true;
			App->particles->explosion_finish = true;
			App->audio->PlayFx(3, 0);
			App->particles->explosion = false;
			App->particles->hitobject = false;

			if (blit == false)
			{
				App->particles->AddParticle(App->particles->Projectile, lasPosition.x + 10, lasPosition.y + 30, COLLIDER_PLAYER_SHOT);
				App->particles->explosion_right = true;
			}
			else
			{
				App->particles->AddParticle(App->particles->Projectile_flip, lasPosition.x + 10, lasPosition.y + 30, COLLIDER_PLAYER_SHOT);
				App->particles->explosion_right = false;
			}

			isrunshooting = true;

			if (goleft == true)
			{
				position.x = position.x - speed;
				goright = false;
			}
			if (goright == true)
			{
				position.x = position.x + speed;
				goleft = false;
			}

			if (shootrunfinish == false)
			{
				shootruntime = SDL_GetTicks();
				shootrunfinish = true;
			}
		}

		else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && canJump1 == true && dead_animation == false && controls == false && isshooting == false)
		{
			actualState = ST_RUN;
			position.x = position.x - speed;
			blit = true;

			goright = false;
			goleft = true;
			
			// Reset animations
			idle.Reset();
			jump.Reset();
			death.Reset();
			grab.Reset();	
		}

		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && canJump1 == true && dead_animation == false && controls == false && isshooting == false)
		{
			actualState = ST_RUN;
			position.x = position.x + speed;
			blit = false;

			goleft = false;
			goright = true;
			
			// Reset animations
			idle.Reset();
			jump.Reset();
			death.Reset();
			grab.Reset();
		}

		else if (canJump1 == true && App->input->GetKey(SDL_SCANCODE_D) == NULL && App->input->GetKey(SDL_SCANCODE_A) == NULL && App->input->GetKey(SDL_SCANCODE_SPACE) == NULL && dead_animation == false && grabing == false && isshooting == false)
		{
			actualState = ST_IDLE;

			// Reset animations
			run.Reset();
			jump.Reset();
			death.Reset();
			grab.Reset();	
		}

		else if (dead_animation == true)
		{
			actualState = ST_DEAD;
		}
	}
}

void j1Player::CheckAnimation(float dt)
{

	if (actualState == ST_JUMP)
	{

		canJump1 = false;
		current_animation = &jump;
		
		if (grabing == false)
		{
			if (energyJump < gravity)
			{
				if (energyJump == iJumpF) { App->audio->PlayFx(1, 0); }
				energyJump += incrementJ;
				position.y = position.y + energyJump;
				if (energyJump < 0)
				{
					canjumpPlat = true;
					goingdown = false;
				}
				else 
				{
					goingdown = true;
					canjumpPlat = false;
				}
			}
		}
		if (grabing == true)
		{
			if (energyJump < gravity)
			{
				if (energyJump == iJumpF) { App->audio->PlayFx(1, 0); }
				energyJump += incrementJ;
				position.y = position.y + energyJump;
				if (goleft == true && nojumpingleft == true)
				{
					position.x = position.x - energyGrab;
					controls = true;
				}
				if (goright == true && nojumpingright == true)
				{
					position.x = position.x + energyGrab;
					controls = true;
					
				}
				if (energyJump < 0)
				{
					canjumpPlat = true;
					goingdown = false;
				}
				else 
				{
					goingdown = true;
					canjumpPlat = false;
				}
			}
		}

		if (controls == false)
		{
			if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
			{
				position.x = position.x - speed;
				blit = true;
			}
			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				position.x = position.x + speed;
				blit = false;
			}
		}
	}

	if (actualState == ST_RUN )
	{
		current_animation = &run;
	}

	if (actualState == ST_IDLE)
	{
		current_animation = &idle;
	}

	if (isshooting == true)
	{
		if (actualState == ST_IDLE|| actualState == ST_JUMP)
		{
			current_animation = &shoot;
			if (SDL_GetTicks() > shoottime + 300)
			{
				isshooting = false;
				shootfinish = false;
				shoot.Reset();
			}
		}
	}

	if (isrunshooting == true)
	{
		current_animation = &shoot_run;
		if (SDL_GetTicks() > shootruntime + 300)
		{
			isrunshooting = false;
			shootrunfinish = false;
			shoot_run.Reset();
		}
	}

	if (actualState == ST_DEAD) 
	{
		current_animation = &death;
	}

	if (grabing == true)
	{
		current_animation = &grab;
		gravity = gGravity;
		position.y = position.y + slipping;
	}
	if (fallingravity == true && godMode == false && canjumpPlat == false)
	{

		grabFinish = false;

		if (SDL_GetTicks() > timegrab2 + timeAccelerationDelay)
		{	
			if (energyfalling < maxAcceleration)
			{
				gravity = gravity + energyfalling;
				energyfalling = energyfalling + acceleration;
			}
		}

	}
	fallingravity = true;
}

void j1Player::OnCollision(Collider* c1, Collider* c2) 
{

	if (collider == c1 && c2->type == COLLIDER_FLOOR)
	{
		timegrab2 = SDL_GetTicks();
		energyfalling = 0;
		grab_falling = false; 
		gravity = igravity;
		position.y = lasPosition.y;
		if ((position.y + playerHeight) > c2->rect.y && position.y < c2->rect.y) // this is because the gravity makes colliders go weird with this 
		{
			position.y = position.y-2;                                 //the colliders from the player works well
		}
		canJump1 = true;
		if ((position.y + playerHeight2) > c2->rect.y || position.y > c2->rect.y)
		{
			position.x = lasPosition.x;
		}
	}

	if (collider == c1 && c2->type == COLLIDER_PLATAFORM)
	{
		timegrab2 = SDL_GetTicks();
		energyfalling = 0;
		grab_falling = false;
		gravity = igravity;
		if ((position.y + playerHeight2) < (c2->rect.y+1) && (c2->rect.y + 2)|| goingdown == true)
		{
			position.y = lasPosition.y;
			canJump1 = true;
		}
		if ((position.y + playerHeight2) > (c2->rect.y+3) && goingdown==true)
		{
			position.y = position.y + gravity;
		}
	}

	if (collider == c1 && c2->type == COLLIDER_DEATH || collider == c1 && c2->type == COLLIDER_ENEMY)
	{
		timegrab2 = SDL_GetTicks();
		energyfalling = 0;
		dead_animation = true;
		position.y = lasPosition.y;
		
		if (count_dead == false)
		{
			dead_animation_finish = SDL_GetTicks();
			App->audio->PlayFx(2, 0);
			count_dead = true;
		}
		if (SDL_GetTicks() > dead_animation_finish + deadDelay)
		{
			dead = true;
			dead_animation = false;
			count_dead = false;
		}
	}
	if (collider == c1 && c2->type == COLLIDER_WALL)
	{
		timegrab2 = SDL_GetTicks();
		energyfalling = 0;
		grab_falling = true;
		grabing = true;
		grabFinish = true;
		canJump1 = true;
		position.x = lasPosition.x;

		if (position.x > c2->rect.x)
		{
			nojumpingright = false;
			nojumpingleft = true;
		}
		else
		{
			nojumpingleft = false;
			nojumpingright = true;
		}
	}

	if (collider == c1 && c2->type == COLLIDER_NEXTMAP)
	{
		map_next = true;
	}

}

// Load Game State
bool j1Player::load(pugi::xml_node& savegame)
{
	lasPosition.x = savegame.child("posx").attribute("x").as_int();
	lasPosition.y = savegame.child("posy").attribute("y").as_int();
	position.x = savegame.child("posx").attribute("x").as_int();
	position.y = savegame.child("posy").attribute("y").as_int();
	return true;
}

// Save Game State
bool j1Player::save(pugi::xml_node& savegame)
{
	savegame.append_child("posx").append_attribute("x").set_value(position.x);
	savegame.append_child("posy").append_attribute("y").set_value(position.y);

	return true;
}
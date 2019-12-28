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
#include<stdio.h>
#include "j1Colliders.h"
#include "p2Log.h"
#include "j1EntityManager.h"
#include "j1Entity.h"

j1Player::j1Player(int posx, int posy) : j1Entity(entityType::PLAYER)
{ 
	LoadConfigInfo();

	name.create("player");

	// Initializing variables
	actualState = ST_IDLE;
	position.x = posx;
	position.y = posy;

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

	pause.PushBack({ 0,0,42,52 }, 0.2, 0, 0);
}

j1Player::~j1Player()
{}

bool j1Player::Start()
{
	// Load Fx 
	App->audio->LoadFx(jumpFx.GetString());
	App->audio->LoadFx(deadFx.GetString());
	App->audio->LoadFx(throwrockFx.GetString());
	App->audio->LoadFx(ballhitFx.GetString());
	App->audio->LoadFx(ghostdeadFx.GetString());
	App->audio->LoadFx(ghostfollowFx.GetString());
	App->audio->LoadFx(slimedeadFx.GetString());
	App->audio->LoadFx(checkPoint.GetString());
	App->audio->LoadFx(coin.GetString());
	App->audio->LoadFx(push_button.GetString());
	// Add player collider
	collider = App->colliders->AddCollider({ position.x,position.y, width, high }, COLLIDER_PLAYER, this); //a collider to start COLLIDER PLAYER

	energyfalling = 0;

	return true;
}

bool j1Player::CleanUp() 
{
	App->audio->UnloadFx(jumpFx.GetString());
	App->audio->UnloadFx(deadFx.GetString());
	App->audio->UnloadFx(throwrockFx.GetString());
	App->audio->UnloadFx(ballhitFx.GetString());
	App->audio->UnloadFx(ghostdeadFx.GetString());
	App->audio->UnloadFx(ghostfollowFx.GetString());
	App->audio->UnloadFx(slimedeadFx.GetString());
	App->audio->UnloadFx(checkPoint.GetString());
	App->audio->UnloadFx(coin.GetString());
	App->audio->UnloadFx(push_button.GetString());
	return true;
}

bool j1Player::Update(float dt) 
{
	BROFILER_CATEGORY("UpdatePlayer", Profiler::Color::Pink);

	App->render->player_pos.x = position.x;
	//LOG("PLAYER LIVES= %i", App->scene->lives);
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
			if (ground == false)
			{
				position.y += (int)(gravity * dt * VELOCITY);
			}
		}
	}
	ground = false;
	if (App->scene->pause == false)
	{
		CheckInputState(dt);
		CheckAnimation(dt);
	}

	if (App->scene->pause == true)
	{
		current_animation = &pause;
		position = lasPosition;
	}

	// Player colliders
	collider->SetPos(position.x, position.y);

	// Print player
	if (blit == false)
	{
		App->render->Blit(App->entity->player_graphics, position.x + current_animation->pivotx[current_animation->returnCurrentFrame()], position.y + current_animation->pivoty[current_animation->returnCurrentFrame()], &(current_animation->GetCurrentFrame(dt)), 1.0f);
		App->particles->Projectile.speed.x = (6 * dt * 60);
	}
	else
	{
		App->render->BlitWithScale(App->entity->player_graphics, position.x + fixBlit + (-current_animation->pivotx[current_animation->returnCurrentFrame()]), position.y + current_animation->pivoty[current_animation->returnCurrentFrame()], &(current_animation->GetCurrentFrame(dt)), -1, 1.0f, 1, TOP_RIGHT);
		App->particles->Projectile_flip.speed.x = -(6 * dt * 60);
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
	speed = 3;
	return true;
}

bool j1Player::PostUpdate(float dt)
{
	BROFILER_CATEGORY("PostupdatePlayer", Profiler::Color::HotPink)

	

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
			collider = App->colliders->AddCollider({ position.x,position.y, width, high }, NO_COLLIDER, this);
			godMode = true;
		}
		else if (godMode == true)
		{
			collider->to_delete = true;
			collider = App->colliders->AddCollider({ position.x,position.y, width, high }, COLLIDER_PLAYER, this);
			godMode = false;
		}
	}

	if (godMode == true)
	{
		actualState = ST_IDLE;

		// Map limits for God mode
		if (position.x < 0)
		{
			position.x = 0;
		}
		if (position.y < 0)
		{
			position.y = 0;
		}
		else if (position.y > 713)
		{
			position.y = 713;
		}

		// Controls for god mode
		if (App->input->GetKey(SDL_SCANCODE_W) == KEY_REPEAT)
		{
			position.y -= (int)(speedgm * dt * VELOCITY);
		}
		if (App->input->GetKey(SDL_SCANCODE_S) == KEY_REPEAT)
		{
			position.y += (int)(speedgm * dt * VELOCITY);
		}
		if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT)
		{
			position.x -= (int)(speedgm * dt * VELOCITY);
		}
		if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
		{
			position.x += (int)(speedgm * dt * VELOCITY);
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
		if (App->particles->particle_jump == true)
		{
			App->particles->particle_jump_time = SDL_GetTicks();
			App->particles->particle_jump = false;
		}
		if (SDL_GetTicks() > App->particles->particle_jump_time + 201)
		{
			App->particles->isjumping = false;
		}

		// Player controllers
		if (App->input->GetKey(SDL_SCANCODE_SPACE) == KEY_DOWN && dead_animation == false && dead_monster_animation == false)
		{
			actualState = ST_JUMP;

			App->particles->isjumping = true;
			App->particles->particle_jump = true;

			if (canJump1 == true)
			{
				App->particles->AddParticle(App->particles->jump_particle, lasPosition.x + 5, lasPosition.y + 50, NO_COLLIDER);
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
			App->audio->PlayFx(3, 0);

			App->particles->explosion_time_init = true;
			App->particles->explosion_finish = true;
			App->particles->explosion = true;
			App->particles->hitobject = false;

			if (blit == false)
			{
				App->particles->explosion_right = true;
				App->particles->AddParticle(App->particles->Projectile, lasPosition.x + 10, lasPosition.y + 30, COLLIDER_PLAYER_SHOT);
			}
			else
			{
				App->particles->explosion_right = false;
				App->particles->AddParticle(App->particles->Projectile_flip, lasPosition.x + 10, lasPosition.y + 30, COLLIDER_PLAYER_SHOT);	
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
			App->audio->PlayFx(3, 0);

			App->particles->explosion_time_init = true;
			App->particles->explosion_finish = true;
			App->particles->explosion = true;
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
				position.x -= (int)(speed * dt * VELOCITY);
				goright = false;
			}
			if (goright == true)
			{
				position.x += (int)(speed * dt * VELOCITY);
				goleft = false;
			}

			if (shootrunfinish == false)
			{
				shootruntime = SDL_GetTicks();
				shootrunfinish = true;
			}
		}

		else if (App->input->GetKey(SDL_SCANCODE_A) == KEY_REPEAT && canJump1 == true && dead_animation == false && dead_monster_animation == false && controls == false && isshooting == false)
		{
			speed = 3;
			actualState = ST_RUN;
			position.x -= (int)(speed * dt * VELOCITY);
			blit = true;

			goright = false;
			goleft = true;
			
			// Reset animations
			idle.Reset();
			jump.Reset();
			death.Reset();
			grab.Reset();	
		}

		else if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT && canJump1 == true && dead_animation == false && dead_monster_animation == false && controls == false && isshooting == false)
		{
			speed = 3;
			actualState = ST_RUN;
			position.x += (int)(speed * dt * VELOCITY);
			blit = false;

			goleft = false;
			goright = true;
			
			// Reset animations
			idle.Reset();
			jump.Reset();
			death.Reset();
			grab.Reset();
		}

		else if (canJump1 == true && App->input->GetKey(SDL_SCANCODE_D) == NULL && App->input->GetKey(SDL_SCANCODE_A) == NULL && App->input->GetKey(SDL_SCANCODE_SPACE) == NULL && dead_animation == false && dead_monster_animation == false && grabing == false && isshooting == false)
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
		
		else if (dead_monster_animation == true)
		{
			actualState = ST_DEADMONS;
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
				if (energyJump == iJumpF) { App->audio->PlayFx(1, 0);}
				energyJump += (incrementJ * dt * VELOCITY);
				position.y += (int)(energyJump * dt * VELOCITY);
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
				if (energyJump == iJumpF) { App->audio->PlayFx(1, 0);}
				energyJump += (incrementJ * dt * VELOCITY);
				position.y += (int)(energyJump * dt * VELOCITY);
				if (goleft == true && nojumpingleft == true)
				{
					position.x -= (int)(energyGrab * dt * VELOCITY);
					controls = true;
				}
				if (goright == true && nojumpingright == true)
				{
					position.x += (int)(energyGrab * dt * VELOCITY);
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
				position.x -= (int)(speed * dt * VELOCITY);
				blit = true;
			}
			if (App->input->GetKey(SDL_SCANCODE_D) == KEY_REPEAT)
			{
				position.x += (int)(speed * dt * VELOCITY);
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
		if (actualState == ST_IDLE || actualState == ST_JUMP)
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

	if (actualState == ST_DEADMONS)
	{
		current_animation = &death;

		if (SDL_GetTicks() > dead_monster_animation_finish + deadDelay)
		{
			App->scene->player_dead = true;
			dead_monster_animation = false;
			count_monster_dead = false;
		}
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
		canJump1 = true;
		ground = true;
		timegrab2 = SDL_GetTicks();
		energyfalling = 0;
		grab_falling = false;
		gravity = igravity;
		ground = true;
		if (position.y >= (c2->rect.y))// under a floor collision
		{
			canJump1 = false;
			position.y = c2->rect.y + c2->rect.h + 1;
			ground = false;
		}
		else if (position.y + high > c2->rect.y && position.x < (c2->rect.x + c2->rect.w) && (position.x + width) >(c2->rect.x))// over a floor collision  
		{
			position.y = c2->rect.y - high;
		}


	}

	if (collider == c1 && c2->type == COLLIDER_PLATAFORM && App->scene->lowfps == false)
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
	if (collider == c1 && c2->type == COLLIDER_PLATAFORM && App->scene->lowfps == true)
	{
		if (position.y + 40 < c2->rect.y && canjumpPlat == false)// over a floor collision
		{
			canJump1 = true;
			energyfalling = 0;
			position.y = c2->rect.y - high;
			ground = true;
		}
		else // under a lowcorner floor collision
		{

		}
	}

	if (collider == c1 && c2->type == COLLIDER_DEATH)
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
			App->scene->coin_number = 0;
			App->scene->player_score = 0;
			App->scene->player_dead = true;
			dead_animation = false;
			count_dead = false;
			current_lives = current_lives - 1;
		}
	}

	if (collider == c1 && c2->type == COLLIDER_ENEMY)
	{
		
		deaddead++;
		if (count_monster_dead == false)
		{
			dead_monster_animation_finish = SDL_GetTicks();
			App->audio->PlayFx(2, 0);
			dead_monster_animation = true;
			count_monster_dead = true;
			if (deaddead == 1) 
			{
				App->scene->player_score = 0;
				App->scene->coin_number = 0;
				deaddead = 0;
			}
			
		}
		to_delete = true;
	}
	else {
		to_delete = false;
	}
	


	if (collider == c1 && c2->type == COLLIDER_WALL)
	{
		speed = 0;
		number = ((position.x + width) - c2->rect.x);
		timegrab2 = SDL_GetTicks();
		energyfalling = 0;
		grab_falling = true;
		grabing = true;
		grabFinish = true;
		canJump1 = true;
		position.x = lasPosition.x;
		/*if (goright == true) {
			position.x = c2->rect.x-(playerwidth+number-10);
		}
		if (goleft == true) {
			position.x = c2->rect.x+c2->rect.w;
		}*/

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

	if (collider == c1 && c2->type == COLLIDER_CORNER)
	{
		if (position.y >= ceil(c2->rect.y + (c2->rect.h/1.5)))// under a floor collision
		{
			position.y = c2->rect.y + c2->rect.h + 1;
			ground = false;
		}
	}

	if (collider == c1 && c2->type == COLLIDER_LOW_CORNER)
	{
		if (position.y + 35 < c2->rect.y)// over a floor collision
		{
			canJump1 = true;
			energyfalling = 0;
			position.y = c2->rect.y-high;
			ground = true;
		}
		else // under a lowcorner floor collision
		{
			
		}
	}

	if (collider == c1 && c2->type == COLLIDER_NEXTMAP)
	{
		App->scene->player_map_next = true;
	}

}

bool j1Player::LoadConfigInfo()
{
	// Loading files from config
	pugi::xml_document	config_file;
	pugi::xml_node		config;
	config = App->LoadConfig(config_file);
	config = config.child("player");

	// Player width and high
	width = config.child("width").attribute("w").as_int();
	high = config.child("high").attribute("h").as_int();

	// Player Fx

	jumpFx = config.child("fx_name").attribute("jump").as_string("");
	deadFx = config.child("fx_name2").attribute("dead").as_string("");
	throwrockFx = config.child("fx_name3").attribute("throwrock").as_string("");
	ballhitFx = config.child("fx_name4").attribute("ballhit").as_string("");
	checkPoint = config.child("fx_name8").attribute("checkPoint").as_string("");
	coin = config.child("fx_name9").attribute("coin").as_string("");
	push_button = config.child("fx_name10").attribute("button").as_string("");
	// Ghost FX
	ghostdeadFx = config.child("fx_name5").attribute("ghost_dead").as_string("");
	ghostfollowFx = config.child("fx_name6").attribute("ghost_follow").as_string("");

	// Slime FX
	slimedeadFx = config.child("fx_name7").attribute("slime_dead").as_string("");

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
	iJumpF = config.child("iJumpF").attribute("j").as_float();

	// Jump force
	jumpF = config.child("jumpF").attribute("j").as_float();

	// Jump force when grabbed
	jumpG = config.child("jumpG").attribute("g").as_float();

	// Slipping velocity
	slipping = config.child("slipping").attribute("s").as_int();

	// Grab time delay
	timeGrabDelay = config.child("timeGrabDelay").attribute("time").as_int();

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

	return true;
}
#include "j1EntityManager.h"
#include "j1Entity.h"
#include "p2Defs.h"
#include "p2Log.h"
#include "j1App.h"
#include "j1Textures.h"
#include "j1Input.h"
#include "j1Scene.h"
#include "j1Audio.h"
#include "j1Render.h"
#include "j1Window.h"

j1Entity::j1Entity(entityType type) : type(type)
{
	name.create("entity");
}

j1Entity::~j1Entity() 
{

}

bool j1Entity::Awake(pugi::xml_node& config)
{
	//int j = 1 + 1;
	// Player width and high
	/*player_width = config.child("width").attribute("w").as_int();
	player_high = config.child("high").attribute("h").as_int();

	// Play Fx
	jumpFx = config.child("fx_name").attribute("jump").as_string("");
	deadFx = config.child("fx_name2").attribute("dead").as_string("");
	throwrockFx = config.child("fx_name3").attribute("throwrock").as_string("");
	ballhitFx = config.child("fx_name4").attribute("ballhit").as_string("");

	// Ghost dead FX
	ghostdeadFx = config.child("fx_name5").attribute("ghost_dead").as_string("");

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
	fixBlit = config.child("fixBlit").attribute("fix").as_int();*/

	return true;
}

bool j1Entity::CleanUp() 
{

	return true;
}

bool j1Entity::save(pugi::xml_node& savegame)
{
	savegame.append_child("position");

	savegame.append_attribute("type") = name.GetString();
	savegame.child("position").append_attribute("pos.x") = position.x;
	savegame.child("position").append_attribute("pos.y") = position.y;
	return true;
}

// Load Game State
bool j1Entity::load(pugi::xml_node& savegame)
{
	/*savegame.append_child("position");

	savegame.append_attribute("type") = name.GetString();
	savegame.child("position").append_attribute("pos_x") = position.x;
	savegame.child("position").append_attribute("pos_y") = position.y;*/
	return true;
}

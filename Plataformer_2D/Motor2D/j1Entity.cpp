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

j1Entity::j1Entity(Types type) : type(type)
{
}

j1Entity::~j1Entity() 
{

}


bool j1Entity::CleanUp() 
{

	return true;
}

bool j1Entity::save(pugi::xml_node& data)
{

	return true;
}

bool j1Entity::load(pugi::xml_node& data) 
{
	
	return true;
}
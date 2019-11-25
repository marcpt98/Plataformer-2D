#ifndef __j1MAP_H__
#define __j1MAP_H__

#include "PugiXml/src/pugixml.hpp"
#include "p2List.h"
#include "p2Point.h"
#include "j1Module.h"


// ----------------------------------------------------
struct MapLayer
{
	p2SString	name;
	int			width = 0;
	int			height = 0;
	float		speed = 0;
	uint*		data=nullptr;

	MapLayer() : data(NULL)
	{}

	~MapLayer()
	{
		RELEASE(data);
	}

	inline uint Get(int x, int y) const
	{
		return x + y * width;	
	}
};

// ----------------------------------------------------
struct TileSet
{
	SDL_Rect GetTileRect(int id) const;

	p2SString			name;
	int					firstgid = 0;
	int					margin = 0;
	int					spacing = 0;
	int					tile_width = 0;
	int					tile_height = 0;
	SDL_Texture*		texture = nullptr;
	int					tex_width = 0;
	int					tex_height = 0;
	int					num_tiles_width = 0;
	int					num_tiles_height = 0;
	int					offset_x = 0;
	int					offset_y = 0;
	uint* data=nullptr;

	TileSet(): data(NULL)
	{}

	~TileSet()
	{
		RELEASE(data);
	}
};

struct ObjectGroup 
{
	p2SString name = "No name";
	int size = 0;
	SDL_Rect* object=nullptr;
	uint* data=nullptr;

	ObjectGroup(): data(NULL)
	{}

	~ObjectGroup()
	{
		RELEASE(data);
	}
};


enum MapTypes
{
	MAPTYPE_UNKNOWN = 0,
	MAPTYPE_ORTHOGONAL,
	MAPTYPE_ISOMETRIC,
	MAPTYPE_STAGGERED
};
// ----------------------------------------------------
struct MapData
{
	int					width = 0;;
	int					height = 0;;
	int					tile_width = 0;;
	int					tile_height = 0;;
	SDL_Color			background_color;
	MapTypes			type;
	p2List<TileSet*>	tilesets;
	p2List<MapLayer*>	layers;
	p2List<ObjectGroup*> objectgroups;
	uint* data = nullptr;

	MapData() : data(NULL)
	{}

	~MapData()
	{
		RELEASE(data);
	}
};

// ----------------------------------------------------
class j1Map : public j1Module
{
public:

	j1Map();

	// Destructor
	virtual ~j1Map();

	// Called before render is available
	bool Awake(pugi::xml_node& conf);

	// Called each loop iteration
	void Draw();

	// Called before quitting
	bool CleanUp();

	// Load new map
	bool Load(const char* path);

	// Change actual map and music
	bool ChangeMapMusic(p2SString* map, p2SString* music);

	// Coordinate translation methods
	iPoint MapToWorld(int x, int y) const;
	iPoint WorldToMap(int x, int y) const;

private:

	bool LoadMap();
	bool LoadTilesetDetails(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadTilesetImage(pugi::xml_node& tileset_node, TileSet* set);
	bool LoadLayer(pugi::xml_node& node, MapLayer* layer);
	bool LoadObjectGroup(pugi::xml_node& node, ObjectGroup* objectgroup);
public:

	MapData data;

private:

	pugi::xml_document	map_file;
	p2SString			folder;
	bool				map_loaded = false;
	float				parallax = 0;
};

#endif // __j1MAP_H__
#ifndef __j1RENDER_H__
#define __j1RENDER_H__

#include "SDL/include/SDL.h"
#include "p2Point.h"
#include "j1Module.h"

enum RENDER_PIVOT
{
	TOP_RIGHT,
	TOP_LEFT,
	MIDDLE
};

class j1Render : public j1Module
{
public:

	j1Render();

	// Destructor
	virtual ~j1Render();

	// Called before render is available
	bool Awake(pugi::xml_node&);

	// Called before the first frame
	bool Start();

	// Called each loop iteration
	bool PreUpdate();
	bool Update(float dt);
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Blit
	void SetViewPort(const SDL_Rect& rect);
	void ResetViewPort();
	iPoint ScreenToWorld(int x, int y) const;
	bool Blit(SDL_Texture* texture, int x, int y, const SDL_Rect* section = NULL, float speed = 1, double angle = 0, int pivot_x = INT_MAX, int pivot_y = INT_MAX) const;
	bool DrawQuad(const SDL_Rect& rect, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool filled = true, bool use_camera = true) const;
	bool DrawLine(int x1, int y1, int x2, int y2, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool use_camera = true) const;
	bool DrawCircle(int x1, int y1, int redius, Uint8 r, Uint8 g, Uint8 b, Uint8 a = 255, bool use_camera = true) const;

	// BlitWithScale
	bool BlitWithScale(SDL_Texture* texture, int x, int y, SDL_Rect* section, float scale, float speed, float fillAmount, RENDER_PIVOT pivot);

	// Set background color
	void SetBackgroundColor(SDL_Color color);

public:

	SDL_Renderer*	renderer = nullptr;
	SDL_Rect		camera;
	SDL_Point		camera_offset;
	SDL_Rect		viewport;
	SDL_Color		background;

	// Camera scale
	int				cameraScale;
	int				cameraOffset;

	// Map limits
	int MapLimitStart;
	int MapLimitEnd;

	// Player
	iPoint player_pos;
};

#endif // __j1RENDER_H__
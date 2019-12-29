#ifndef __j1GUI_H__
#define __j1GUI_H__

#include "j1Module.h"
#include "p2Point.h"
#include "SDL/include/SDL_rect.h"

#define CURSOR_WIDTH 2

// UI_classes
struct _TTF_Font;
struct SDL_Texture;
class UI_text;
class UI_image;
class UI_button;
class UI_boolbutton;
class UI_window;
class UI_slider;

enum event_type
{
	MOUSE_ENTER,
	MOUSE_LEAVE,
	MOUSE_RIGHT_CLICK,
	MOUSE_RIGHT_RELEASE,
	MOUSE_LEFT_CLICK,
	MOUSE_LEFT_RELEASE
};


// ---------------------------------------------------
class j1Gui : public j1Module
{
public:

	j1Gui();

	// Destructor
	virtual ~j1Gui();

	// Called when before render is available
	bool Awake(pugi::xml_node&);

	// Call before first frame
	bool Start();

	// Called before all Updates
	bool PreUpdate();

	// Called after all Updates
	bool PostUpdate();

	// Called before quitting
	bool CleanUp();

	// Gui creation functions
	UI_text* AddText(char* text, int x, int y, _TTF_Font* font, SDL_Color color = { 255, 255, 255, 255 }, j1Module* callback = nullptr);
	UI_image* AddImage(SDL_Texture* texture, int x, int y, SDL_Rect section, j1Module* callback = nullptr);
	UI_button* AddButton(int x, int y, SDL_Texture* texture, SDL_Rect standby, SDL_Rect OnMouse, SDL_Rect OnClick, j1Module* callback = nullptr);
	UI_boolbutton* AddBoolButton(int x, int y, SDL_Texture* texture, SDL_Rect booltrue, SDL_Rect boolfalse, j1Module* callback = nullptr);
	UI_window* AddWindow(SDL_Texture* texture, int x, int y, SDL_Rect section, j1Module* callback = nullptr);
	UI_slider* AddSlider(int x, int y, SDL_Texture* texture, UI_button* button, j1Module* callback, SDL_Rect image_bar);
	SDL_Texture* GetAtlas();

	bool UIDebugDraw();

	bool DeleteGui(UI_element* gui);

public:
	bool UI_debug = false;

private:

	SDL_Texture* atlas;
	p2SString atlas_file_name;
	p2List<UI_element*> UI_elements;

public:
	SDL_Texture* scene_intro;
	p2SString scene_intro_name;
	SDL_Texture* title_intro;
	p2SString title_intro_name;
	SDL_Texture* licence;
	p2SString licence_name;
	SDL_Texture* addText;
	p2SString addText_name;
	SDL_Texture* list;
	p2SString list_name;
};

#endif // __j1GUI_H__

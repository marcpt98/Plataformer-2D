#pragma once
#ifndef __j1CONSOLE_H__
#define __j1CONSOLE_H__

#include "j1Module.h"
#include "p2List.h"
#include "p2DynArray.h"
#include "UI_text.h"

struct _TTF_Font;

class j1Console : public j1Module
{
public:

	j1Console();
	~j1Console();

	// Called before the first frame
	bool Start();

	// Called before each loop iteration
	bool PreUpdate(float dt);

	// Called each loop iteration
	bool Update(float dt);

	// Called before all Updates
	bool PostUpdate(float dt);

	// Called before quitting
	bool CleanUp();

	// Check player input
	bool Checkinput();

	// Open console
	void Open();

	// Close console
	void Close();

public:
	// Text open console
	UI_text* opened_text = nullptr;
	UI_text* insert_text = nullptr;
	
	// Text player input
	UI_text* text_1 = nullptr;
	UI_text* text_2 = nullptr;
	UI_text* text_3 = nullptr;
	UI_text* text_4 = nullptr;

	bool firstletter = false;
	bool secondletter = false;
	bool thirdletter = false;
	bool forthletter = false;
	
	bool opened = false;
	_TTF_Font* Text_font = nullptr;

	int textmax = 4;
	int currenttext = 0;
	int textdistance = 0;

	// GodMode command
	bool text_1_god = false;
	bool text_2_god = false;
	bool text_3_god = false;
	bool godConsole = false;

	// Quit command
	bool text_1_quit = false;
	bool text_2_quit = false;
	bool text_3_quit = false;
	bool text_4_quit = false;

	// Map command
	bool loadmap1();
	bool loadmap2();
	bool text_1_map = false;
	bool text_2_map = false;
	bool text_3_map = false;
	bool text_4_map1 = false;
	bool text_4_map2 = false;

	// FPS command
	bool text_1_FPS = false;
	bool text_2_FPS = false;
	bool text_3_FPS = false;
	bool text_4_FPS30 = false;
	bool text_4_FPS60 = false;

	// List command
	bool text_1_list = false;
	bool text_2_list = false;
	bool text_3_list = false;
	bool text_4_list = false;
	UI_element* img_list = nullptr;
};

#endif // !__j1MAINMENU_H__

#include "j1App.h"
#include "UI_Window.h"
#include "j1App.h"
#include "j1Render.h"
#include "p2Defs.h"
#include "j1Gui.h"
#include "j1Render.h"

UI_window::UI_window()
{}

UI_window::~UI_window()
{}

void UI_window::BlitElement()
{
	BROFILER_CATEGORY("Blitwindow", Profiler::Color::SandyBrown)

	iPoint globalPos = calculateAbsolutePosition();
	App->render->Blit(texture, globalPos.x, globalPos.y, &section, false);
}
#include "UI_slider.h"
#include "j1App.h"
#include "j1Render.h"
#include "UI_Button.h"
#include "UI_Button.h"
#include "j1Scene_UI.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Input.h"
#include "p2Log.h"

void UI_slider::BlitElement()
{
	BROFILER_CATEGORY("Blitslider", Profiler::Color::Null)

	App->input->GetMousePosition(x, y);
	iPoint globalPos = calculateAbsolutePosition();
	App->render->Blit(texture, globalPos.x - 250, globalPos.y, &section, false);
	slider_button->BlitElement();
	
}
void UI_slider::ChangeVolume()
{
	position = x;
	LOG("%i", position);
	

}
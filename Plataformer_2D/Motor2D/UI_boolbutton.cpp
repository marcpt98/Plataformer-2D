#include "UI_Button.h"
#include "j1App.h"
#include "j1Render.h"
#include "UI_boolbutton.h"
#include "j1App.h"
#include "j1Render.h"
#include "j1Scene_UI.h"

void UI_boolbutton::BlitElement()
{
	BROFILER_CATEGORY("Blitboolbutton", Profiler::Color::WhiteSmoke)

	iPoint globalPos = calculateAbsolutePosition();

	if (App->sceneui->iscap == true)
	{
		App->render->Blit(texture, globalPos.x, globalPos.y, &booltrue, false);
	}
	else
	{
		App->render->Blit(texture, globalPos.x, globalPos.y, &boolfalse, false);
	}
}
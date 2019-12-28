#include "UI_Image.h"
#include "j1App.h"
#include "j1Render.h"

void UI_image::BlitElement()
{
	BROFILER_CATEGORY("Blitimage", Profiler::Color::Navy)

	iPoint globalPos = calculateAbsolutePosition();
	if (section.w != 0 && section.h != 0)
		App->render->Blit(texture, globalPos.x, globalPos.y, &section, false);
	else
		App->render->Blit(texture, globalPos.x, globalPos.y, nullptr, false);
}
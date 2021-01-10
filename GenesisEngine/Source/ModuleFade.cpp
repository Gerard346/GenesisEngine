#include "Globals.h"
#include "Application.h"
#include "ModuleFade.h"
#include "glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "ImGuizmo/ImGuizmo.h"

ModuleFade::ModuleFade(bool start_enabled) :Module(start_enabled)
{
	name = "fade";
}

ModuleFade::~ModuleFade()
{
}

bool ModuleFade::Init()
{
	return true;
}

bool ModuleFade::CleanUp()
{
	return true;
}

update_status ModuleFade::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleFade::Update(float dt)
{
	return UPDATE_CONTINUE;
}

update_status ModuleFade::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

bool ModuleFade::FadeToBlack(float time)
{
	if (current_step == NONE) {
		current_step = FADE_TO_BLACK;
		start_time = SDL_GetTicks();
		total_time = (Uint32)(time * 0.5f * 1000.0f);
	}

	return true;
}

bool ModuleFade::FadeToColor(float time)
{
	if (current_step == NONE) {
		current_step = FADE_FROM_BLACK;
		start_time = SDL_GetTicks();
		total_time = (Uint32)(time * 0.5f * 1000.0f);
	}

	return true;
}

bool ModuleFade::DrawFade()
{
	if (current_step == NONE) {
		return true;
	}

	Uint32 now = SDL_GetTicks() - start_time;
	float normalized = MIN(1.0f, (float)now / (float)total_time);

	switch (current_step) {
	case FADE_TO_BLACK:
	{
		if (now >= total_time) {
			total_time += total_time;
			start_time = SDL_GetTicks();
			current_step = FADE_FROM_BLACK;
			App->Load("Library/Scenes/main_menu.scene");

			App->input->SetActive();
		}
	}	break;

	case FADE_FROM_BLACK:
	{
		normalized = 1.0f - normalized;
		if (now >= total_time) {
			current_step = NONE;
			App->input->SetActive();
		}
	}break;
	}

	//Draw Rect
	float2 position;
	float width = App->window->width;
	float height = App->window->height;
	float size = 250.0f;

	position.x = 0 / 2;
	position.y = 000 / 2;
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	float hola = normalized * 255.0f / 100;
	glColor4f(0.0f, 0.0f, 0.0f, hola);
	glBegin(GL_QUADS);
	glVertex2f(0.0f, height);
	glVertex2f(0.0f, 0.0f);
	glVertex2f(width, 0.0f);
	glVertex2f(width, height);
	glEnd();

	return true;
}

fade_step ModuleFade::GetFadeStep()
{
	return current_step;
}

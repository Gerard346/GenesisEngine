#include "Globals.h"
#include "Application.h"
#include "UI.h"
#include "glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "ImGuizmo/ImGuizmo.h"

UI::UI(bool start_enabled) : Module(start_enabled)
{

}

UI::~UI()
{

}

bool UI::Init()
{
	return true;
}

bool UI::CleanUp()
{
	return true;
}

update_status UI::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status UI::Update(float dt)
{
	return UPDATE_CONTINUE;

}

update_status UI::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

void UI::SetUpOrtho()
{
	glPushAttrib(GL_TRANSFORM_BIT);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDisable(GL_CULL_FACE);
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_DEPTH_CLAMP);
	glDisable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Get Canvas size
	glOrtho(0.0f, App->window->width, 0.0f, App->window->height, 0.0f, 1.0f);//0,0 Top-Left, 640,480 Bot-right.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPopAttrib();
	
}

void UI::ResetRender()
{
	glPushAttrib(GL_TRANSFORM_BIT);
	glDisable(GL_BLEND);
	glEnable(GL_DEPTH_CLAMP);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glEnable(GL_LIGHTING);
	glPopAttrib();
	glViewport(0, 0, App->window->width, App->window->height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glPopMatrix();

	mat4x4 ProjectionMatrix = perspective(60.0f, (float)App->window->width / (float)App->window->height, 0.125f, 512.0f);
	glLoadMatrixf(&ProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
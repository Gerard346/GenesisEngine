#include "Globals.h"
#include "Application.h"
#include "UI.h"
#include "glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>

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
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	//Get Canvas size
	glOrtho(0, 640, 480, 0, 1, -1);//0,0 Top-Left, 640,480 Bot-right.
	glMatrixMode(GL_MODELVIEW);
}

void UI::ResetRender()
{

}
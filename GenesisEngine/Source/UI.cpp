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
	glOrtho(0.0f, App->window->width, 0.0f, App->window->height, 0.0f, 1.0f);//0,0 Top-Left, 640,480 Bot-right.
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	//
	float2 position;
	float width = App->window->width;
	float height = App->window->height;
	float size = 250.0f;

	position.x = 1000 / 2;
	position.y = 1000 / 2;

	static const GLfloat vertex[] = {
	position.x, position.y, 0,
	position.x + size, position.y,0,
	position.x, position.y + size,0,
	position.x + size, position.y + size, 0
	};

	static const GLuint index[] = {
		//Front
		0,1,2,
		2,1,3
	};

	/*
		static const GLfloat vertex[] = {
	position.x, position.y, 0,
	position.x + size, position.y+size,0,
	position.x+size, position.y + size, 0,
	position.x, position.y+size,0
	};
	static const GLuint index[] = {
		//Front
		2,1,0,
		2,3,0
	};
	*/
	GLuint vertex_buffer;
	//Create new buffer, gives uint
	glGenBuffers(1, &vertex_buffer);
	//Start using that buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	//send array to VRAM
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex) * 3, vertex, GL_STATIC_DRAW);

	glEnableClientState(GL_VERTEX_ARRAY);
	glBindBuffer(GL_ARRAY_BUFFER, vertex_buffer);
	glVertexPointer(3, GL_FLOAT, 0, NULL);

	GLuint index_buffer;

	glGenBuffers(1, &index_buffer);
	//Start using that buffer
	glBindBuffer(GL_ARRAY_BUFFER, index_buffer);
	//send array to VRAM
	glBufferData(GL_ARRAY_BUFFER, sizeof(index), index, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, index_buffer);

	glDrawElements(GL_TRIANGLES, (sizeof(index) / sizeof(GLuint)), GL_UNSIGNED_INT, NULL);

	glDisableClientState(GL_VERTEX_ARRAY);
}

void UI::ResetRender()
{
	glViewport(0, 0, App->window->width, App->window->height);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	//glPopMatrix();

	mat4x4 ProjectionMatrix = perspective(60.0f, (float)App->window->width / (float)App->window->height, 0.125f, 512.0f);
	glLoadMatrixf(&ProjectionMatrix);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
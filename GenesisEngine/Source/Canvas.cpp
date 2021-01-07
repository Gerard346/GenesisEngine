#include "ImGui/imgui.h"
#include "FileSystem.h"
#include "GnJSON.h"
#include "GameObject.h"
#include "Application.h"
#include "WindowAssets.h"
#include "Canvas.h"
#include "RectTransform.h"
#include "glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "ImGuizmo/ImGuizmo.h"

Canvas::Canvas() : Component(nullptr)
{
	type = ComponentType::CANVAS_UI;
	is_UI = true;
}

Canvas::Canvas(GameObject* gameobject) : Component(gameobject)
{
	type = ComponentType::CANVAS_UI;
	is_UI = true;
}

Canvas::~Canvas()
{
}

void Canvas::Update()
{
	Draw();
}

void Canvas::OnEditor()
{

}

void Canvas::Save(GnJSONArray& save_array)
{
}

void Canvas::Load(GnJSONObj& load_object)
{
}

void Canvas::Draw()
{
	RectTransform* ui_transform = _gameObject->GetRectTransform();
	float3 position;
	float width = _gameObject->GetRectTransform()->GetWidth();
	float height = _gameObject->GetRectTransform()->GetHeight();
	float size = 250.0f;

	position = ui_transform->GetPosition();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	glColor4f(1.0f, 1.0f, 1.0f, 0.5f);
	glBegin(GL_QUADS);
	glVertex2f(0.0f, height);
	glVertex2f(position.x, position.y);
	glVertex2f(width, 0.0f);
	glVertex2f(width, height);
	glEnd();
}

#include "ImGui/imgui.h"
#include "FileSystem.h"
#include "ModuleInput.h"
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
	gameobject->AddComponent(ComponentType::RECT_TRANSFORM);
	ui_transform = _gameObject->GetRectTransform();
}

Canvas::~Canvas()
{
}

void Canvas::Update()
{
	if (draggable && App->editor->MouseOnScene()) {

		if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT) {
			float3 canvas_pos = ui_transform->GetPosition();
			if (IsInsideCanvas()) {
				ui_transform->SetPosition(canvas_pos.x + App->input->GetMouseXMotion(), canvas_pos.y - App->input->GetMouseYMotion(), 0);
			}
		}
	}

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

	glVertex2f(position.x, position.y);
	glVertex2f(position.x + width, position.y);
	glVertex2f(position.x + width, position.y + height);
	glVertex2f(position.x, position.y + height);

	glEnd(); 
}

bool Canvas::IsInsideCanvas()
{
	float3 position = ui_transform->GetPosition();
	if (position.x < App->editor->mouseScenePosition.x < position.x + ui_transform->GetWidth()) {
		if (position.y < App->editor->mouseScenePosition.y < position.y + ui_transform->GetHeight())
			return true;
		else
			return false;
	}
		return false;
}



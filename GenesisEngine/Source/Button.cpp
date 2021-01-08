#include "Application.h"
#include "FileSystem.h"
#include "GameObject.h"
#include "Transform.h"
#include "RectTransform.h"
#include "GnJSON.h"
#include "Button.h"
#include "ResourceTexture.h"
#include "glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "ImGuizmo/ImGuizmo.h"

Button::Button() : Component(nullptr)
{
	type = ComponentType::BUTTON;
	is_UI = true;

	ui_transform = _gameObject->GetRectTransform();
	GameObject* canvas = ui_transform->GetCanvas();

	_gameObject->AddComponent(ComponentType::IMAGE);
}

Button::Button(GameObject* gameObject) : Component(gameObject)
{
	type = ComponentType::BUTTON;
	is_UI = true;
	_gameObject->AddComponent(ComponentType::IMAGE);

	ui_transform = _gameObject->GetRectTransform();
	GameObject* canvas = ui_transform->GetCanvas();

}

Button::~Button()
{
}

void Button::Update()
{
	if (ui_transform->GetVisible()) {
		if (ui_transform->GetInteractive()) {
			if (App->editor->MouseOnScene()) {
				if (ui_transform->IsInsideUIElement()) {
					Hover();
					if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT) {
						OnClicked();
					}
				}
			
			}
		}
	}
}

void Button::OnEditor()
{
}

void Button::Save(GnJSONArray& save_array)
{
}

void Button::Load(GnJSONObj& load_object)
{
}

void Button::OnClicked()
{
	float width = _gameObject->GetRectTransform()->GetWidth();
	float height = _gameObject->GetRectTransform()->GetHeight();
	float3 position;

	position = ui_transform->GetPosition();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor4f(0.0f, 0.0f, 0.0f, 0.7f);
	glBegin(GL_QUADS);

	glVertex2f(position.x, position.y);
	glVertex2f(position.x + width, position.y);
	glVertex2f(position.x + width, position.y + height);
	glVertex2f(position.x, position.y + height);

	glEnd();
}

void Button::Hover()
{
	float width = _gameObject->GetRectTransform()->GetWidth();
	float height = _gameObject->GetRectTransform()->GetHeight();
	float3 position;

	position = ui_transform->GetPosition();

	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
	glColor4f(1.0f, 1.0f, 1.0f, 0.35f);
	glBegin(GL_QUADS);

	glVertex2f(position.x, position.y);
	glVertex2f(position.x + width, position.y);
	glVertex2f(position.x + width, position.y + height);
	glVertex2f(position.x, position.y + height);

	glEnd();
}

void Button::OnRelease()
{
}
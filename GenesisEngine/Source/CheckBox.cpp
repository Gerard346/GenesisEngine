#include "Application.h"
#include "FileSystem.h"
#include "GameObject.h"
#include "Transform.h"
#include "RectTransform.h"
#include "GnJSON.h"
#include "Checkbox.h"
#include "ResourceTexture.h"
#include "glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "ImGuizmo/ImGuizmo.h"
#include "Image.h"

Checkbox::Checkbox() : Component(nullptr)
{
	type = ComponentType::CHECKBOX;
	is_UI = true;

	ui_transform = _gameObject->GetRectTransform();
	GameObject* canvas = ui_transform->GetCanvas();

	check = (Image*)_gameObject->AddComponent(ComponentType::IMAGE);

	_box = new GameObject();

	_gameObject->AddChild(_box);
}

Checkbox::Checkbox(GameObject* gameObject) : Component(gameObject)
{
	type = ComponentType::CHECKBOX;
	is_UI = true;

	check = (Image*)_gameObject->AddComponent(ComponentType::IMAGE);

	ui_transform = _gameObject->GetRectTransform();
	GameObject* canvas = ui_transform->GetCanvas();

	_box = new GameObject();
	_box->SetName("Tick");
	_box->AddComponent(ComponentType::IMAGE);

	_gameObject->AddChild(_box);
}

Checkbox::~Checkbox()
{
}

void Checkbox::Update()
{
	if (checkbox_state == CHECKBOX_ON) {
		timer += App->GetLastDt();
		OnClicked();
		if (timer > check_on_delay) {
			timer = 0.0f;
			checkbox_state = CHECKBOX_HOVER;
		}
		return;
	}

	if (ui_transform->GetVisible()) {
		if (ui_transform->GetInteractive()) {
			if (App->editor->MouseOnScene()) {
				if (ui_transform->IsInsideUIElement()) {
					Hover();
					if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT) {
						OnClicked();
					}
				}
				else {
					checkbox_state = CHECKBOX_OFF;
				}

			}
		}
	}
}

void Checkbox::OnEditor()
{
}

void Checkbox::Save(GnJSONArray& save_array)
{
}

void Checkbox::Load(GnJSONObj& load_object)
{
}

void Checkbox::OnClicked()
{
	checkbox_state = CHECKBOX_ON;

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

void Checkbox::Hover()
{
	checkbox_state = CHECKBOX_HOVER;

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

void Checkbox::OnRelease()
{
}
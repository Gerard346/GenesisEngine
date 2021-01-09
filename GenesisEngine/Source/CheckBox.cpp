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

	check = (Image*)_gameObject->AddComponent(ComponentType::IMAGE);

	ui_transform = _gameObject->GetRectTransform();
	GameObject* canvas = ui_transform->GetCanvas();
}

Checkbox::Checkbox(GameObject* gameObject) : Component(gameObject)
{
	type = ComponentType::CHECKBOX;
	is_UI = true;

	check = (Image*)_gameObject->AddComponent(ComponentType::IMAGE);

	ui_transform = _gameObject->GetRectTransform();
	GameObject* canvas = ui_transform->GetCanvas();
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
						for (int i = 0; i < _gameObject->GetChildrenAmount(); i++) {
							_gameObject->GetChildAt(i)->GetRectTransform()->SetVisible();
						}
						OnClicked();
					}
				}
				else {
					checkbox_state = CHECKBOX_OFF;
				}

			}
		}
	}
	for (int i = 0; i < _gameObject->GetChildrenAmount(); i++) {
		_gameObject->GetChildAt(i)->GetRectTransform()->SetPosition(_gameObject->GetRectTransform()->GetPosition());
		_gameObject->GetChildAt(i)->GetRectTransform()->SetWidth(_gameObject->GetRectTransform()->GetWidth());
		_gameObject->GetChildAt(i)->GetRectTransform()->SetHeight(_gameObject->GetRectTransform()->GetHeight());

	}
}

void Checkbox::OnEditor()
{
}

void Checkbox::Save(GnJSONArray& save_array)
{
	GnJSONObj save_object;

	save_object.AddInt("Type", type);

	save_array.AddObject(save_object);
}

void Checkbox::Load(GnJSONObj& load_object)
{
//	_gameObject->DeleteChildren();
}

void Checkbox::OnClicked()
{
	checkbox_state = CHECKBOX_ON;
}

void Checkbox::Hover()
{
	checkbox_state = CHECKBOX_HOVER;
}

void Checkbox::OnRelease()
{
}
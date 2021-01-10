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
}

Checkbox::Checkbox(GameObject* gameObject) : Component(gameObject)
{
	type = ComponentType::CHECKBOX;
	is_UI = true;

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
		if (timer > check_on_delay) {
			timer = 0.0f;
			checkbox_state = CHECKBOX_OFF;
			if (App->in_game) {
				App->function->CallFunction(type_function, _gameObject);
			}
		}
		return;
	}

	if (is_on && _gameObject->GetRectTransform()->GetVisible()) {
		for (int i = 0; i < _gameObject->GetChildrenAmount(); i++) {
			_gameObject->GetChildAt(i)->GetRectTransform()->SetVisible(true);
		}
	}
	else {
		for (int i = 0; i < _gameObject->GetChildrenAmount(); i++) {
			_gameObject->GetChildAt(i)->GetRectTransform()->SetVisible(false);
		}
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
	if (ImGui::CollapsingHeader("CheckBox", ImGuiTreeNodeFlags_DefaultOpen))
	{
		static int item_current = 0;
		const char* list_funcionts[] = { "None", "Start Game", "VSYNC", "Close Window", "Drag canvas" };

		if (ImGui::ListBox("List of Functions avaliable", &item_current, list_funcionts, IM_ARRAYSIZE(list_funcionts), 4)) {
			if (item_current == 0) {
				type_function = TypeFunction::NONE_FUNCTION;
			}
			if (item_current == 1) {
				type_function = TypeFunction::START_GAME;
			}
			if (item_current == 2) {
				type_function = TypeFunction::ACTIVATE_VSYNC;
			}
			if (item_current == 3) {
				type_function = TypeFunction::CLOSE_WINDOW;
			}
			if (item_current == 4) {
				type_function = TypeFunction::WINDOW_DRAGGED;
			}
		}
	}
}

void Checkbox::Save(GnJSONArray& save_array)
{
	GnJSONObj save_object;

	save_object.AddInt("Type", type);

	int function_id;
	if (type_function == NONE_FUNCTION) {
		function_id = 0;
	}
	if (type_function == START_GAME) {
		function_id = 1;
	}
	if (type_function == ACTIVATE_VSYNC) {
		function_id = 2;
	}
	if (type_function == CLOSE_WINDOW) {
		function_id = 3;
	}
	if (function_id == 4) {
		type_function = TypeFunction::WINDOW_DRAGGED;
	}
	save_object.AddInt("ID function", function_id);

	save_array.AddObject(save_object);
}

void Checkbox::Load(GnJSONObj& load_object)
{
	int function_id = load_object.GetInt("ID function", 0);

	if (function_id == 0) {
		type_function = TypeFunction::NONE_FUNCTION;
	}
	if (function_id == 1) {
		type_function = TypeFunction::START_GAME;
	}
	if (function_id == 2) {
		type_function = TypeFunction::ACTIVATE_VSYNC;
	}
	if (function_id == 3) {
		type_function = TypeFunction::CLOSE_WINDOW;
	}
	if (function_id == 4) {
		type_function = TypeFunction::WINDOW_DRAGGED;
	}
}

void Checkbox::OnClicked()
{
	checkbox_state = CHECKBOX_ON;
	is_on = !is_on;
}

void Checkbox::Hover()
{
	checkbox_state = CHECKBOX_HOVER;
}

void Checkbox::OnRelease()
{
}
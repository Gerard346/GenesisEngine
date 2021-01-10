#include "Application.h"
#include "FileSystem.h"
#include "GameObject.h"
#include "Transform.h"
#include "RectTransform.h"
#include "Image.h"
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
	button = (Image*)_gameObject->AddComponent(ComponentType::IMAGE);

	ui_transform = _gameObject->GetRectTransform();
	GameObject* canvas = ui_transform->GetCanvas();

}

Button::~Button()
{
}

void Button::Update()
{
	if (button_state == BUTTON_ON) {
		timer += App->GetLastDt();
		OnClicked();
		if (timer > button_on_delay) {
			timer = 0.0f;
			button_state = BUTTON_OFF;
			if (App->in_game) {
				App->function->CallFunction(type_function, _gameObject);
			}
		}
		return;
	}

	if (ui_transform->GetVisible()) {
		if (ui_transform->GetInteractive()) {
			if (App->editor->MouseOnScene()) {
				if (App->input->GetKey(SDLK_KP_ENTER) == KEY_DOWN) {
					OnClicked();
					return;
				}
				if (ui_transform->IsInsideUIElement()) {
					Hover();
					if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN) {
						OnClicked();
					}
				}
				else {
					button_state = BUTTON_OFF;
				}

			}
		}
	}
}
void Button::OnEditor()
{
	if (ImGui::CollapsingHeader("Button", ImGuiTreeNodeFlags_DefaultOpen))
	{
		static int item_current = 0;
		const char* list_funcionts[] = { "None", "Start Game", "VSYNC", "Close Window" };

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
		}
	}
}

void Button::Save(GnJSONArray& save_array)
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
	save_object.AddInt("ID function", function_id);

	save_array.AddObject(save_object);
}

void Button::Load(GnJSONObj& load_object)
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
	
	_gameObject->RemoveComponent(button);

}

void Button::OnClicked()
{
	button_state = BUTTON_ON;

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
	button_state = BUTTON_HOVER;

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
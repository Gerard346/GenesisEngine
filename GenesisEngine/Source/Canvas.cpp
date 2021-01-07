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


	GameObject* root_scene = App->scene->GetRoot();
	gameobject->SetParent(root_scene);
	root_scene->AddChild(gameobject);
}

Canvas::~Canvas()
{
}

void Canvas::Update()
{
	if (ui_transform->GetVisible()) {
		if (ui_transform->GetInteractive()) {
			if (App->editor->MouseOnScene()) {
				if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN) {
					if (ui_transform->IsInsideUIElement()) {
						App->scene->selectedGameObject = this->GetGameObject();
					}
				}
				if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_REPEAT) {
						if (draggable) {
							MoveCanvas();
						}
				}
			}
		}
		Draw();
	}
}


void Canvas::OnEditor()
{
	if (ImGui::CollapsingHeader("Canvas", ImGuiTreeNodeFlags_DefaultOpen))
	{
		bool full_screen = ui_transform->GetFullScreen();
		if (ImGui::Checkbox("Full Screen", &full_screen)) {
			ui_transform->SetFullScreen();
		}
		ImGui::Spacing();

		if (ImGui::Checkbox("Set canvas draggable", &draggable)) {
		}
		ImGui::Spacing();

		bool interactive = ui_transform->GetInteractive();
		if (ImGui::Checkbox("Set Interactive", &interactive)) {
			ui_transform->SetInteractive();
		}
		ImGui::Spacing();
		
		bool visible = ui_transform->GetVisible();
		if (ImGui::Checkbox("Set visibility canvas", &visible)) {
			ui_transform->SetVisible();
		}

		bool set_up_at_mid = ui_transform->GetMid();
		if (ImGui::Checkbox("Set mid canvas", &set_up_at_mid)) {
			ui_transform->SetMid();
		}

		ImGui::Spacing();
	}
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


void Canvas::MoveCanvas()
{
	float3 canvas_pos = ui_transform->GetPosition();
	if (ui_transform->IsInsideUIElement()) {
		if ((canvas_pos.x + App->input->GetMouseXMotion()) < 0 ||
			(canvas_pos.x + ui_transform->GetWidth() + App->input->GetMouseXMotion()) > App->editor->image_size.x) {
			if ((canvas_pos.y - App->input->GetMouseYMotion()) < 0 ||
				(canvas_pos.y + ui_transform->GetHeight() - App->input->GetMouseYMotion()) > App->editor->image_size.y) {
			}
			else
				ui_transform->SetPosition(canvas_pos.x, canvas_pos.y - App->input->GetMouseYMotion(), 0);
			for (int i = 0; i < _gameObject->GetChildrenAmount(); i++) {
				RectTransform* child_transform = _gameObject->GetChildAt(i)->GetRectTransform();
				float3 child_pos = child_transform->GetPosition();
				if (child_transform != nullptr) {
					child_transform->SetPosition(child_pos.x, child_pos.y - App->input->GetMouseYMotion(), 0);
				}
			}
		}
		else {
			if ((canvas_pos.y - App->input->GetMouseYMotion()) < 0 || (canvas_pos.y + ui_transform->GetHeight() - App->input->GetMouseYMotion()) > App->editor->image_size.y) {
				ui_transform->SetPosition(canvas_pos.x + App->input->GetMouseXMotion(), canvas_pos.y, 0);
				for (int i = 0; i < _gameObject->GetChildrenAmount(); i++) {
					RectTransform* child_transform = _gameObject->GetChildAt(i)->GetRectTransform();
					float3 child_pos = child_transform->GetPosition();
					if (child_transform != nullptr) {
						child_transform->SetPosition(child_pos.x + App->input->GetMouseXMotion(), child_pos.y, 0);
					}
				}
			}
			else {
				ui_transform->SetPosition(canvas_pos.x + App->input->GetMouseXMotion(), canvas_pos.y - App->input->GetMouseYMotion(), 0);
				for (int i = 0; i < _gameObject->GetChildrenAmount(); i++) {
					RectTransform* child_transform = _gameObject->GetChildAt(i)->GetRectTransform();
					float3 child_pos = child_transform->GetPosition();
					if (child_transform != nullptr) {
						child_transform->SetPosition(child_pos.x + App->input->GetMouseXMotion(), child_pos.y - App->input->GetMouseYMotion(), 0);
					}
				}
			}
		}
	}
}

void Canvas::SetDraggable()
{
	this->draggable = !this->draggable;
}



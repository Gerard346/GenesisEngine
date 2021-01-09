#include "Application.h"
#include "FileSystem.h"
#include "GameObject.h"
#include "Transform.h"
#include "RectTransform.h"
#include "GnJSON.h"
#include "Image.h"
#include "ResourceTexture.h"
#include "glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "ImGuizmo/ImGuizmo.h"

Image::Image() : Component(nullptr)
{
	type = ComponentType::IMAGE;
	is_UI = true;
}

Image::Image(GameObject* gameObject) : Component(gameObject)
{
	type = ComponentType::IMAGE;
	is_UI = true;

	GameObject* canvas = ui_transform->GetCanvas();

	ui_transform = _gameObject->GetRectTransform();

	if (strcmp(gameObject->GetName(), "Tick") == 0) {
		ui_transform->SetFullScreen(false);
	}
}

Image::~Image()
{
}

void Image::Update()
{
	if (ui_transform->GetVisible()) {
		if (ui_transform->GetInteractive()) {
			if (App->editor->MouseOnScene()) {
				if (App->input->GetMouseButton(SDL_BUTTON_LEFT) == KEY_DOWN) {
					if (ui_transform->IsInsideUIElement()) {
						App->scene->selectedGameObject = this->GetGameObject();
					}
				}
			}
		}
		Draw();
	}
}

void Image::OnEditor()
{
	if (ImGui::CollapsingHeader("Image", ImGuiTreeNodeFlags_DefaultOpen))
	{
		static int item_current = 1;
		const char* list_img[] = { "Background image", "Button Image", "Menu", "Box", "Check", "Crosshair" };

		if (ImGui::ListBox("List of Textures for UI elements", &item_current, list_img, IM_ARRAYSIZE(list_img), 4)) {
			if (item_current == 0) {
				LOG("Bck img");
				SetTexture((ResourceTexture*)App->resources->RequestResource(App->resources->Find("Assets/Textures/Captura.PNG")));
				path = "Assets/Textures/Captura.PNG";
			}
			if (item_current == 1) {
				LOG("Button img");
				SetTexture((ResourceTexture*)App->resources->RequestResource(App->resources->Find("Assets/Textures/shotgun.PNG")));
				path = "Assets/Textures/shotgun.PNG";
			}
			if (item_current == 2) {
				LOG("Menu img");
			}
			if (item_current == 3) {
				LOG("Box img");
			}
			if (item_current == 4) {
				LOG("Check img");
			}
			if (item_current == 5) {
				LOG("Crosshair img");
			}
		}
		bool full_screen = ui_transform->GetFullScreen();
		if (ImGui::Checkbox("Full Screen", &full_screen)) {
			ui_transform->SetFullScreen(full_screen);
		}
		ImGui::Spacing();

		bool interactive = ui_transform->GetInteractive();
		if (ImGui::Checkbox("Set Interactive", &interactive)) {
			ui_transform->SetInteractive();
		}
		ImGui::Spacing();

		bool visible = ui_transform->GetVisible();
		if (ImGui::Checkbox("Set visibility", &visible)) {
			ui_transform->SetVisible();
		}

		bool set_up_at_mid = ui_transform->GetMid();
		if (ImGui::Checkbox("Set mid image on canvas", &set_up_at_mid)) {
			ui_transform->SetMid();
		}

		bool lock_ratio = ui_transform->GetAspectRatio();
		if (ImGui::Checkbox("Set lock aspect ratio image", &lock_ratio)) {
			ui_transform->SetLockAspectRatio();
		}

		ImGui::Spacing();
	}
}

void Image::Draw()
{
	if (ui_transform != nullptr) {
		RectTransform* ui_transform = _gameObject->GetRectTransform();
		float3 position;

		float width = _gameObject->GetRectTransform()->GetWidth();
		float height = _gameObject->GetRectTransform()->GetHeight();

		position = ui_transform->GetPosition();

		BindTexture();

		glBegin(GL_QUADS);
		_diffuseTexture;

		glVertex2f(position.x, position.y);
		glTexCoord2f(1, 1);
		glVertex2f(position.x + width, position.y);
		glTexCoord2f(1, 0);
		glVertex2f(position.x + width, position.y + height);
		glTexCoord2f(0, 0);
		glVertex2f(position.x, position.y + height);
		glTexCoord2f(0, 1);

		glEnd();
	}
}

void Image::Save(GnJSONArray& save_array)
{
	GnJSONObj save_object;

	save_object.AddInt("Type", type);

	if (_diffuseTexture != nullptr) {
		save_object.AddString("String", path);
	}

	save_array.AddObject(save_object);
}

void Image::Load(GnJSONObj& load_object)
{
	path = (char*)load_object.GetString("String", "No path");
	if (path != nullptr) {
		loading = true;
		SetTexture((ResourceTexture*)App->resources->RequestResource(App->resources->Find(path)));
	}
	loading = false;
}

void Image::ChangeImage(uint new_image)
{
	_diffuseTexture->SetUID(new_image);
}

uint Image::GetImageID() const
{
	if (_diffuseTexture != nullptr) {
		return _diffuseTexture->GetID();
	}
	else {
		return -1;
	}
}


void Image::BindTexture()
{
	if (!App->resources->Exists(_resourceUID))
	{
		_resourceUID = 0u;
	}
	if (_diffuseTexture != nullptr)
		_diffuseTexture->BindTexture();
}

void Image::SetTexture(ResourceTexture* texture)
{
	if (texture != nullptr)
	{
		if (_diffuseTexture != nullptr)
			App->resources->ReleaseResource(_diffuseTexture->GetUID());

		_diffuseTexture = texture;
		
		if (!loading) {
			float img_w = texture->GeWidth();
			float img_h = texture->GetHeight();
			float aspect = img_w / img_h;

			ui_transform->SetWidth(img_w);
			ui_transform->SetHeight(img_h);
			ui_transform->SetAspectRatio(aspect);
		}
	}
}

ResourceTexture* Image::GetDiffuseTexture()
{
	return _diffuseTexture;
}
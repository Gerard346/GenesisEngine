#include "Application.h"
#include "FileSystem.h"
#include "GameObject.h"
#include "Transform.h"
#include "RectTransform.h"
#include "GnJSON.h"
#include "Image.h"
#include "ResourceTexture.h"

Image::Image() : Component(nullptr)
{
	type = ComponentType::IMAGE;
	is_UI = true;

	

}

Image::Image(GameObject* gameObject) : Component(gameObject)
{
	type = ComponentType::IMAGE;
	is_UI = true;

	gameObject->AddComponent(ComponentType::RECT_TRANSFORM);
	ui_transform = _gameObject->GetRectTransform();
	GameObject* canvas = ui_transform->GetCanvas();

	if (canvas == nullptr) {
		App->scene->AddGameObject(new GameObject(ComponentType::CANVAS_UI));
	}
	canvas = ui_transform->GetCanvas();
	canvas->AddChild(gameObject);
	ui_transform->SetCanvas(canvas);
}

Image::~Image()
{
}

void Image::Update()
{
}

void Image::OnEditor()
{
	if (ImGui::CollapsingHeader("Image", ImGuiTreeNodeFlags_DefaultOpen))
	{
		const char* items[] = { "Background image", "Button Image", "Menu", "Box", "Check", "Crosshair" };
		static int item_current = 1;
		if (ImGui::ListBox("listbox\n(single select)", &item_current, items, IM_ARRAYSIZE(items), 4)) {
			LOG("%d", item_current);
		}
	}
	ImGui::Spacing();
}

void Image::Save(GnJSONArray& save_array)
{
}

void Image::Load(GnJSONObj& load_object)
{
}

void Image::ChangeImage(uint new_image)
{
	image->SetUID(new_image);
}

uint Image::GetImageID() const
{
	if (image != nullptr) {
		return image->GetID();
	}
	else {
		return -1;
	}
}

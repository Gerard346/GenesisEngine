#include "Application.h"
#include "ModuleWindow.h"
#include "RectTransform.h"

RectTransform::RectTransform()
{
	type = ComponentType::RECT_TRANSFORM;
}

RectTransform::RectTransform(GameObject* gameobject)
{
	type = ComponentType::RECT_TRANSFORM;

}

RectTransform::~RectTransform()
{
}

void RectTransform::Update()
{
	if (full_screen) {
		width = App->window->width;
		height = App->window->height;
	}
}

void RectTransform::OnEditor()
{
}

void RectTransform::SetTransform(float3 new_scale, Quat new_rotation, float3 new_position)
{
	scale = new_scale;
	rotation = new_rotation;
	position = new_position;
}

void RectTransform::SetWidth(float new_width)
{
	width = new_width;
}

void RectTransform::SetHeight(float new_height)
{
	height = new_height;
}

float3 RectTransform::GetScale() const
{
	return scale;
}

float2 RectTransform::GetPivot() const
{
	return pivot;
}

Quat RectTransform::GetRotation() const
{
	return rotation;
}

float RectTransform::GetWidth() const
{
	return width;
}

float RectTransform::GetHeight() const
{
	return height;
}

void RectTransform::Save(GnJSONArray& save_array)
{
}

void RectTransform::Load(GnJSONObj& load_object)
{
}
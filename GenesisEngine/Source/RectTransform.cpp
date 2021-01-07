#include "Application.h"
#include "ModuleWindow.h"
#include "RectTransform.h"
#include "GameObject.h"
#include "ImGui/imgui.h"

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
		width = App->editor->image_size.x;
		height = App->editor->image_size.y;
		_position.x = 0.0f + pivot.x;
		_position.y = 0.0f + pivot.y;
	}
}

void RectTransform::OnEditor()
{
	if (ImGui::CollapsingHeader("Rect_Transform", ImGuiTreeNodeFlags_DefaultOpen))
	{
		float position4f[2] = { _position.x, _position.y };
		if (ImGui::DragFloat2("Position", position4f, 0.1f, -10000.0f, 10000.0f))
		{
			SetPosition(position4f[0], position4f[1], 0);
			UpdateGlobalTransform();
			_gameObject->UpdateChildrenRectTransforms();
		}

		if (ImGui::DragFloat("Width", &width, 1))
			SetWidth(width);

		if (ImGui::DragFloat("Heigth", &height, 1))
			SetHeight(height);

		ImGui::Spacing();

		if (ImGui::Button("Reset"))
			Reset();

		ImGui::Spacing();
	}
}

void RectTransform::SetWidth(float new_width)
{
	width = new_width;
}

void RectTransform::SetHeight(float new_height)
{
	height = new_height;
}

void RectTransform::SetPivot(float2 new_pivot)
{
	pivot = new_pivot;
}

bool RectTransform::IsInsideUIElement()
{
	float position_x = _position.x;
	float scene_pos_x = App->editor->mouseScenePosition.x;
	float position_xw = _position.x + GetWidth();

	if (_position.x < App->editor->mouseScenePosition.x) {
		if (App->editor->mouseScenePosition.x < _position.x + GetWidth()) {
			if (_position.y < App->editor->mouseScenePosition.y < _position.y + GetHeight()) {
				return true;
			}
			else
				return false;
		}
	}
	return false;
}

float2 RectTransform::GetPivot() const
{
	return pivot;
}

float RectTransform::GetWidth() const
{
	return width;
}

float RectTransform::GetHeight() const
{
	return height;
}

void RectTransform::Set(float4x4 g_transform)
{
	_localTransform = g_transform;
}

float4x4 RectTransform::GetLocalTransform()
{
	return _localTransform;
}

float4x4 RectTransform::GetGlobalTransform()
{
	return _globalTransform;
}

void RectTransform::SetGlobalTransform(float4x4 newTransform)
{
	_globalTransform = newTransform;
	float4x4 inverseParentGlobal = _parentGlobalTransform;
	inverseParentGlobal.Inverse();
	_localTransform = inverseParentGlobal * _globalTransform;
	UpdateTRS();
	_gameObject->UpdateChildrenRectTransforms();
}

void RectTransform::UpdateLocalTransform()
{
	_localTransform = float4x4::FromTRS(_position, _rotation, _scale);
}

void RectTransform::UpdateTRS()
{
	_localTransform.Decompose(_position, _rotation, _scale);
}

void RectTransform::UpdateGlobalTransform()
{
	UpdateLocalTransform();
	_globalTransform = _parentGlobalTransform * _localTransform;
}

void RectTransform::UpdateGlobalTransform(float4x4 parentGlobalTransform)
{
	UpdateLocalTransform();
	_parentGlobalTransform = parentGlobalTransform;
	_globalTransform = _parentGlobalTransform * _localTransform;
}

void RectTransform::ChangeParentTransform(float4x4 newParentGlobalTransform)
{
	_parentGlobalTransform = newParentGlobalTransform;
	newParentGlobalTransform.Inverse();
	_localTransform = newParentGlobalTransform * _globalTransform;
	UpdateTRS();
	_globalTransform = _parentGlobalTransform * _localTransform;
}

void RectTransform::Reset()
{
	_position = float3::zero;
	_scale = float3::one;

	UpdateGlobalTransform();
	_gameObject->UpdateChildrenRectTransforms();

}

void RectTransform::SetPosition(float x, float y, float z)
{
	_position.x = x;
	_position.y = y;
	_position.z = z;

	UpdateLocalTransform();
}

void RectTransform::SetPosition(float3 new_position)
{
	_position = new_position;
	UpdateGlobalTransform();
}

float3 RectTransform::GetPosition()
{
	return _position;
}

void RectTransform::Save(GnJSONArray& save_array)
{
}

void RectTransform::Load(GnJSONObj& load_object)
{
}
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
	/*if (full_screen) {
		width = App->window->width;
		height = App->window->height;
	}*/
}

void RectTransform::OnEditor()
{
	if (ImGui::CollapsingHeader("Rect_Transform", ImGuiTreeNodeFlags_DefaultOpen))
	{
		float position4f[4] = { _position.x, _position.y, _position.z, 1.0f };
		if (ImGui::DragFloat3("Position", position4f, 0.1f, -10000.0f, 10000.0f))
		{
			SetPosition(position4f[0], position4f[1], position4f[2]);
			UpdateGlobalTransform();
			_gameObject->UpdateChildrenRectTransforms();
		}

		float rotation4f[4] = { _eulerRotation.x, _eulerRotation.y, _eulerRotation.z, 1.0f };
		if (ImGui::DragFloat3("Rotation", rotation4f, 0.1f, -360.0f, 360.0f))
		{
			SetRotation(rotation4f[0], rotation4f[1], rotation4f[2]);
			UpdateGlobalTransform();
			_gameObject->UpdateChildrenRectTransforms();
		}

		float scale4f[4] = { _scale.x, _scale.y, _scale.z, 1.0f };
		if (ImGui::DragFloat3("Scale", scale4f, 0.01f, -10000.0f, 10000.0f))
		{
			SetScale(scale4f[0], scale4f[1], scale4f[2]);
			UpdateGlobalTransform();
			_gameObject->UpdateChildrenRectTransforms();
		};

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
	UpdateEulerRotation();
}

void RectTransform::UpdateTRS()
{
	_localTransform.Decompose(_position, _rotation, _scale);
	UpdateEulerRotation();
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
	_rotation = Quat::identity;
	_scale = float3::one;
	_eulerRotation = float3::zero;

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


//Set rotation from Euler angles
void RectTransform::SetRotation(float x, float y, float z)
{
	_eulerRotation = float3(x, y, z);
	_rotation = Quat::FromEulerXYZ(x * DEGTORAD, y * DEGTORAD, z * DEGTORAD);
	UpdateGlobalTransform();
}

void RectTransform::SetRotation(Quat new_rotation)
{
	_rotation = new_rotation;
	_eulerRotation = _rotation.ToEulerXYZ() * RADTODEG;

	UpdateGlobalTransform();
}

void RectTransform::SetRotation(float x, float y, float z, float w)
{
	_rotation.x = x;
	_rotation.y = y;
	_rotation.z = z;
	_rotation.w = w;

	UpdateGlobalTransform();
}

Quat RectTransform::GetRotation()
{
	return _rotation;
}

void RectTransform::UpdateEulerRotation()
{
	_eulerRotation = _rotation.ToEulerXYZ();
	_eulerRotation *= RADTODEG;
}

void RectTransform::SetScale(float x, float y, float z)
{
	_scale.x = x;
	_scale.y = y;
	_scale.z = z;

	UpdateGlobalTransform();
}

void RectTransform::SetScale(float3 new_scale)
{
	_scale = new_scale;

	UpdateGlobalTransform();
}

void RectTransform::SetProportionalScale(float multiplier)
{
	_scale.x = _scale.y = _scale.z = multiplier;

	UpdateGlobalTransform();
}

float3 RectTransform::GetScale()
{
	return _scale;
}

void RectTransform::Save(GnJSONArray& save_array)
{
}

void RectTransform::Load(GnJSONObj& load_object)
{
}

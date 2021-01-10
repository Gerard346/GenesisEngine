#include "Application.h"
#include "ModuleWindow.h"
#include "RectTransform.h"
#include "GameObject.h"
#include "ImGui/imgui.h"
#include "GnJSON.h"

RectTransform::RectTransform() : Component()
{
	type = ComponentType::RECT_TRANSFORM;
}

RectTransform::RectTransform(float3 position, Quat rotation, float3 scale)
{
	type = ComponentType::RECT_TRANSFORM;

	_position = position;
	_rotation = rotation;
	_eulerRotation = rotation.ToEulerXYZ();
	_eulerRotation *= RADTODEG;
	_scale = scale;

	_localTransform = float4x4::FromTRS(_position, _rotation, _scale);
	_globalTransform = _localTransform;
	_parentGlobalTransform = float4x4::identity;
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
	if (mid) {
		SetAtMiddle();
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

		if (ImGui::DragFloat("Width", &width, 1)) {
			SetWidth(width);
			if (lock_aspect_ratio) {
				SetHeight(width/aspect_ratio);
			}
		}

		if (ImGui::DragFloat("Heigth", &height, 1)) {
			SetHeight(height);
			if (lock_aspect_ratio) {
				SetWidth(height * aspect_ratio);
			}
		}

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
	float position_y = App->editor->image_size.y - _position.y;

	if (_position.x < App->editor->mouseScenePosition.x) {
		if (App->editor->mouseScenePosition.x < _position.x + GetWidth()) {
			if (position_y > App->editor->mouseScenePosition.y) {
				if (position_y - GetHeight() < App->editor->mouseScenePosition.y) {
					return true;
				}
			}
		}
		else {
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
	float diff_x = x - _position.x;
	float diff_y = y - _position.y;
	float diff_z = z - _position.z;

	_position.x = x;
	_position.y = y;
	_position.z = z;

	for (int i = 0; i < _gameObject->GetChildrenAmount(); i++) {
		float3 pos_child = _gameObject->GetChildAt(i)->GetRectTransform()->GetPosition();
		_gameObject->GetChildAt(i)->GetRectTransform()->SetPosition(pos_child.x + diff_x, pos_child.y + diff_y, pos_child.z + diff_z);
	}
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

void RectTransform::SetVisible()
{
	for (int i = 0; i < _gameObject->GetChildrenAmount(); i++) {
		_gameObject->GetChildAt(i)->GetRectTransform()->SetVisible();
	}
	visible = !visible;
}

void RectTransform::SetVisible(bool state)
{
	for (int i = 0; i < _gameObject->GetChildrenAmount(); i++) {
		_gameObject->GetChildAt(i)->GetRectTransform()->SetVisible(state);
	}
	visible = state;
}

void RectTransform::Save(GnJSONArray& save_array)
{
	GnJSONObj save_object;

	save_object.AddInt("Type", type);

	save_object.AddFloat3("UI Position", _position);

	save_object.AddQuaternion("UI Rotation", _rotation);

	save_object.AddFloat3("UI Scale", _scale);

	save_object.AddFloat3("UI Euler", _eulerRotation);

	save_object.AddFloat("Width", width);

	save_object.AddFloat("Height", height);

	save_object.AddFloat("Aspect Ratio", aspect_ratio);

	save_object.AddBool("Full Screen", full_screen);

	save_object.AddBool("Interactive", interactive);

	save_object.AddBool("Visible", visible);

	save_object.AddBool("Mid", mid);

	save_object.AddBool("Lock Ratio", lock_aspect_ratio);


	save_array.AddObject(save_object);
}

void RectTransform::Load(GnJSONObj& load_object)
{
	_position = load_object.GetFloat3("UI Position");

	_rotation = load_object.GetQuaternion("UI Rotation");
	
	_scale = load_object.GetFloat3("UI Scale");

	_eulerRotation = load_object.GetFloat3("UI Euler");

	width = load_object.GetFloat("Width");

	height = load_object.GetFloat("Height");

	aspect_ratio = load_object.GetFloat("Aspect Ratio");

	full_screen = load_object.GetBool("Full Screen");

	interactive = load_object.GetBool("Interactive");

	visible = load_object.GetBool("Visible");

	mid = load_object.GetBool("Mid");

	lock_aspect_ratio = load_object.GetBool("Lock Ratio");

	UpdateGlobalTransform();
}

void RectTransform::SetAtMiddle()
{
	if (canvas_parent == nullptr) {
		float mid_x = App->editor->image_size.x / 2;
		float mid_y = App->editor->image_size.y / 2;

		SetPosition(mid_x - width / 2, mid_y - height / 2, 0);
	}
	else {
		GameObject* canvas_obj = GetCanvas();
		RectTransform* canvas_transform = canvas_obj->GetRectTransform();
		float3 canvas_pos = canvas_transform->GetPosition();
		float mid_x = canvas_pos.x + (canvas_transform->GetWidth() / 2);
		float mid_y = canvas_pos.y + (canvas_transform->GetHeight() / 2);

		SetPosition(mid_x - width / 2, mid_y - height / 2, 0);
	}
}

void RectTransform::SetAspectRatio(float new_aspect_ratio)
{
	aspect_ratio = new_aspect_ratio;
}

GameObject* RectTransform::GetCanvas()
{
	GameObject* ret = nullptr;

	std::vector<GameObject*> sceneGameObjects = App->scene->GetAllGameObjects();

	for (size_t i = 0; i < sceneGameObjects.size(); i++)
	{
		Canvas* ret_canvas = ((Canvas*)sceneGameObjects.at(i)->GetComponent(ComponentType::CANVAS_UI));

		if (ret_canvas != nullptr) {
			return sceneGameObjects[i];
		}
	}
}

void RectTransform::SetCanvas(GameObject* _canvas)
{
	canvas_parent = (Canvas*)_canvas->GetComponent(ComponentType::CANVAS_UI);
	_gameObject->SetParent(_canvas);
}
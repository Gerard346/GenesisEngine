#ifndef _RECTTRANSFORM_H_
#define _RECTTRANSFORM_H_

#include "Component.h"
#include "UI.h"
#include "MathGeoLib/include/MathGeoLib.h"

class Canvas;

class RectTransform : public Component {
public:
	RectTransform();
	RectTransform(float3 position, Quat rotation, float3 scale);
	~RectTransform();

	void Update() override;
	void OnEditor() override;

	void SetTransform(float3 new_scale, Quat new_rotation, float3 new_position);
	void SetWidth(float new_width);
	void SetHeight(float new_height);
	void SetRotation(float3 new_rotation);
	void SetPostion(float3 new_position);
	void SetPivot(float2 new_pivot);
	void SetFullScreen(bool new_state) { full_screen = new_state; }
	bool IsInsideUIElement();

	float3 GetScale() const;
	float2 GetPivot() const;
	Quat GetRotation() const;

	float GetWidth() const;
	float GetHeight() const;

	void Reset();

	void Set(float4x4 transform);

	float4x4 GetLocalTransform();
	float4x4 GetGlobalTransform();
	void SetGlobalTransform(float4x4 newTransform);

	void UpdateLocalTransform();
	void UpdateTRS();
	void UpdateGlobalTransform();
	void UpdateGlobalTransform(float4x4 parentGlobalTransform);
	void ChangeParentTransform(float4x4 newParentGlobalTransform);

	void SetPosition(float x, float y, float z);
	void SetPosition(float3 new_position);
	float3 GetPosition();

	bool GetFullScreen() { return full_screen; }

	bool GetInteractive() { return interactive; }
	void SetInteractive() { interactive = !interactive; }

	bool GetDraggable() { return draggable; }
	void SetDraggable() { draggable = !draggable; }

	bool GetVisible() { return visible; }
	void SetVisible();
	void SetVisible(bool state);


	void Save(GnJSONArray& save_array) override;
	void Load(GnJSONObj& load_object) override;

	bool GetMid() { return mid; }
	void SetMid() {
		SetAtMiddle();
		mid = !mid;
	}

	void SetAtMiddle();

	void SetLockAspectRatio() { lock_aspect_ratio = !lock_aspect_ratio; }
	bool GetAspectRatio() { return lock_aspect_ratio; }
	void SetAspectRatio(float new_aspect_ratio);
	GameObject* GetCanvas();
	void SetCanvas(GameObject* _canvas);

public:

private:
	float4x4 _localTransform = float4x4::identity;
	float4x4 _globalTransform = float4x4::identity;
	float4x4 _parentGlobalTransform = float4x4::identity;

	float width = 100.0f;
	float height = 100.0f;

	float2 pivot = { 0.0, 0.0f };

	float3 _position = { 0.0f, 0.0f, 0.0f };
	Quat _rotation;
	float3 _scale = { 0.0f, 0.0f, 0.0f };
	float3 _eulerRotation = { 0.0f, 0.0f,0.0f };
	float aspect_ratio = 0.0f;

	Canvas* canvas_parent = nullptr;

	bool update = false;
	bool full_screen = true;
	bool interactive = true;
	bool visible = true;
	bool mid = false;
	bool draggable = false;

	bool lock_aspect_ratio = false;

};
#endif
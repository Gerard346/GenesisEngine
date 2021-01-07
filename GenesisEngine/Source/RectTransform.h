#pragma once

#include "Component.h"
#include "UI.h"
#include "MathGeoLib/include/MathGeoLib.h"

class RectTransform : public Component {
public:
	RectTransform();
	RectTransform(GameObject* gameobject);
	~RectTransform();

	void Update() override;
	void OnEditor() override;

	void SetTransform(float3 new_scale, Quat new_rotation, float3 new_position);
	void SetWidth(float new_width);
	void SetHeight(float new_height);

	float3 GetScale() const;
	float2 GetPivot() const;
	Quat GetRotation() const;

	float GetWidth() const;
	float GetHeight() const;

	bool GetFullScreen() { return full_screen; }

	void Save(GnJSONArray& save_array) override;
	void Load(GnJSONObj& load_object) override;

public:

private:
	float4x4 _transformMatrix = float4x4::identity;
	float4x4 _transformMatrix_transposed = float4x4::identity;

	float4x4 _globalTransform = float4x4::identity;
	float4x4 _globalTransform_identity = float4x4::identity;

	float width = 100.0f;
	float height = 100.0f;

	float2 pivot = { 0.5, 0.5f };
	float3 position = float3::zero;
	float3 scale = float3::zero;
	Quat rotation = Quat::identity;

	bool update = false;
	bool full_screen = true;
};

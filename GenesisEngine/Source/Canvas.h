#pragma once

#include "Globals.h"
#include "Component.h"
#include <list>
#include "MathGeoLib/include/Math/float2.h"

class GameObject;
class RectTransform;

class Canvas : public Component {
public:
	Canvas();
	Canvas(GameObject* gameobject);
	~Canvas();

	void Update() override;
	void OnEditor() override;

	void Save(GnJSONArray& save_array) override;
	void Load(GnJSONObj& load_object) override;

	void Draw();
	bool IsInsideCanvas();
	void MoveCanvas();

	void SetDraggable();

private:
	bool draggable = false;
	RectTransform* ui_transform = nullptr;
	float2 pivot = { 0.0f, 0.0f };
};

#pragma once

#include "Globals.h"
#include "Component.h"
#include <list>
#include "MathGeoLib/include/Math/float2.h"

class GameObject;
class RectTransform;

struct DataCanvas {
	float2 size;
	float2 position;
};

class Canvas : public Component {
public:
	Canvas();
	Canvas(GameObject* gameobject);
	~Canvas();

	void Update() override;
	void OnEditor() override;

	void Save(GnJSONArray& save_array) override;
	void Load(GnJSONObj& load_object) override;

	DataCanvas GetDataCanvas();

private:
	DataCanvas canvas_data;

	uint width = 0;
	uint height = 0;
	
	//RectTransform* ui_transform = nullptr;
};
#pragma once
#include "Globals.h"
#include "Component.h"

class GameObject;
class ResourceTexture;
class Image;
class RectTransform;

enum State_CheckBox {
	CHECKBOX_OFF,
	CHECKBOX_ON,
	CHECKBOX_HOVER
};

class Checkbox : public Component {
public:
	Checkbox();
	Checkbox(GameObject* gameObject);
	~Checkbox();

	virtual void Update() override;
	void OnEditor() override;

	void Save(GnJSONArray& save_array) override;
	void Load(GnJSONObj& load_object) override;

	void OnClicked();
	void Hover();
	void OnRelease();

private:
	Image* check = nullptr;
	RectTransform* ui_transform = nullptr;
	GameObject* _box = nullptr;

	float check_on_delay = 0.3f;
	float timer = 0.0f;

	State_CheckBox checkbox_state = CHECKBOX_OFF;
};
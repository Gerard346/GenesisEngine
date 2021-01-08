#pragma once
#include "Globals.h"
#include "Component.h"

class GameObject;
class ResourceTexture;
class Image;

enum State_Button {
	BUTTON_OFF,
	BUTTON_ON,
	BUTTON_HOVER
};

class Button : public Component {
public:
	Button();
	Button(GameObject* gameObject);
	~Button();

	virtual void Update() override;
	void OnEditor() override;

	void Save(GnJSONArray& save_array) override;
	void Load(GnJSONObj& load_object) override;

	void OnClicked();
	void Hover();
	void OnRelease();

private:
	Image* button = nullptr;
	RectTransform* ui_transform = nullptr;

	float button_on_delay =0.3f;
	float timer = 0.0f;

	State_Button button_state = BUTTON_OFF;
};
#pragma once
#include "Globals.h"
#include "Component.h"
#include "Functions.h"

class GameObject;
class ResourceTexture;
class Image;
class RectTransform;

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
	void Draw();
	void OnEditor() override;

	void Save(GnJSONArray& save_array) override;
	void Load(GnJSONObj& load_object) override;

	void OnClicked();
	void Hover();
	void OnRelease();

	State_Button button_state = BUTTON_OFF;

private:
	Image* button = nullptr;
	RectTransform* ui_transform = nullptr;
	TypeFunction type_function = TypeFunction::NONE_FUNCTION;

	float button_on_delay =0.5f;
	float timer = 0.0f;

};
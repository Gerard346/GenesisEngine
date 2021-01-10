#ifndef _CHECKBOX_H_
#define _CHECKBOX_H_
#include "Globals.h"
#include "Component.h"
#include "Functions.h"

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

	void IsOn() { is_on = !is_on; }
private:
	Image* check = nullptr;
	RectTransform* ui_transform = nullptr;
	GameObject* _box = nullptr;

	float check_on_delay = 0.3f;
	float timer = 0.0f;

	bool is_on = false;
	TypeFunction type_function = TypeFunction::NONE_FUNCTION;

	State_CheckBox checkbox_state = CHECKBOX_OFF;
};
#endif
#pragma once
#include "Globals.h"
#include "Component.h"

class GameObject;
class ResourceTexture;
class Image;

class Button : public Component {
public:
	Button();
	Button(GameObject* gameObject);
	~Button();

	void OnEditor() override;

	void Save(GnJSONArray& save_array) override;
	void Load(GnJSONObj& load_object) override;

	void OnClicked();
	void Idle();
	void Hover();
	void OnRelease();

private:
	Image* button = nullptr;
	RectTransform* ui_transform = nullptr;
};
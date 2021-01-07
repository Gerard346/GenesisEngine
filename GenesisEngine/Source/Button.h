#pragma once
#include "Globals.h"
#include "Component.h"
#include "Image.h"

class GameObject;
class ResourceTexture;

class Button : public Component {
public:
	Button();
	Button(GameObject* gameObject);
	~Button();

	void Save(GnJSONArray& save_array) override;
	void Load(GnJSONObj& load_object) override;

	void OnClicked();
	void Idle();
	void Hover();
	void OnRelease();

private:
	Image* button = nullptr;
	ResourceTexture* clicked = nullptr;
	ResourceTexture* hover = nullptr;

};
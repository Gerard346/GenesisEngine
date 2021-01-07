#pragma once

#include "Globals.h"
#include "Component.h"

class GameObject;
class RectTransform;
class ResourceTexture;
class Canvas;

class Image : public Component {
public:
	Image();
	Image(GameObject* gameObject);
	~Image();

	virtual void Update() override;
	void OnEditor() override;

	void Save(GnJSONArray& save_array) override;
	void Load(GnJSONObj& load_object) override;

	ResourceTexture* image = nullptr;

	void ChangeImage(uint new_image);
	uint GetImageID() const;

private:
	RectTransform* ui_transform = nullptr;
};
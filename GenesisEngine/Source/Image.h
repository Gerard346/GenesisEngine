#ifndef _IMAGE_H_
#define _IMAGE_H_

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

	void Draw();

	void Save(GnJSONArray& save_array) override;
	void Load(GnJSONObj& load_object) override;

	void Print(float alpha);

	void ChangeImage(uint new_image);
	uint GetImageID() const;

	void BindTexture();
	void SetTexture(ResourceTexture* texture);
	ResourceTexture* GetDiffuseTexture();

private:
	RectTransform* ui_transform = nullptr;
	ResourceTexture* _diffuseTexture = nullptr;
	char* path = nullptr;
	bool loading = false;
	float alpha = 0;
};
#endif
#pragma once
/*
#include "Globals.h"
#include "Component.h"

class GameObject;
class RectTransform;
class Canvas;
class Image;

class Text : public Component {
public:
	Text();
	Text(GameObject* gameObject);
	~Text();

	virtual void Update() override;
	void OnEditor() override;

	void Draw();

	void Save(GnJSONArray& save_array) override;
	void Load(GnJSONObj& load_object) override;

	void SetUpText();

	void RenderText(std::string text, float scale);

private:
	RectTransform* ui_transform = nullptr;
	Image* text_img = nullptr;
	uint VAO, VBO;
};*/
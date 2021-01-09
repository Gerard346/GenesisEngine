#pragma once
#include "Globals.h"
#include "Component.h"
#include "FontImporter.h"

class GameObject;
class RectTransform;
class Canvas;

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

	freetype_mod::font_data our_font;

private:
	RectTransform* ui_transform = nullptr;
};
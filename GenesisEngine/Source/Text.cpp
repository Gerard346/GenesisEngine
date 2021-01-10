#include "Application.h"
#include "Text.h"
#include "GameObject.h"
#include "RectTransform.h"
#include "GnJSON.h"
#include "FontImporter.h"


Text::Text() : Component(nullptr)
{
	type = ComponentType::TEXT;
	is_UI = true;

    ui_transform = _gameObject->GetRectTransform();
	our_font.init("Assets/Fonts/Test.ttf", 32);

}

Text::Text(GameObject* gameObject) : Component(gameObject)
{
	type = ComponentType::TEXT;
	is_UI = true;

    ui_transform = _gameObject->GetRectTransform();
	our_font.init("Assets/Fonts/Test.ttf", 32);

	label = "hola";
}

Text::~Text()
{
}

void Text::Update()
{
	if (ui_transform->GetVisible()) {
		if (ui_transform->GetInteractive()) {
			if (App->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_DOWN) {
				if (label.length() > 0) {
					label.pop_back();
				}
			}
		}
		freetype_mod::Print(our_font, label.c_str(), ui_transform->GetPosition());
	}
}

void Text::OnEditor()
{
}

void Text::Draw()
{
    
}

void Text::Save(GnJSONArray& save_array)
{
	GnJSONObj save_object;

	save_object.AddInt("Type", type);

	if (!label.empty()) {
		save_object.AddString("StringText", label.c_str());
	}

	save_array.AddObject(save_object);
}

void Text::Load(GnJSONObj& load_object)
{
	label = (char*)load_object.GetString("StringText", "No path");
	
}

void Text::AddChar(char* str)
{
	if (App->in_game) {
		label.append(str);
	}
}


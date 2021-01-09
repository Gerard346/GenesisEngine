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
	if (opened) {
		SDL_Event event;
		SDL_StartTextInput();
		SDL_WaitEvent(&event);
		if (SDL_PollEvent(&event)) {
			switch (event.type) {
			case SDL_TEXTINPUT:
				label.append(event.text.text);
				break;

			case SDL_QUIT:
				opened = false;
				break;
			}
		}
		freetype_mod::Print(our_font, label.c_str(), float3(0.0f, 0.0f, 0.0f));
		if (App->scene->selectedGameObject == _gameObject) {
			if (App->input->GetKey(SDL_SCANCODE_BACKSPACE) == KEY_REPEAT) {
				if (label.length() > 0) {
					label.pop_back();
				}
			}

		}
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
}

void Text::Load(GnJSONObj& load_object)
{
}


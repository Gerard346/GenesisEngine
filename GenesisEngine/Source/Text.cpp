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

}

Text::~Text()
{
}

void Text::Update()
{
	freetype_mod::Print(our_font, "Gerard",  float3(0.0f, 0.0f, 0.0f));

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


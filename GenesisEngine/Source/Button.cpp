#include "Application.h"
#include "FileSystem.h"
#include "GameObject.h"
#include "Transform.h"
#include "RectTransform.h"
#include "GnJSON.h"
#include "Button.h"
#include "ResourceTexture.h"
#include "glew/include/glew.h"
#include "SDL\include\SDL_opengl.h"
#include <gl/GL.h>
#include <gl/GLU.h>
#include "ImGuizmo/ImGuizmo.h"

Button::Button() : Component(nullptr)
{
	type = ComponentType::BUTTON;
	is_UI = true;
}

Button::Button(GameObject* gameObject) : Component(gameObject)
{
	type = ComponentType::BUTTON;
	is_UI = true;

	ui_transform = _gameObject->GetRectTransform();
	GameObject* canvas = ui_transform->GetCanvas();

	_gameObject->AddComponent(ComponentType::IMAGE);
}

Button::~Button()
{
}

void Button::OnEditor()
{
}

void Button::Save(GnJSONArray& save_array)
{
}

void Button::Load(GnJSONObj& load_object)
{
}

void Button::OnClicked()
{
}

void Button::Idle()
{
}

void Button::Hover()
{
}

void Button::OnRelease()
{
}
#include "ImGui/imgui.h"
#include "FileSystem.h"
#include "GnJSON.h"
#include "GameObject.h"
#include "Application.h"
#include "WindowAssets.h"
#include "Canvas.h"
#include "RectTransform.h"

Canvas::Canvas()
{
	type = ComponentType::CANVAS;
	is_UI = true;
}

Canvas::Canvas(GameObject* gameobject)
{
	type = ComponentType::CANVAS;
	is_UI = true;
}

Canvas::~Canvas()
{
}

void Canvas::Update()
{

}

void Canvas::OnEditor()
{
}

void Canvas::Save(GnJSONArray& save_array)
{
}

void Canvas::Load(GnJSONObj& load_object)
{
}

DataCanvas Canvas::GetDataCanvas()
{
	return canvas_data;
}
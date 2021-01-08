#include "Globals.h"
#include "Application.h"
#include "Functions.h"
#include "GameObject.h"
#include "RectTransform.h"
#include "ModuleRenderer3D.h"

Functions::Functions(bool start_enabled) :Module(start_enabled)
{
}

Functions::~Functions()
{
}

bool Functions::Init()
{
	return true;
}

bool Functions::CleanUp()
{
	return true;
}

update_status Functions::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status Functions::Update(float dt)
{
	return UPDATE_CONTINUE;
}

update_status Functions::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

void Functions::CallFunction(TypeFunction type, GameObject* obj)
{
	switch (type) {
	case TypeFunction::NONE_FUNCTION:
		break;

	case TypeFunction::START_GAME:
		App->editor->SetSceneOperation(SceneOperation::LOAD);
		break;

	case TypeFunction::ACTIVATE_VSYNC:
		vsync = App->renderer3D->GetVSYNC();
		App->renderer3D->SetVSYNC(vsync);
		break;
		
	case TypeFunction::CLOSE_WINDOW:
		tmp_obj = obj;
		while (tmp_obj->GetParent()->GetComponent(ComponentType::CANVAS_UI) == nullptr){
			tmp_obj = obj->GetParent();
			if (tmp_obj->GetParent()->GetComponent(ComponentType::CANVAS_UI) != nullptr) {
				break;
			}
		}
		tmp_obj->GetRectTransform()->SetVisible();
		break;
		
	default:
		break;
	}
}


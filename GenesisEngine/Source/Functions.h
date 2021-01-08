#pragma once

#include "Module.h"
#include "Globals.h"

enum TypeFunction {
	NONE_FUNCTION,
	START_GAME,
	CLOSE_WINDOW,
	ACTIVATE_VSYNC
};

class Functions : public Module
{
public:
	Functions(bool start_enabled = true);
	~Functions();

	bool Init();
	bool CleanUp();

	update_status PreUpdate(float dt) override;
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;

	void CallFunction(TypeFunction type, GameObject* obj);

private:
	TypeFunction function_type = NONE_FUNCTION;
	bool vsync;
	GameObject* tmp_obj;


};
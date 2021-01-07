#pragma once

#include "Module.h"
#include "Globals.h"

class ModuleFade : public Module {
public:
	enum fade_step {
		NONE,
		FADE_TO_BLACK,
		FADE_FROM_BLACK
	};

	ModuleFade();
	~ModuleFade();

	bool Init();

	update_status PreUpdate(float dt) override;
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;

	bool FadeToBlack(float time);
	bool FadeToColor(float time);

private:
	UINT32 start_time = NULL;
	UINT32 total_time = NULL;

	fade_step current_step = none;

};
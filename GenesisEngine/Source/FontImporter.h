#pragma once

#include "Module.h"
#include "Globals.h"

class FontImporter : public Module
{
public:
	FontImporter(bool start_enabled = true);
	~FontImporter();

	bool Init();
	bool CleanUp();

	update_status PreUpdate(float dt) override;
	update_status Update(float dt) override;
	update_status PostUpdate(float dt) override;

	void LoadFont();
private:
};
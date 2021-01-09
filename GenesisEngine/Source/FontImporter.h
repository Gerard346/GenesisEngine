#pragma once

#include "Module.h"
#include "Globals.h"
#include "MathGeoLib/include/Math/float2.h"
#include <vector>
#include <map>

struct Character {
	uint TextureID;  // ID handle of the glyph texture
	float2   Size;       // Size of glyph
	float2   Bearing;    // Offset from baseline to left/top of glyph
	uint Advance;    // Offset to advance to next glyph
};


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

	bool LoadFont();
private:
	std::map<char, Character> Characters;

};
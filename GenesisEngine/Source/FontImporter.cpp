#include "Globals.h"
#include "Application.h"

#include "FontImporter.h"
#include "FreeType/include/ft2build.h"
#include "FreeType/include/freetype/freetype.h"
#include "FreeType/include/freetype/ftglyph.h"
#include "FreeType/include/freetype/config/ftheader.h"

#pragma comment(lib, "FreeType/libx86/freetype.lib")

FontImporter::FontImporter(bool start_enabled) :Module(start_enabled)
{
	name = "Fonts";
}

FontImporter::~FontImporter()
{
}

bool FontImporter::Init()
{
	FT_Library ft;
	if (FT_Init_FreeType(&ft)) {
		LOG("FreeType Error loading freetype library. Could not init FreeType Library");
	}
	else {
		LOG("FreeType Library initialized correctly");
	}
	return true;
}

bool FontImporter::CleanUp()
{
	return true;
}

update_status FontImporter::PreUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

update_status FontImporter::Update(float dt)
{
	return UPDATE_CONTINUE;
}

update_status FontImporter::PostUpdate(float dt)
{
	return UPDATE_CONTINUE;
}

void FontImporter::LoadFont()
{

}

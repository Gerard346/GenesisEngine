#include "Globals.h"
#include "Application.h"

#include "FontImporter.h"
#include "FreeType/include/ft2build.h"
#include "FreeType/include/freetype/freetype.h"
#include "FreeType/include/freetype/ftglyph.h"
#include "FreeType/include/freetype/config/ftheader.h"

#include "glew/include/glew.h"

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
	LoadFont();
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

bool FontImporter::LoadFont()
{
	FT_Library ft;

	if (FT_Init_FreeType(&ft)) {
		LOG("FreeType Error loading freetype library. Could not init FreeType Library");
	}
	else {
		LOG("FreeType Library initialized correctly");
	}
	FT_Face face;

	//Set Font
	if (FT_New_Face(ft, "Assets/Fonts/DroidSans.ttf", 0, &face)) {
		fprintf(stderr, "Could not open font\n");
		return true;
	}
	//Set size
	FT_Set_Pixel_Sizes(face, 0, 48);

	FT_GlyphSlot g = face->glyph;

	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    for (unsigned char c = 0; c < 128; c++)
    {
        // load character glyph 
        if (FT_Load_Char(face, c, FT_LOAD_RENDER))
        {
            std::cout << "ERROR::FREETYTPE: Failed to load Glyph" << std::endl;
            continue;
        }
        // generate texture
        GLuint texture;
        glGenTextures(1, &texture);
        glBindTexture(GL_TEXTURE_2D, texture);
        glTexImage2D(
            GL_TEXTURE_2D,
            0,
            GL_RED,
            g->bitmap.width,
            g->bitmap.rows,
            0,
            GL_RED,
            GL_UNSIGNED_BYTE,
            g->bitmap.buffer
        );
        // set texture options
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        // now store character for later use
        Character character = {
            texture,
            float2(g->bitmap.width, g->bitmap.rows),
            float2(g->bitmap_left, g->bitmap_top),
            g->advance.x
        };

        Characters.insert(std::pair<GLchar, Character>(c, character));
    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    FT_Done_Face(face);
    FT_Done_FreeType(ft);

    return true;
}

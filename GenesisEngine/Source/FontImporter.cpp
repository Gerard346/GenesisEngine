#include "Globals.h"
#include "Application.h"

#include "FontImporter.h"
#include "FreeType/include/ft2build.h"
#include "FreeType/include/freetype/freetype.h"
#include "FreeType/include/freetype/ftglyph.h"
#include "FreeType/include/freetype/config/ftheader.h"

#include "glew/include/glew.h"
#pragma comment(lib, "FreeType/libx86/freetype.lib")


inline void move_raster_x(int x) {
    glBitmap(0, 0, 0, 0, x, 0, NULL);
}
inline void move_raster_y(int y) {
    glBitmap(0, 0, 0, 0, 0, y, NULL);
}

void freetype_mod::Print(const font_data& ft_font, const char* fmt, float3 pos)
{
    char		text[256];								
    va_list		ap;										

    if (fmt == NULL)									
        *text = 0;											

    else {
        va_start(ap, fmt);							
        vsprintf(text, fmt, ap);						
        va_end(ap);										
    }

    glPushAttrib(GL_CURRENT_BIT | GL_PIXEL_MODE_BIT | GL_ENABLE_BIT);
    glDisable(GL_TEXTURE_2D);
    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glDisable(GL_LIGHTING);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    GLint old_unpack;
    glGetIntegerv(GL_UNPACK_ALIGNMENT, &old_unpack);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);

    float color[4];
    glGetFloatv(GL_CURRENT_COLOR, color);

    glPixelTransferf(GL_RED_SCALE, color[0]);
    glPixelTransferf(GL_GREEN_SCALE, color[1]);
    glPixelTransferf(GL_BLUE_SCALE, color[2]);
    glPixelTransferf(GL_ALPHA_SCALE, color[3]);

    move_raster_x(pos.x);
    move_raster_y(pos.y);

    for (int i = 0; text[i]; i++) {
        const char_data& cdata = *ft_font.chars[text[i]];

        move_raster_x(cdata.left);
        move_raster_y(cdata.move_up);

        glDrawPixels(cdata.w, cdata.h, GL_LUMINANCE_ALPHA, GL_UNSIGNED_BYTE, cdata.data);

        move_raster_y(-cdata.move_up);
        move_raster_x(cdata.advance - cdata.left);

    }

    glPixelStorei(GL_UNPACK_ALIGNMENT, old_unpack);
    glPopAttrib();
}

void freetype_mod::font_data::CleanUp()
{
    for (int i = 0; i < 128; i++) delete chars[i];
}

void freetype_mod::font_data::init(const char* fname, unsigned int h)
{
    this->h = h;

    FT_Library library;

    if (FT_Init_FreeType(&library))
        throw std::runtime_error("FT_Init_FreeType failed");

    FT_Face face;

    if (FT_New_Face(library, fname, 0, &face))
        throw std::runtime_error("FT_New_Face failed (there is probably a problem with your font file)");

    FT_Set_Char_Size(face, h << 6, h << 6, 96, 96);

    for (int i = 0; i < 128; i++) chars[i] = new char_data(i, face);

    FT_Done_Face(face);

    FT_Done_FreeType(library);
}

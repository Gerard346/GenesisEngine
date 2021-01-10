#ifndef _FONTIMPORTER_H_
#define _FONTIMPORTER_H_
#include "Module.h"
#include "Globals.h"
#include <vector>
#include <map>

#include "FreeType/include/ft2build.h"
#include "FreeType/include/freetype/freetype.h"
#include "FreeType/include/freetype/ftglyph.h"
#include "FreeType/include/freetype/ftoutln.h"
#include "FreeType/include/freetype/fttrigon.h"

#include <string>

namespace freetype_mod {

	using std::vector;

	//Ditto for string.
	using std::string;

	struct char_data {
		int w = 0;
		int h = 0;
		int advance = 0;
		int left = 0;
		int move_up = 0;
		unsigned char* data = nullptr;

		char_data(char ch, FT_Face face) {

			if (FT_Load_Glyph(face, FT_Get_Char_Index(face, ch), FT_LOAD_DEFAULT))
				throw std::runtime_error("FT_Load_Glyph failed");

			FT_Glyph glyph;
			if (FT_Get_Glyph(face->glyph, &glyph))
				throw std::runtime_error("FT_Get_Glyph failed");

			FT_Glyph_To_Bitmap(&glyph, ft_render_mode_normal, 0, 1);
			FT_BitmapGlyph bitmap_glyph = (FT_BitmapGlyph)glyph;

			FT_Bitmap& bitmap = bitmap_glyph->bitmap;

			advance = face->glyph->advance.x >> 6;
			left = bitmap_glyph->left;
			w = bitmap.width;
			h = bitmap.rows;
			move_up = bitmap_glyph->top - bitmap.rows;


			data = new unsigned char[2 * w * h];
			for (int x = 0; x < w; x++) for (int y = 0; y < h; y++) {
				const int my = h - 1 - y;
				data[2 * (x + w * my)] = 255;
				data[2 * (x + w * my) + 1] = bitmap.buffer[x + w * y];
			}
		}

		~char_data() { delete[] data; }
	};
	struct font_data {
		char_data* chars[128];

		float h = 0.0f;

		void init(const char* fname, unsigned int h);

		void CleanUp();
	};

	void Print(const font_data& ft_font, const char* fmt, float3 pos);

}

#endif
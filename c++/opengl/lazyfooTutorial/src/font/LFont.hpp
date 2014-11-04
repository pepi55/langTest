#ifndef LFONT_H
#define LFONT_H

#include <freetype2/ft2build.h>
#include FT_FREETYPE_H
#include FT_BITMAP_H

#include "../tex/LSpriteSheet.hpp"

class LFont : private LSpriteSheet {
	public:
		LFont(void);
		~LFont(void);

		static bool initFreetype(void);

		bool loadFreetype(std::string path, GLuint pixelSize);
		bool loadBitmap(std::string path);
		void freeFont(void);
		void renderText(GLfloat x, GLfloat y, std::string text);

	private:
		static FT_Library mLibrary;
		GLfloat mSpace,
						mLineHeight,
						mNewLine;
};

#endif

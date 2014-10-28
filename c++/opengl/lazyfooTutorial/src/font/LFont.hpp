#include "../tex/LSpriteSheet.hpp"

class LFont : private LSpriteSheet {
	public:
		LFont(void);
		~LFont(void);

		bool loadBitmap(std::string path);
		void freeFont(void);
		void renderText(GLfloat x, GLfloat y, std::string text);

	private:
		GLfloat mSpace,
						mLineHeight,
						mNewLine;
};

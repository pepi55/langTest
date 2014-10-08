#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <string>

#include "LOpenGL.hpp"
#include "LRect.hpp"

class LTexture {
	public:
		LTexture();
		~LTexture();

		bool lock(void);
		bool unlock(void);

		void render(GLfloat x, GLfloat y, LFRect *clip = NULL);
		void freeTexture(void);

		bool loadPixelsFromFile(std::string path);
		bool loadTextureFromFile(std::string path);
		bool loadTextureFromFileWithColorKey(std::string path, GLubyte r, GLubyte g, GLubyte b, GLubyte a = 000);
		bool loadTextureFromPixels32(void);
		bool loadTextureFromPixels32(GLuint *pixels, GLuint imgW, GLuint imgH, GLuint texW, GLuint texH);

		void setPixel32(GLuint x, GLuint y, GLuint pixel);

		GLuint getPixel32(GLuint x, GLuint y);
		GLuint *getPixelData32(void);
		GLuint getTextureID(void);
		GLuint textureWidth(void);
		GLuint textureHeight(void);
		GLuint imageWidth(void);
		GLuint imageHeight(void);

	private:
		GLuint powerOfTwo(GLuint num);
		GLuint *mPixels;
		GLuint mTextureID,
					 mTextureWidth,
					 mTextureHeight,
					 mImageWidth,
					 mImageHeight;
};

#endif

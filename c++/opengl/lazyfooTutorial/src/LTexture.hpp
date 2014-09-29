#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <stdio.h>
#include <string>

#include "LOpenGL.hpp"
#include "LRect.hpp"

class LTexture {
	public:
		LTexture();
		~LTexture();

		bool loadTextureFromFile(std::string path);
		bool loadTextureFromPixels32(GLuint *pixels, GLuint width, GLuint height);
		void freeTexture(void);
		void render(GLfloat x, GLfloat y, LFRect *clip = NULL);
		GLuint getTextureID(void);
		GLuint textureWidth(void);
		GLuint textureHeight(void);

	private:
		GLuint mTextureID,
					 mTextureWidth,
					 mTextureHeight;
};

#endif

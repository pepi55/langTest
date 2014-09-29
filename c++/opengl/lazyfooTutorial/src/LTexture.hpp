#ifndef LTEXTURE_H
#define LTEXTURE_H

#include "LOpenGL.hpp"
#include <stdio.h>
#include <string>

class LTexture {
	public:
		LTexture();
		~LTexture();

		bool loadTextureFromFile(std::string path);
		bool loadTextureFromPixels32(GLuint *pixels, GLuint width, GLuint height);
		void freeTexture(void);
		void render(GLfloat x, GLfloat y);
		GLuint getTextureID(void);
		GLuint textureWidth(void);
		GLuint textureHeight(void);

	private:
		GLuint mTextureID,
					 mTextureWidth,
					 mTextureHeight;
};

#endif

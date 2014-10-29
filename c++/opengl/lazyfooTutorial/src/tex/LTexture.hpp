#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <string>

#include "../ogl/LOpenGL.hpp"
#include "../prim/LRect.hpp"

class LTexture {
	public:
		LTexture();
		virtual ~LTexture();

		bool lock(void);
		bool unlock(void);

		void initVBO(void);
		void freeVBO(void);
		void render(GLfloat x, GLfloat y, LFRect *clip = NULL);
		virtual void freeTexture(void);

		bool loadPixelsFromFile8(std::string path);

		bool loadPixelsFromFile32(std::string path);
		bool loadTextureFromFile32(std::string path);
		bool loadTextureFromFileWithColorKey32(std::string path, GLubyte r, GLubyte g, GLubyte b, GLubyte a = 000);
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
		GLubyte *mPixels8;
		GLuint *mPixels32;
		GLuint powerOfTwo(GLuint num);
		GLuint mTextureID,
					 mPixelFormat,
					 mTextureWidth,
					 mTextureHeight,
					 mImageWidth,
					 mImageHeight,
					 mVBOID,
					 mIBOID;
};

#endif

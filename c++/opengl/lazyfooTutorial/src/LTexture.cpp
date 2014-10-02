#include "LTexture.hpp"
#include <IL/il.h>
#include <IL/ilu.h>

LTexture::LTexture() {
	mTextureID = 0;

	mTextureWidth = 0;
	mTextureHeight = 0;

	mImageWidth = 0;
	mImageHeight = 0;
}

LTexture::~LTexture() {
	freeTexture();
}

bool LTexture::loadTextureFromFile(std::string path) {
	bool textureLoaded = false;

	ILuint imgID = 0;
	ILboolean success;

	ilGenImages(1, &imgID);
	ilBindImage(imgID);

	success = ilLoadImage(path.c_str());

	if (success == IL_TRUE) {
		success = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);

		if (success == IL_TRUE) {
			GLuint imgWidth = (GLuint)ilGetInteger(IL_IMAGE_WIDTH);
			GLuint imgHeight = (GLuint)ilGetInteger(IL_IMAGE_HEIGHT);

			GLuint texWidth = powerOfTwo(imgWidth);
			GLuint texHeight = powerOfTwo(imgHeight);

			if (imgWidth != texWidth || imgHeight != texHeight) {
				iluImageParameter(ILU_PLACEMENT, ILU_UPPER_LEFT);
				iluEnlargeCanvas((int)texWidth, (int)texHeight, 1);
			}

			textureLoaded = loadTextureFromPixels32((GLuint*)ilGetData(),
					imgWidth, imgHeight,
					texWidth, texHeight
					);
		}

		ilDeleteImages(1, &imgID);
	}

	if (!textureLoaded) {
		fprintf(stderr, "Unable to load image %s\n", path.c_str());
	}

	return textureLoaded;
}

bool LTexture::loadTextureFromPixels32(GLuint *pixels, GLuint imgW, GLuint imgH, GLuint texW, GLuint texH) {
	freeTexture();

	mImageWidth = imgW;
	mImageHeight = imgH;
	mTextureWidth = texW;
	mTextureHeight = texH;

	glGenTextures(1, &mTextureID);
	glBindTexture(GL_TEXTURE_2D, mTextureID);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mTextureWidth, mTextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, (GLuint)NULL);

	GLenum error = glGetError();
	if (error != GL_NO_ERROR) {
		fprintf(stderr, "Error loading texture from %p pixels!\n%s\n", (void*)pixels, gluErrorString(error));
		return false;
	}

	return true;
}

void LTexture::freeTexture(void) {
	if (mTextureID != 0) {
		glDeleteTextures(1, &mTextureID);
		mTextureID = 0;
	}

	mImageWidth = 0;
	mImageHeight = 0;
	mTextureWidth = 0;
	mTextureHeight = 0;
}

void LTexture::render(GLfloat x, GLfloat y, LFRect *clip) {
	if (mTextureID != 0) {
		glLoadIdentity();

		GLfloat texTop = 0.0f;
		GLfloat	texBottom = (GLfloat)mImageHeight / (GLfloat)mTextureHeight;
		GLfloat texLeft = 0.0f;
		GLfloat texRight = (GLfloat)mImageWidth / (GLfloat)mTextureWidth;

		GLfloat quadWidth = mTextureWidth;
		GLfloat quadHeight = mTextureHeight;

		if (clip != NULL) {
			texLeft = clip->x / mTextureWidth;
			texRight = (clip->x + clip->w) / mTextureWidth;
			texTop = clip->y / mTextureHeight;
			texBottom = (clip->y + clip->h) / mTextureHeight;

			quadWidth = clip->w;
			quadHeight = clip->h;
		}

		glTranslatef(x, y, 0.0f);
		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, mTextureID);

		glBegin(GL_QUADS);
			glTexCoord2f(texLeft, texTop);			glVertex2f(0.0f, 0.0f);
			glTexCoord2f(texRight, texTop);			glVertex2f(quadWidth, 0.0f);
			glTexCoord2f(texRight, texBottom);	glVertex2f(quadWidth, quadHeight);
			glTexCoord2f(texLeft, texBottom);		glVertex2f(0.0f, quadHeight);
		glEnd();
	}
}

GLuint LTexture::powerOfTwo(GLuint num) {
	if (num != 0) {
		num--;
		num |= (num >> 1);
		num |= (num >> 2);
		num |= (num >> 4);
		num |= (num >> 8);
		num |= (num >> 16);
		num++;
	}

	return num;
}

GLuint LTexture::getTextureID(void) {
	return mTextureID;
}

GLuint LTexture::textureWidth(void) {
	return mTextureWidth;
}

GLuint LTexture::textureHeight(void) {
	return mTextureHeight;
}

GLuint LTexture::imageWidth(void) {
	return mImageWidth;
}

GLuint LTexture::imageHeight(void) {
	return mImageHeight;
}

#include "LTexture.hpp"
#include <string.h>
#include <IL/il.h>
#include <IL/ilu.h>

LTexture::LTexture() {
	mTextureID = 0;
	mPixels = NULL;

	mTextureWidth = 0;
	mTextureHeight = 0;

	mImageWidth = 0;
	mImageHeight = 0;
}

LTexture::~LTexture() {
	freeTexture();
}

bool LTexture::lock(void) {
	if (mPixels == NULL && mTextureID != 0) {
		GLuint size = mTextureWidth * mTextureHeight;
		mPixels = new GLuint[size];

		glBindTexture(GL_TEXTURE_2D, mTextureID);
		glGetTexImage(GL_TEXTURE_2D, 0, GL_RGBA, GL_UNSIGNED_BYTE, mPixels);
		glBindTexture(GL_TEXTURE_2D, (GLuint)NULL);

		return true;
	}

	return false;
}

bool LTexture::unlock(void) {
	if (mPixels != NULL && mTextureID != 0) {
		glBindTexture(GL_TEXTURE_2D, mTextureID);

		glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0,mTextureWidth, mTextureHeight,
				GL_RGBA, GL_UNSIGNED_BYTE, mPixels
				);

		delete[] mPixels;
		mPixels = NULL;
		glBindTexture(GL_TEXTURE_2D, (GLuint)NULL);

		return true;
	}

	return false;
}

bool LTexture::loadPixelsFromFile(std::string path) {
	freeTexture();

	bool pixelsLoaded = false;
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

			GLuint size = texWidth * texHeight;
			mPixels = new GLuint[size];

			mImageWidth = imgWidth;
			mImageHeight = imgHeight;
			mTextureWidth = texWidth;
			mTextureHeight = texHeight;

			memcpy(mPixels, ilGetData(), size * 4);
			pixelsLoaded = true;
		}

		ilDeleteImages(1, &imgID);
	}

	if (!pixelsLoaded) {
		fprintf(stderr, "Unable to load %s\n", path.c_str());
	}

	return pixelsLoaded;
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

bool LTexture::loadTextureFromFileWithColorKey(std::string path, GLubyte r, GLubyte g, GLubyte b, GLubyte a) {
	if (!loadPixelsFromFile(path)) {
		return false;
	}

	GLuint size = mTextureWidth * mTextureHeight;
	for (GLuint i = 0; i < size; ++i) {
		GLubyte *colors = (GLubyte*)&mPixels[i];

		if (colors[0] == r && colors[1] == g && colors[2] == b && (0 == a || colors[3] == a)) {
			colors[0] = 255;
			colors[1] = 255;
			colors[2] = 255;
			colors[3] = 000;
		}
	}

	return loadTextureFromPixels32();
}

bool LTexture::loadTextureFromPixels32(void) {
	bool success = true;

	if (mTextureID == 0 && mPixels != NULL) {
		glGenTextures(1, &mTextureID);
		glBindTexture(GL_TEXTURE_2D, mTextureID);
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mTextureWidth, mTextureHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, mPixels);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

		glBindTexture(GL_TEXTURE_2D, (GLuint)NULL);

		GLenum error = glGetError();
		if (error != GL_NO_ERROR) {
			fprintf(stderr, "Error loading texture from %p pixels!\n%s\n", (void*)mPixels, gluErrorString(error));
			success = false;
		} else {
			delete[] mPixels;
			mPixels = NULL;
		}
	} else {
		fprintf(stderr, "Cannot load texture from pixels!\n");

		if (mTextureID != 0) {
			fprintf(stderr, "A texture has already been loaded!\n");
		} else if (mPixels == NULL) {
			fprintf(stderr, "No pixels to create texture from!\n");
		}

		success = false;
	}

	return success;
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

	if (mPixels != NULL) {
		delete[] mPixels;
		mPixels = NULL;
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

		if (stretch != NULL) {
			quadWidth = stretch->w;
			quadHeight = stretch->h;
		}

		glTranslatef(x + quadWidth / 2.0f, y + quadHeight / 2.0f, 0.0f);
		glRotatef(degrees, 0.0f, 0.0f, 1.0f);

		glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);
		glBindTexture(GL_TEXTURE_2D, mTextureID);

		glBegin(GL_QUADS);
			glTexCoord2f(texLeft, texTop);			glVertex2f(-quadWidth / 2.0f, -quadHeight / 2.0f);
			glTexCoord2f(texRight, texTop);			glVertex2f(quadWidth / 2.0f, -quadHeight / 2.0f);
			glTexCoord2f(texRight, texBottom);	glVertex2f(quadWidth / 2.0f, quadHeight / 2.0f);
			glTexCoord2f(texLeft, texBottom);		glVertex2f(-quadWidth / 2.0f, quadHeight / 2.0f);
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

void LTexture::setPixel32(GLuint x, GLuint y, GLuint pixel) {
	mPixels[y * mTextureWidth + x] = pixel;
}

GLuint LTexture::getPixel32(GLuint x, GLuint y) {
	return mPixels[y * mTextureWidth + x];
}

GLuint *LTexture::getPixelData32(void) {
	return mPixels;
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

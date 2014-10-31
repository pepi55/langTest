#include "LFont.hpp"

LFont::LFont(void) {
	mSpace = 0.0f;
	mLineHeight = 0.0f;
	mNewLine = 0.0f;
}

LFont::~LFont(void) {
	freeFont();
}

bool LFont::loadBitmap(std::string path) {
	bool success = true;
	const GLuint BLACK_PIXEL = 0x00;

	freeFont();

	if (loadPixelsFromFile8(path)) {
		GLfloat cellW = imageWidth() / 16.0f;
		GLfloat cellH = imageHeight() / 16.0f;

		GLuint top = cellH;
		GLuint bottom = 0;
		GLuint aBottom = 0;

		int pX = 0;
		int pY = 0;
		int bX = 0;
		int bY = 0;

		GLuint currentChar = 0;
		LFRect nextClip = {0.0f, 0.0f, cellH, cellW};

		for (unsigned int rows = 0; rows < 16; ++rows) {
			for (unsigned int cols = 0; cols < 16; ++cols) {
				bX = cellW * cols;
				bY = cellH * rows;

				nextClip.x = cellW * cols;
				nextClip.y = cellH * rows;
				nextClip.w = cellW;
				nextClip.h = cellH;

				//Left side
				for (int pCol = 0; pCol < cellW; ++pCol) {
					for (int pRow = 0; pRow < cellH; ++pRow) {
						pX = bX + pCol;
						pY = bY + pRow;

						if (getPixel8(pX, pY) != BLACK_PIXEL) {
							nextClip.x = pX;

							pCol = cellW;
							pRow = cellH;
						}
					}
				}

				//Right side
				for (int pCol_w = cellW - 1; pCol_w >= 0; --pCol_w) {
					for (int pRow_w = 0; pRow_w < cellH; ++pRow_w) {
						pX = bX + pCol_w;
						pY = bY + pRow_w;

						if (getPixel8(pX, pY) != BLACK_PIXEL) {
							nextClip.w = (pX - nextClip.x) + 1;

							pCol_w = -1;
							pRow_w = cellH;
						}
					}
				}

				//Top side
				for (int pRow = 0; pRow < cellH; ++pRow) {
					for (int pCol = 0; pCol < cellW; ++pCol) {
						pX = bX + pCol;
						pY = bY + pRow;

						if (getPixel8(pX, pY) != BLACK_PIXEL) {
							if (pRow < (int)top) {
								top = pRow;
							}

							pCol = cellW;
							pRow = cellH;
						}
					}
				}

				//Bottom side
				for (int pRow_b = cellH - 1; pRow_b >= 0; --pRow_b) {
					for (int pCol_b = 0; pCol_b < cellW; ++pCol_b) {
						pX = bX + pCol_b;
						pY = bY + pRow_b;

						if (getPixel8(pX, pY) != BLACK_PIXEL) {
							if (currentChar == 'A') {
								aBottom = pRow_b;
							}

							if (pRow_b > (int)bottom) {
								bottom = pRow_b;
							}

							pCol_b = cellW;
							pRow_b = -1;
						}
					}
				}

				mClips.push_back(nextClip);
				currentChar++;
			}
		}

		for (int t = 0; t < 256; ++t) {
			mClips[t].y += top;
			mClips[t].h -= top;
		}

		if (loadTextureFromPixels8()) {
			if (!generateDataBuffer(LSPRITE_ORIGIN_TOP_LEFT)) {
				fprintf(stderr, "Unable to create vertex buffer for bitmap font!\n");
				success = false;
			}
		} else {
			fprintf(stderr, "Unable to create texture from bitmap font pixels!\n");
			success = false;
		}

		glBindTexture(GL_TEXTURE_2D, getTextureID());
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);

		mSpace = cellW / 2;
		mNewLine = aBottom - top;
		mLineHeight = bottom - top;
	} else {
		fprintf(stderr, "Could not load bitmap font image %s!\n", path.c_str());
		success = false;
	}

	return success;
}

void LFont::freeFont(void) {
	freeTexture();

	mSpace = 0.0f;
	mNewLine = 0.0f;
	mLineHeight = 0.0f;
}

void LFont::renderText(GLfloat x, GLfloat y, std::string text) {
	if (getTextureID() != 0) {
		GLfloat dX = x;
		GLfloat dY = y;

		glTranslatef(x, y, 0.0f);
		glBindTexture(GL_TEXTURE_2D, getTextureID());

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBuffer(GL_ARRAY_BUFFER, mVertexDataBuffer);
			glTexCoordPointer(2, GL_FLOAT, sizeof(LVertexData2D), (GLvoid*)offsetof(LVertexData2D, texCoord));
			glVertexPointer(2, GL_FLOAT, sizeof(LVertexData2D), (GLvoid*)offsetof(LVertexData2D, position));

			for (int i = 0; i < (int)text.length(); ++i) {
				if (text[i] == ' ') {
					glTranslatef(mSpace, 0.0f, 0.0f);
					dX += mSpace;
				} else if (text[i] == '\n') {
					glTranslatef(x - dX, mNewLine, 0.0f);

					dY += mNewLine;
					dX += x - dX;
				} else {
					GLuint ascii = (unsigned char)text[i];

					glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffers[ascii]);
					glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, NULL);

					glTranslatef(mClips[ascii].w, 0.0f, 0.0f);
					dX += mClips[ascii].w;
				}
			}
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

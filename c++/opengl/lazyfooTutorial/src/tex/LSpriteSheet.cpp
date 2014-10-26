#include "LSpriteSheet.hpp"

LSpriteSheet::LSpriteSheet(void) {
	mVertexDataBuffer = 0x0;
	mIndexBuffers = NULL;
}

LSpriteSheet::~LSpriteSheet(void) {
	freeSheet();
}

int LSpriteSheet::addClipSprite(LFRect &newClip) {
	mClips.push_back(newClip);

	return mClips.size() - 1;
}

LFRect LSpriteSheet::getClip(int index) {
	return mClips[index];
}

bool LSpriteSheet::generateDataBuffer(void) {
	if (getTextureID() != 0 && mClips.size() > 0) {
		int totalSprites = mClips.size();
		LVertexData2D *vertexData = new LVertexData2D[totalSprites * 4];
		mIndexBuffers = new GLuint[totalSprites];

		glGenBuffers(1, &mVertexDataBuffer);
		glGenBuffers(totalSprites, mIndexBuffers);

		GLfloat tW = textureWidth();
		GLfloat tH = textureHeight();
		GLuint spriteIndices[4] = {0, 0, 0, 0};

		for (int i = 0; i < totalSprites; ++i) {
			spriteIndices[0] = i * 4 + 0;
			spriteIndices[1] = i * 4 + 1;
			spriteIndices[2] = i * 4 + 2;
			spriteIndices[3] = i * 4 + 3;

			vertexData[spriteIndices[0]].position.x = -mClips[i].w / 2.0f;
			vertexData[spriteIndices[0]].position.y = -mClips[i].h / 2.0f;
			vertexData[spriteIndices[0]].texCoord.s = (mClips[i].x) / tW;
			vertexData[spriteIndices[0]].texCoord.t = (mClips[i].y) / tH;

			vertexData[spriteIndices[1]].position.x = mClips[i].w / 2.0f;
			vertexData[spriteIndices[1]].position.y = -mClips[i].h / 2.0f;
			vertexData[spriteIndices[1]].texCoord.s = (mClips[i].x + mClips[i].w) / tW;
			vertexData[spriteIndices[1]].texCoord.t = (mClips[i].y) / tH;

			vertexData[spriteIndices[2]].position.x = mClips[i].w / 2.0f;
			vertexData[spriteIndices[2]].position.y = mClips[i].h / 2.0f;
			vertexData[spriteIndices[2]].texCoord.s = (mClips[i].x + mClips[i].w) / tW;
			vertexData[spriteIndices[2]].texCoord.t = (mClips[i].y + mClips[i].h) / tH;

			vertexData[spriteIndices[3]].position.x = -mClips[i].w / 2.0f;
			vertexData[spriteIndices[3]].position.y = mClips[i].h / 2.0f;
			vertexData[spriteIndices[3]].texCoord.s = (mClips[i].x) / tW;
			vertexData[spriteIndices[3]].texCoord.t = (mClips[i].y + mClips[i].h) / tH;

			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffers[i]);
			glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(GLuint), spriteIndices, GL_STATIC_DRAW);
		}

		glBindBuffer(GL_ARRAY_BUFFER, mVertexDataBuffer);
		glBufferData(GL_ARRAY_BUFFER, totalSprites * 4 * sizeof(LVertexData2D), vertexData, GL_STATIC_DRAW);

		delete[] vertexData;
	} else {
		if (getTextureID() == 0) {
			fprintf(stderr, "No texture to render with!\n");
		}

		if (mClips.size() <= 0) {
			fprintf(stderr, "No clips to generate vertex data from!\n");
		}

		return false;
	}

	return true;
}

void LSpriteSheet::freeSheet(void) {
	if (mVertexDataBuffer != 0x0) {
		glDeleteBuffers(1, &mVertexDataBuffer);
		mVertexDataBuffer = 0x0;
	}

	if (mIndexBuffers != NULL) {
		glDeleteBuffers(mClips.size(), mIndexBuffers);
		delete[] mIndexBuffers;
		mIndexBuffers = NULL;
	}

	mClips.clear();
}

void LSpriteSheet::freeTexture(void) {
	freeSheet();

	LTexture::freeTexture();
}

void LSpriteSheet::renderSprite(int index) {
	if (mVertexDataBuffer != 0x0) {
		glBindTexture(GL_TEXTURE_2D, getTextureID());

		glEnableClientState(GL_VERTEX_ARRAY);
		glEnableClientState(GL_TEXTURE_COORD_ARRAY);
			glBindBuffer(GL_ARRAY_BUFFER, mVertexDataBuffer);
			glTexCoordPointer(2, GL_FLOAT, sizeof(LVertexData2D), (GLvoid*)offsetof(LVertexData2D, texCoord));
			glVertexPointer(2, GL_FLOAT, sizeof(LVertexData2D), (GLvoid*)offsetof(LVertexData2D, position));
			glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIndexBuffers[index]);
			glDrawElements(GL_QUADS, 4, GL_UNSIGNED_INT, NULL);
		glDisableClientState(GL_TEXTURE_COORD_ARRAY);
		glDisableClientState(GL_VERTEX_ARRAY);
	}
}

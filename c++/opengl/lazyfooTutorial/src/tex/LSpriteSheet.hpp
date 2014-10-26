#ifndef LSPRITE_SHEET_H
#define LSPRITE_SHEET_H

#include <vector>
#include "LTexture.hpp"

class LSpriteSheet : public LTexture {
	public:
		LSpriteSheet(void);
		~LSpriteSheet(void);

		int addClipSprite(LFRect &newClip);
		LFRect getClip(int index);
		bool generateDataBuffer(void);
		void freeSheet(void);
		void freeTexture(void);
		void renderSprite(int index);

	private:
		std::vector<LFRect> mClips;
		GLuint mVertexDataBuffer;
		GLuint *mIndexBuffers;
};

#endif

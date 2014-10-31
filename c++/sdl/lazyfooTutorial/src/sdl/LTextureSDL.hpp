#ifndef LTEXTURE_SDL_H
#define LTEXTURE_SDL_H

#include <string>
#include "LSDL.hpp"

class LTextureSDL {
	public:
		LTextureSDL(void);
		~LTextureSDL(void);

		bool loadFromFile(SDL_Renderer *renderer, std::string path);

		void free(void);
		void render(SDL_Renderer *renderer, int x, int y);

		int getWidth(void);
		int getHeight(void);

	private:
		SDL_Texture *mTexture;

		int mWidth;
		int mHeight;
};

#endif

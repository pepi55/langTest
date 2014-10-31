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
		void setColor(Uint8 red, Uint8 green, Uint8 blue);
		void render(SDL_Renderer *renderer, int x, int y, SDL_Rect *clip = NULL);

		int getWidth(void);
		int getHeight(void);

	private:
		SDL_Texture *mTexture;

		int mWidth;
		int mHeight;
};

#endif

#include "LTextureSDL.hpp"

LTextureSDL::LTextureSDL(void) {
	mTexture = NULL;

	mWidth = 0;
	mHeight = 0;
}

LTextureSDL::~LTextureSDL(void) {
	free();
}

bool LTextureSDL::loadFromFile(SDL_Renderer *renderer, std::string path) {
	free();

	SDL_Texture *newTexture = NULL;
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());

	if (loadedSurface == NULL) {
		fprintf(stderr, "Unable to load image %s!\nIMG_Error: %s\n", path.c_str(), IMG_GetError());
	} else {
		SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
		newTexture = SDL_CreateTextureFromSurface(renderer, loadedSurface);

		if (newTexture == NULL) {
			fprintf(stderr, "Unable to create texture from %s!\nSDL_Error: %s\n", path.c_str(), SDL_GetError());
		} else {
			mWidth = loadedSurface->w;
			mHeight = loadedSurface->h;
		}

		SDL_FreeSurface(loadedSurface);
	}

	mTexture = newTexture;
	return mTexture != NULL;
}

void LTextureSDL::free(void) {
	if (mTexture != NULL) {
		SDL_DestroyTexture(mTexture);

		mTexture = NULL;
		mWidth = 0;
		mHeight = 0;
	}
}

void LTextureSDL::render(SDL_Renderer *renderer, int x, int y) {
	SDL_Rect renderQuad = {x, y, mWidth, mHeight};
	SDL_RenderCopy(renderer, mTexture, NULL, &renderQuad);
}

int LTextureSDL::getWidth(void) {
	return mWidth;
}

int LTextureSDL::getHeight(void) {
	return mHeight;
}

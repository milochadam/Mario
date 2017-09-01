#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <SDL2/SDL.h>
#include <string>
class LTexture
{
	public:
        LTexture();
        LTexture(SDL_Renderer* s);
		~LTexture();

		bool loadFromFile( std::string path );
		void free();
		void render( int x, int y );

		int getWidth();
		int getHeight();

	private:
		SDL_Texture* mTexture;
        SDL_Renderer* renderer;
		int mWidth;
		int mHeight;
};
#endif //LTEXTURE_H
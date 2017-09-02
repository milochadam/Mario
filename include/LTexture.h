#ifndef LTEXTURE_H
#define LTEXTURE_H

#include <SDL2/SDL.h>
#include <string>
class LTexture {
	public:
        LTexture();
        LTexture(SDL_Renderer* s);
		~LTexture();

		bool loadFromFile( std::string path );
		void free();
		void setColor( Uint8 red, Uint8 green, Uint8 blue );
        void setBlendMode( SDL_BlendMode blending );
		void setAlpha( Uint8 alpha );
		void render( int x, int y, SDL_Rect* clip = NULL );

		int getWidth();
		int getHeight();

	private:
		SDL_Texture* mTexture;
        SDL_Renderer* renderer;
		int mWidth;
		int mHeight;
};
#endif //LTEXTURE_H
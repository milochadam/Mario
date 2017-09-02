#include "../include/Cmain.h"
#include <iostream>
#include "../include/LTexture.h"
Cmain::Cmain() : SCREEN_WIDTH(640), SCREEN_HEIGHT(480) {
    window = NULL;
	screenSurface = NULL;
	
	helloWorld=NULL;
	exitImage=NULL;
	currentSurface=NULL;
	pngSurface=NULL;

	renderer=NULL;
	texture=NULL;

	for(int i=0;i<KB_TOTAL;i++) {
		kbSurfaces[i]=NULL;
	}
}

Cmain::~Cmain(){
	freeSurface(helloWorld);
	freeSurface(exitImage);
	freeSurface(pngSurface);

	for(int i=0;i<KB_TOTAL;i++) {
		freeSurface( kbSurfaces[i] );
	}

	//Free loaded image
	SDL_DestroyTexture( texture );
	texture = NULL;

	//Destroy window	
	SDL_DestroyRenderer( renderer );
	SDL_DestroyWindow( window );
	window = NULL;
	renderer = NULL;

	//Quit SDL subsystems
	IMG_Quit();
    SDL_Quit();
}

int Cmain::main(){
	
	int posx=240,posy=190;
    if( !init() ) {
		printf( "Failed to initialize!\n" );
		return 0;
	}
	
	//Load media
	if( !loadMedia() ) {
		printf( "Failed to load media!\n" );
		return 0;
	}
	
	bool quit = false;

	currentSurface=kbSurfaces[KB_DEFAULT];

	while( !quit ) {
		while( SDL_PollEvent( &e ) != 0 ) {
			if( e.type == SDL_QUIT ) {
				quit = true;
			} else if( e.type == SDL_KEYDOWN ) {
				switch( e.key.keysym.sym ) {
					case SDLK_UP:
					posy-=5;
					break;

					case SDLK_DOWN:
					posy+=5;
					break;

					case SDLK_LEFT:
					posx-=5;
					break;

					case SDLK_RIGHT:
					posx+=5;
					break;

					case SDLK_p:
					break;

					default:
					break;
				}
			}
		}
		//Clear screen
		SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( renderer );

		//Render top left sprite
		spriteSheetTexture->render( 0, 0, &spriteClips[ 0 ] );

		//Render top right sprite
		spriteSheetTexture->render( SCREEN_WIDTH - spriteClips[ 1 ].w, 0, &spriteClips[ 1 ] );

		//Render bottom left sprite
		spriteSheetTexture->render( 0, SCREEN_HEIGHT - spriteClips[ 2 ].h, &spriteClips[ 2 ] );

		//Render bottom right sprite
		spriteSheetTexture->render( SCREEN_WIDTH - spriteClips[ 3 ].w, SCREEN_HEIGHT - spriteClips[ 3 ].h, &spriteClips[ 3 ] );

		//Update screen
		SDL_RenderPresent( renderer );
	}


}

bool Cmain::init(){
	/**
	 * initializing: 
	 * success = true
	 *  failure = false
	 */

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		return false;
	}

	if( !SDL_SetHint( SDL_HINT_RENDER_SCALE_QUALITY, "1" ) ) {
		printf( "Warning: Linear texture filtering not enabled!" );
	}

	window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
	if( window == NULL ) {
		printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
		return false;
	}

	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED );
	if( renderer == NULL ) {
		printf( "Renderer could not be created! SDL Error: %s\n", SDL_GetError() );
		return false;
	}
	//Initialize renderer color
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );

	//Initialize PNG loading
	int imgFlags = IMG_INIT_PNG;
	if( !( IMG_Init( imgFlags ) & imgFlags ) ) {
		printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
		return false;
	}

	//Get window surface
	screenSurface = SDL_GetWindowSurface( window );

	return true;
}

bool Cmain::loadMedia() {
	bool success = true;

	helloWorld = loadSurface( "../../res/hello_world.bmp" );
	if( helloWorld == NULL ) {
		printf( "Failed to load helloWorld image!\n" );
		success = false;
	}
	exitImage = loadSurface( "../../res/x.bmp" );
	if( exitImage == NULL ) {
		printf( "Failed to load exitImage image!\n" );
		success = false;
	}
	pngSurface = loadSurface( "../../res/loaded.png" );
	if( exitImage == NULL ) {
		printf( "Failed to load png image!\n" );
		success = false;
	}
	//Load default surface
	kbSurfaces[ KB_DEFAULT ] = loadSurface( "../../res/press.bmp" );
	if( kbSurfaces[ KB_DEFAULT ] == NULL ) {
		printf( "Failed to load default image!\n" );
		success = false;
	}

	//Load up surface
	kbSurfaces[ KB_UP ] = loadSurface( "../../res/up.bmp" );
	if( kbSurfaces[ KB_UP ] == NULL ) {
		printf( "Failed to load up image!\n" );
		success = false;
	}

	//Load down surface
	kbSurfaces[ KB_DOWN ] = loadSurface( "../../res/down.bmp" );
	if( kbSurfaces[ KB_DOWN ] == NULL ) {
		printf( "Failed to load down image!\n" );
		success = false;
	}

	//Load left surface
	kbSurfaces[ KB_LEFT ] = loadSurface( "../../res/left.bmp" );
	if( kbSurfaces[ KB_LEFT ] == NULL ) {
		printf( "Failed to load left image!\n" );
		success = false;
	}

	//Load right surface
	kbSurfaces[ KB_RIGHT ] = loadSurface( "../../res/right.bmp" );
	if( kbSurfaces[ KB_RIGHT ] == NULL ) {
		printf( "Failed to load right image!\n" );
		success = false;
	}

	//Load PNG texture
	texture = loadTexture( "../../res/texture.png" );
	if( texture == NULL ) {
		printf( "Failed to load texture image!\n" );
		success = false;
	}

	fooTexture = new LTexture(renderer);
	if( !fooTexture->loadFromFile("../../res/foo.png") ) {
		printf( "Failed to load texture image!\n" );
		success = false;
	}
	bgTexture = new LTexture(renderer);
	if( !bgTexture->loadFromFile("../../res/background.png") ) {
		printf( "Failed to load texture image!\n" );
		success = false;
	}
	spriteSheetTexture = new LTexture(renderer);
	if( !spriteSheetTexture->loadFromFile("../../res/dots.png") ) {
		printf( "Failed to load texture image!\n" );
		success = false;
	} else {
        spriteClips[ 0 ].x =   0;
        spriteClips[ 0 ].y =   0;
        spriteClips[ 0 ].w = 100;
		spriteClips[ 0 ].h = 100;
		
        spriteClips[ 1 ].x = 100;
        spriteClips[ 1 ].y =   0;
        spriteClips[ 1 ].w = 100;
		spriteClips[ 1 ].h = 100;
		
        spriteClips[ 2 ].x =   0;
        spriteClips[ 2 ].y = 100;
        spriteClips[ 2 ].w = 100;
		spriteClips[ 2 ].h = 100;
		
        spriteClips[ 3 ].x = 100;
        spriteClips[ 3 ].y = 100;
        spriteClips[ 3 ].w = 100;
        spriteClips[ 3 ].h = 100;
	}


	return success;
}

void Cmain::freeSurface(SDL_Surface* s) {
	SDL_FreeSurface( s );
	s = NULL;
}

SDL_Surface* Cmain::loadSurface( std::string path ) {
	SDL_Surface* optimizedSurface = NULL;
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL ) {
		printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), IMG_GetError() );
		return NULL;
	}

	optimizedSurface = SDL_ConvertSurface( loadedSurface, screenSurface->format, 0 );
	if( optimizedSurface == NULL ) {
		printf( "Unable to optimize image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
		return NULL;
	}

	SDL_FreeSurface( loadedSurface );
	return optimizedSurface;
}

SDL_Texture* Cmain::loadTexture( std::string path ) {
	//The final texture
	SDL_Texture* newTexture = NULL;

	//Load image at specified path
	SDL_Surface* loadedSurface = IMG_Load( path.c_str() );
	if( loadedSurface == NULL ) {
		printf( "Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError() );
		return NULL;
	}
	//Create texture from surface pixels
	newTexture = SDL_CreateTextureFromSurface( renderer, loadedSurface );
	SDL_FreeSurface( loadedSurface );

	if( newTexture == NULL ) {
		printf( "Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
	}

	return newTexture;
}

void Cmain::stretch(SDL_Surface* s) {
	SDL_Rect stretchRect;
	stretchRect.x = 0;
	stretchRect.y = 0;
	stretchRect.w = SCREEN_WIDTH;
	stretchRect.h = SCREEN_HEIGHT;
	SDL_BlitScaled( s, NULL, screenSurface, &stretchRect );
}

void Cmain::example_08() {
		//Clear screen
		SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
		SDL_RenderClear( renderer );

		//Render red filled quad
		SDL_Rect fillRect = { SCREEN_WIDTH / 4, SCREEN_HEIGHT / 4, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
		SDL_SetRenderDrawColor( renderer, 0xFF, 0x00, 0x00, 0xFF );		
		SDL_RenderFillRect( renderer, &fillRect );

		//Render green outlined quad
		SDL_Rect outlineRect = { SCREEN_WIDTH / 6, SCREEN_HEIGHT / 6, SCREEN_WIDTH * 2 / 3, SCREEN_HEIGHT * 2 / 3 };
		SDL_SetRenderDrawColor( renderer, 0x00, 0xFF, 0x00, 0xFF );		
		SDL_RenderDrawRect( renderer, &outlineRect );
		
		//Draw blue horizontal line
		SDL_SetRenderDrawColor( renderer, 0x00, 0x00, 0xFF, 0xFF );		
		SDL_RenderDrawLine( renderer, 0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2 );

		//Draw vertical line of yellow dots
		SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0x00, 0xFF );
		for( int i = 0; i < SCREEN_HEIGHT; i += 4 ) {
			SDL_RenderDrawPoint( renderer, SCREEN_WIDTH / 2, i );
		}

		//Update screen
		SDL_RenderPresent( renderer );
}
void Cmain::example_09() {
	//Clear screen
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( renderer );

	//Top left corner viewport
	SDL_Rect topLeftViewport;
	topLeftViewport.x = 0;
	topLeftViewport.y = 0;
	topLeftViewport.w = SCREEN_WIDTH / 2;
	topLeftViewport.h = SCREEN_HEIGHT / 2;
	SDL_RenderSetViewport( renderer, &topLeftViewport );
	
	//Render texture to screen
	SDL_RenderCopy( renderer, texture, NULL, NULL );


	//Top right viewport
	SDL_Rect topRightViewport;
	topRightViewport.x = SCREEN_WIDTH / 2;
	topRightViewport.y = 0;
	topRightViewport.w = SCREEN_WIDTH / 2;
	topRightViewport.h = SCREEN_HEIGHT / 2;
	SDL_RenderSetViewport( renderer, &topRightViewport );
	
	//Render texture to screen
	SDL_RenderCopy( renderer, texture, NULL, NULL );


	//Bottom viewport
	SDL_Rect bottomViewport;
	bottomViewport.x = 0;
	bottomViewport.y = SCREEN_HEIGHT / 2;
	bottomViewport.w = SCREEN_WIDTH;
	bottomViewport.h = SCREEN_HEIGHT / 2;
	SDL_RenderSetViewport( renderer, &bottomViewport );

	
	//Render texture to screen
	SDL_RenderCopy( renderer, texture, NULL, NULL );


	//Update screen
	SDL_RenderPresent( renderer );
}

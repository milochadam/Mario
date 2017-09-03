#include "../include/Cmain.h"
#include <iostream>
#include "../include/LTexture.h"
Cmain::Cmain() : SCREEN_WIDTH(640), SCREEN_HEIGHT(480), WALKING_ANIMATION_FRAMES(4) {

    window = NULL;
	screenSurface = NULL;

	frame=0;

	renderer=NULL;
	texture=NULL;

	for(int i=0;i<KB_TOTAL;i++) {
		kbSurfaces[i]=NULL;
	}
}

Cmain::~Cmain(){

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
	
	
	const int WALKING_ANIMATION_FRAMES = 4;

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


	while( !quit ) {
		while( SDL_PollEvent( &e ) != 0 ) {
			if( e.type == SDL_QUIT ) {
				quit = true;
			} else if( e.type == SDL_KEYDOWN ) {
				
			}
		}
		clear();
		updateScreen();
	}


}

void Cmain::updateScreen(){


	SDL_Rect* currentClip = &spriteClips[ frame / 4 ];
	spriteSheetTexture->render( ( SCREEN_WIDTH - currentClip->w ) / 2, ( SCREEN_HEIGHT - currentClip->h ) / 2, currentClip );

	//Update screen
	SDL_RenderPresent( renderer );

	//Go to next frame
	++frame;

	//Cycle animation
	if( frame / 4 >= WALKING_ANIMATION_FRAMES ) {
		frame = 0;
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

	renderer = SDL_CreateRenderer( window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
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
	if( !spriteSheetTexture->loadFromFile("../../res/foo_animated.png") ) {
		printf( "Failed to load texture image!\n" );
		success = false;
	} else {
		int img_width=256;
		int img_height=205;
		int img_w_p=img_width/4;
		int img_h_p=img_height;
		int count=0;
		for(int j=0;j<img_height;j+=img_h_p)
			for(int i=0;i<img_width;i+=img_w_p,count++) {
				spriteClips[ count ].x =   i;
				spriteClips[ count ].y =   j;
				spriteClips[ count ].w = img_w_p;
				spriteClips[ count ].h = img_h_p;
			}

	}
	modulatedTexture = new LTexture(renderer);
	if( !modulatedTexture->loadFromFile("../../res/fadein.png") ) {
		printf( "Failed to load texture image!\n" );
		success = false;
	}else {
        modulatedTexture->setBlendMode( SDL_BLENDMODE_BLEND );
	}
	backgroundTexture = new LTexture(renderer);
	if( !backgroundTexture->loadFromFile("../../res/fadeout.png") ) {
		printf( "Failed to load texture image!\n" );
		success = false;
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

void Cmain::clear(){
	SDL_SetRenderDrawColor( renderer, 0xFF, 0xFF, 0xFF, 0xFF );
	SDL_RenderClear( renderer );
}
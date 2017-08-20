#include "../include/Cmain.h"
#include <iostream>
Cmain::Cmain() : SCREEN_WIDTH(640), SCREEN_HEIGHT(480) {
    window = NULL;
	screenSurface = NULL;
	
	helloWorld=NULL;
}

Cmain::~Cmain(){
	freeSurface(helloWorld);
	freeSurface(exitImage);
	
	SDL_DestroyWindow( window );
    SDL_Quit();
}

int Cmain::main(){
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
		//Handle events on queue
		while( SDL_PollEvent( &e ) != 0 ) {
			//User requests quit
			if( e.type == SDL_QUIT )
			{
				quit = true;
			}
		}

		//Apply the image
		SDL_BlitSurface( exitImage, NULL, screenSurface, NULL );
	
		//Update the surface
		SDL_UpdateWindowSurface( window );
	}


}

bool Cmain::init(){
	bool success = true;

	if( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
		printf( "SDL could not initialize! SDL_Error: %s\n", SDL_GetError() );
		success = false;
	} else {
		window = SDL_CreateWindow( "SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN );
		if( window == NULL ) {
			printf( "Window could not be created! SDL_Error: %s\n", SDL_GetError() );
			success = false;
		} else {
			//Get window surface
			screenSurface = SDL_GetWindowSurface( window );
		}
	}
	return success;
}

bool Cmain::loadMedia() {
	bool success = true;

	helloWorld = SDL_LoadBMP( "../../res/hello_world.bmp" );
	if( helloWorld == NULL ) {
		printf( "Unable to load image %s! SDL Error: %s\n", "hello_world.bmp", SDL_GetError() );
		success = false;
	}
	exitImage = SDL_LoadBMP( "../../res/x.bmp" );
	if( exitImage == NULL ) {
		printf( "Unable to load image %s! SDL Error: %s\n", "x.bmp", SDL_GetError() );
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

	return success;
}

void Cmain::freeSurface(SDL_Surface* s) {
	SDL_FreeSurface( s );
	s = NULL;
}

SDL_Surface* Cmain::loadSurface( std::string path ) {
	SDL_Surface* loadedSurface = SDL_LoadBMP( path.c_str() );
	if( loadedSurface == NULL ) {
		printf( "Unable to load image %s! SDL Error: %s\n", path.c_str(), SDL_GetError() );
	}
	return loadedSurface;
}
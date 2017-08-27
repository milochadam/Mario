#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <string>
class Cmain {
private:
    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;
    SDL_Window* window;
    SDL_Surface* screenSurface;

    SDL_Surface* helloWorld;
    SDL_Surface* exitImage;
    SDL_Surface* currentSurface;
    SDL_Surface* pngSurface;

    //The window renderer
    SDL_Renderer* renderer;

    //Current displayed texture
    SDL_Texture* texture;

    SDL_Event e;
    enum KeyPressSurfaces {
        KB_DEFAULT,
        KB_UP,
        KB_DOWN,
        KB_LEFT,
        KB_RIGHT,
        KB_TOTAL
    };
    SDL_Surface* kbSurfaces[KB_TOTAL];
public:
    Cmain();
    ~Cmain();
    bool init();
    bool loadMedia();
    int main();
    
private:
    SDL_Surface* loadSurface( std::string path );
    SDL_Texture* loadTexture( std::string path );
    void freeSurface( SDL_Surface* );
    void stretch( SDL_Surface* );
};

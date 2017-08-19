#include <SDL2/SDL.h>
class Cmain {
private:
    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;
    SDL_Window* window;
    SDL_Surface* screenSurface;

    SDL_Surface* helloWorld;
public:
    Cmain();
    ~Cmain();
    bool init();
    bool loadMedia();
    int main();
private:
    void freeSurface(SDL_Surface* );

};

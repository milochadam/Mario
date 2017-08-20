#include <SDL2/SDL.h>
#include <string>
class Cmain {
private:
    const int SCREEN_WIDTH;
    const int SCREEN_HEIGHT;
    SDL_Window* window;
    SDL_Surface* screenSurface;

    SDL_Surface* helloWorld;
    SDL_Surface* exitImage;

    SDL_Event e;
public:
    Cmain();
    ~Cmain();
    bool init();
    bool loadMedia();
    int main();
private:
    SDL_Surface* loadSurface(std::string path);
    void freeSurface(SDL_Surface* );

};

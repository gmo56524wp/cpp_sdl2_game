#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/Game.h"
#include "../include/TextureManager.h"


using namespace std;


Game* game = nullptr;

int main(int argc, const char * argv[]){

    const int FPS = 60;
    const int frameDelay = 1000/FPS;

    Uint32 frameStart;
    int frameTime;

    game  = new Game();
    game->init("game v1.0", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 2000, 1500, false);

    while(game->running()){

        frameStart = SDL_GetTicks();

        game->handleEvents();
        game->update();
        game->render();

        frameTime = SDL_GetTicks() - frameStart;

        if (frameDelay > frameTime){
            SDL_Delay(frameDelay - frameTime);
        }

    }

    game->clean();

    return 0;
}
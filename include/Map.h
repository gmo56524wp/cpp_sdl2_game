#ifndef MAP_H
#define MAP_H
# include "Game.h"



class Map
{
    public:
        Map();
        ~Map();

        void LoadMap(int arr[50][65]);
        void DrawMap();

    private:
        SDL_Rect src, dest;

        SDL_Texture* dirt;
        SDL_Texture* grass;
        SDL_Texture* water;

        int map[50][65];
};

#endif
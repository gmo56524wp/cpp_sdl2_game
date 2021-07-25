#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/Game.h"
#include "../include/TextureManager.h"
#include "../include/Map.h"
#include "../include/ECS/Components.h"
#include "../include/Vector2D.h"
#include "../include/Collision.h"

using namespace std;


Map* map;
Manager manager;

SDL_Renderer* Game::renderer = nullptr;
SDL_Event Game::event;

vector<ColliderComponent> Game::colliders;

auto& player(manager.addEntity());
auto& wall(manager.addEntity());

auto& tile0(manager.addEntity());
auto& tile1(manager.addEntity());
auto& tile2(manager.addEntity());

Game::Game() {}
Game::~Game() {}

void Game::init(const char *title, int xpos, int ypos, int width, int height, bool fullscreen)
{
    int flags = 0;
    if (fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }

    if (SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        cout << "Subsystem Initialized..." << endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);
        if (window)
        {
            cout << "Window Created!" << endl;
        }

        renderer = SDL_CreateRenderer(window, -1, 0);
        if (renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            cout << "Renderer Created!" << endl;
        }

        isRunning = true;
    }

    map = new Map();

    tile0.addComponent<TileComponent>(200, 200, 32, 32, 0);
    tile1.addComponent<TileComponent>(250, 250, 32, 32, 1);
    tile1.addComponent<ColliderComponent>("dirt");
    tile2.addComponent<TileComponent>(150, 150, 32, 32, 2);
    tile2.addComponent<ColliderComponent>("grass");

    player.addComponent<TransformComponent>(2);
    player.addComponent<SpriteComponent>("../res/character.PNG");
    player.addComponent<KeyboardController>();
    player.addComponent<ColliderComponent>("player");

    wall.addComponent<TransformComponent>(900.0f, 300.0f, 300, 20, 1);
    wall.addComponent<SpriteComponent>("../res/dirt.PNG");
    wall.addComponent<ColliderComponent>("wall");
}



void Game::handleEvents()
{
    SDL_PollEvent(&event);
    switch (event.type)
    {
    case SDL_QUIT:
        isRunning = false;
        break;
    default:
        break;
    }
}

void Game::update()
{
    manager.refresh();
    manager.update();
    if (Collision::AABB(player.getComponent<ColliderComponent>().collider, 
        wall.getComponent<ColliderComponent>().collider))
    {
        player.getComponent<TransformComponent>().scale = 1; 
        player.getComponent<TransformComponent>().velocity * -1;
        cout << "wall hit!" << endl;
    }

}

void Game::render()
{
    SDL_RenderClear(renderer);
    map->DrawMap();
    manager.draw();
    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
    cout << "Game Cleaned" << endl;
}
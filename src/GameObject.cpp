#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include "../include/Game.h"
#include "../include/TextureManager.h"
#include "../include/GameObject.h"


GameObject::GameObject(const char* texturesheet, int x, int y)
{
    objTexture = TextureManager::LoadTexture(texturesheet);

    xpos = x;
    ypos = y;
}

void GameObject::Update()
{
    xpos ++;
    ypos ++;

    srcRect.h = 520;
    srcRect.w = 520;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.h = srcRect.h *0.5;
    destRect.w = srcRect.w *0.5;
}

void GameObject::Render()
{
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}
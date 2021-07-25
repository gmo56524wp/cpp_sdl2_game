#ifndef TILECOMPONENT_H
#define TILECOMPONENT_H

#include "ECS.h"
#include "TransformComponent.h"
#include "SpriteComponent.h"
#include "SDL2/SDL.h"


class TileComponent : public Component
{
public:
    TransformComponent *transform;
    SpriteComponent *sprite;

    SDL_Rect tileRect;
    int tileID;
    char* path;

    TileComponent(int x, int y, int w, int h, int id)
    {
        tileRect.x = x;
        tileRect.y = y;
        tileRect.w = w;
        tileRect.h = h;
        tileID = id;

        switch (tileID)
        {
        case 0:
            path = "../res/water.PNG";
            break;
        case 1:
            path = "../res/dirt.PNG";
            break;
        case 2:
            path = "../res/dirt.PNG";
            break;
        default:
            break;

        }

    }

    void init() override
    {
        entity->addComponent<TransformComponent>((float)tileRect.x, (float)tileRect.y, tileRect.w, tileRect.h, 1);
        transform = &entity->getComponent<TransformComponent>();

        entity->addComponent<SpriteComponent>(path);
        sprite = &entity->getComponent<SpriteComponent>();
    }
 
};




#endif
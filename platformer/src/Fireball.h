#ifndef FIREBALL_H
#define FIREBALL_H

#include <iostream>
#include <ninage/engine/SDLOpenGL.h>
#include <ninage/engine/Entity.h>


class SDLOpenGL;
extern SDLOpenGL *game;

class Fireball: public Entity {
    public:
        Fireball(float x, float y);

        Sprite * standingSprite;
        Sprite * walkingSprite;

        bool onGround;

        void tick(float delta);
        void draw(float delta);
        void scene(float delta, Instance *instance);
};

#endif

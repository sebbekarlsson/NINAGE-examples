#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <scenengine/engine/SDLOpenGL.h>
#include <scenengine/engine/Entity.h>


class SDLOpenGL;
extern SDLOpenGL *game;

class Block: public Entity {
    public:
        Block(float x, float y);

        void tick(float delta);
        void draw(float delta);
        void scene(float delta, Instance *instance);
};

#endif

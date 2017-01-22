#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <ninage/engine/SDLOpenGL.h>
#include <ninage/engine/Entity.h>


class SDLOpenGL;
extern SDLOpenGL *game;

class Player: public Entity {
    public:
        Player(float x, float y);

        bool onGround;

        void tick(float delta);
        void draw(float delta);
        void scene(float delta, Instance *instance);
};

#endif

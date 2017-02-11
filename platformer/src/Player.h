#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <ninage/engine/Ninage.h>
#include <ninage/engine/Entity.h>


class Player: public Entity {
    public:
        Player(float x, float y);

        Sprite * standingSprite;
        Sprite * walkingSprite;

        bool onGround;

        void tick(float delta);
        void draw(float delta);
        void scene(float delta, Instance *instance);
};

#endif

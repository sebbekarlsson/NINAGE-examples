#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <ninage/Ninage.h>
#include <ninage/Entity.h>


class Player: public Entity {
    public:
        Player(float x, float y, float z);

        Sprite * standingSprite;
        Sprite * walkingSprite;

        bool onGround;

        void tick(float delta);
        void draw(float delta);
};

#endif

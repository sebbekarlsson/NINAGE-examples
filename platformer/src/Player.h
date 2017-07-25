#ifndef PLAYER_H
#define PLAYER_H

#include <iostream>
#include <ninage/Ninage.h>
#include <ninage/Entity.h>


class Player: public Entity {
    public:
        Player(float x, float y, float z);

        IllustrationStack * standingIll;
        IllustrationStack * walkingIll;

        bool onGround;

        void tick(float delta);
        void draw(float delta);
};

#endif

#ifndef BALL_H
#define BALL_H

#include <iostream>
#include <ninage/Ninage.h>
#include <ninage/Entity.h>


class Block: public Entity {
    public:
        Block(float x, float y);

        void tick(float delta);
        void draw(float delta);
};

#endif

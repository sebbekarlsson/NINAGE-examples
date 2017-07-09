#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <ninage/Ninage.h>
#include <ninage/Entity.h>


class Ninage;
extern Ninage *game;

class Block: public Entity {
    public:
        Block(float x, float y);

        void tick(float delta);
        void draw(float delta);
};

#endif

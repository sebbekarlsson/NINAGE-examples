#ifndef BLOCK_H
#define BLOCK_H

#include <iostream>
#include <ninage/engine/Ninage.h>
#include <ninage/engine/Entity.h>


class Ninage;
extern Ninage *game;

class Block: public Entity {
    public:
        Block(float x, float y);

        void tick(float delta);
        void draw(float delta);
        void scene(float delta, Instance *instance);
};

#endif

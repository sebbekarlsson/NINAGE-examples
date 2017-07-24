#ifndef GROUND_H
#define GROUND_H

#include <iostream>
#include <ninage/Ninage.h>
#include <ninage/Entity.h>


extern Ninage *app;

class Ground: public Entity {
    public:
        Ground(float x, float y, float z);

        void tick(float delta);
        void draw(float delta);
};

#endif


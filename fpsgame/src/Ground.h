#ifndef GROUND_H
#define GROUND_H


#include <ninage/Instance.h>


class Ground {
    public:
        Ground(float x, float y, float z);

        void tick(float delta);

        void draw(float delta);
};

#endif

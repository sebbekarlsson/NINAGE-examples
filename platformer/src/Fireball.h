#ifndef FIREBALL_H
#define FIREBALL_H

#include <iostream>
#include <ninage/Ninage.h>
#include <ninage/Entity.h>


class Ninage;
extern Ninage *app;

class Fireball: public Entity {
    public:
        Fireball(float x, float y);

        Sprite * standingSprite;
        Sprite * walkingSprite;

        bool onGround;

        void tick(float delta);
        void draw(float delta);
};

#endif

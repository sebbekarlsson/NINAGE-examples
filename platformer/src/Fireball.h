#ifndef FIREBALL_H
#define FIREBALL_H

#include <iostream>
#include <ninage/engine/Ninage.h>
#include <ninage/engine/Entity.h>


class Ninage;
extern Ninage *game;

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

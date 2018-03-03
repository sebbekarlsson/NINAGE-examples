#include "Block.h"
#include <random>


Block::Block(float x, float y, float z): Entity(x, y, z) {
    this->illustrationStack->addIllustration(
        app->loadIllustration("assets/grass.png", GL_RGBA)
    );
    this->centeredOrigo = false;
    this->interactive = true;
}

void Block::tick(float delta) {
}

void Block::draw(float delta) {
    this->illustrationStack->draw(delta);
    //this->collisionBox->draw(delta);
}

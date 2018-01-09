#include "Block.h"
#include <random>


Block::Block(float x, float y, float z): Entity(x, y, z) {
    this->illustrationStack->addIllustration(
        app->loadIllustration("assets/grass.png")
    );
    this->centeredOrigo = false;
    this->interactive = true;
}

void Block::tick(float delta) {
}

void Block::draw(float delta) {
    this->illustrationStack->draw(delta, GL_RGBA);
    //this->collisionBox->draw(delta);
}

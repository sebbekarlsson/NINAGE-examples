#include "Block.h"
#include <random>


Block::Block(float x, float y, float z): Entity(x, y, z) {
    this->illustrationStack->addIllustration(app->loadImage("assets/wuud.png"));
}

void Block::tick(float delta) {
    if (
            app->getMousePosition().x >= this->getX() &&
            app->getMousePosition().x <= this->getX() + this->collisionBox->width &&
            app->getMousePosition().y >= this->getY() &&
            app->getMousePosition().y <= this->getY() + this->collisionBox->height
    ) {
        app->getCurrentScene()->destantiate(this);
    }
}

void Block::draw(float delta) {
    this->illustrationStack->draw(delta);
    //this->collisionBox->draw(delta);
}

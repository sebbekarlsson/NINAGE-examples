#include "Block.h"
#include <random>


Block::Block(float x, float y): Entity(x, y) {
    this->sprite->addImage(app->loadImage("assets/grass.png"));
    this->centeredOrigo = false;
    this->interactive = true;
}

void Block::tick(float delta) {
}

void Block::draw(float delta) {
    this->sprite->draw(delta);
    //this->collisionBox->draw(delta);
}

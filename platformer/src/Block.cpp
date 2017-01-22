#include "Block.h"
#include <random>


Block::Block(float x, float y): Entity(x, y) {
    this->sprite->addImage(game->loadImage("assets/grass.png"));
    this->centeredOrigo = false;
    this->interactive = true;
}

void Block::tick(float delta) {
    if (
            game->getMousePosition().x >= this->x &&
            game->getMousePosition().x <= this->x + this->collisionBox->width &&
            game->getMousePosition().y >= this->y &&
            game->getMousePosition().y <= this->y + this->collisionBox->height
    ) {
        game->getCurrentScene()->destantiate(this);
    }
}

void Block::draw(float delta) {
    this->sprite->draw(delta);
    //this->collisionBox->draw(delta);
}

void Block::scene(float delta, Instance * instance) {

}
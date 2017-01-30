#include "Block.h"
#include <random>


Block::Block(float x, float y): Entity(x, y) {
    this->sprite->addImage(game->loadImage("assets/wuud.png"));
}

void Block::tick(float delta) {
    if (
            game->getMousePosition().x >= this->getX() &&
            game->getMousePosition().x <= this->getX() + this->collisionBox->width &&
            game->getMousePosition().y >= this->getY() &&
            game->getMousePosition().y <= this->getY() + this->collisionBox->height
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

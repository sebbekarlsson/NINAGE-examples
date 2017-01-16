#include "Block.h"
#include <random>


Block::Block(float x, float y): Entity(x, y) {
    this->sprite->addImage(game->loadImage("assets/wuud.png"));
    //this->centeredOrigo = true;
    //this->friction = 0.001f;
}

void Block::tick(float delta) {
    //this->updatePhysics(delta);
    

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

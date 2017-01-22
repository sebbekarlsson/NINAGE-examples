#include "Player.h"
#include "Block.h"
#include <random>


Player::Player(float x, float y): Entity(x, y) {
    this->sprite->addImage(game->loadImage("assets/p2_stand.png"));
    this->centeredOrigo = false;
    this->interactive = true;
    this->onGround = false;
}

void Player::tick(float delta) {
    this->onGround = false;
    
    this->updatePhysics(delta);

    /*if (!this->onGround) {
      this->dy += 0.1f;
      } else {
    //this->dy -= 0.1f;
    }*/

    Scene * scene = game->getCurrentScene();

    float py = 0.0f;

    for (std::vector<Instance*>::iterator it2 = scene->instances->begin(); it2 != scene->instances->end();) {
        if(dynamic_cast<Block*>((*it2)) == NULL) { ++it2; continue; }
        //if ((*it) == (*it2) || (*it)->interactive == false) { ++it2; continue; }

        //(*it2)->scene(delta, (*it));
        
        if (/*this->y+this->collisionBox->height >= (*it2)->y &&*/ this->intersectsWith(delta, (Entity*)(*it2))) {
            this->onGround = true;
            py = (*it2)->y - this->collisionBox->height; 
        }

        ++it2;
    }

    if (!this->onGround) {
        this->dy += 0.1f;
    } else {
        this->dy = 0.0f;
        this->y = py;
    }
    

    if (game->keyboardDown(SDL_SCANCODE_LEFT)) {
        this->addForce(180.0f, 0.05f);
    }
    if (game->keyboardDown(SDL_SCANCODE_RIGHT)) {
        this->addForce(0.0f, 0.05f);
    }
    if (game->keyboardDown(SDL_SCANCODE_UP) && this->onGround) {
        this->addForce(270.0f, 2.0f);
    }

    scene->camera->x = (this->x - game->WIDTH);

    //delete scene;
}

void Player::draw(float delta) {
    this->sprite->draw(delta);
    //this->collisionBox->draw(delta);
}

void Player::scene(float delta, Instance * instance) {


    if (this->intersectsWith(delta, (Entity*) instance)) {
        this->onGround = true;
    }
}

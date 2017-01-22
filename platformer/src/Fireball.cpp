#include "Fireball.h"
#include "Block.h"
#include <random>
#include <algorithm>


Fireball::Fireball(float x, float y): Entity(x, y) {
    this->sprite->addImage(game->loadImage("assets/fireball.png"));

    this->centeredOrigo = false;
    this->interactive = true;
    this->onGround = false;
    this->sprite->animationDelay = 0.30f;
}

void Fireball::tick(float delta) {
    this->onGround = false;
    
    this->updatePhysics(delta);
    
    Scene& scene = *game->getCurrentScene();

    float py = 0.0f;

    for (std::vector<Instance*>::iterator it2 = scene.instances->begin(); it2 != scene.instances->end();) {
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
}

void Fireball::draw(float delta) {
    this->sprite->draw(delta);
    //this->collisionBox->draw(delta);
}

void Fireball::scene(float delta, Instance * instance) {
    if (this->intersectsWith(delta, (Entity*) instance)) {
        this->onGround = true;
    }
}
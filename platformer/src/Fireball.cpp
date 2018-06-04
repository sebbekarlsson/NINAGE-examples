#include "Fireball.h"
#include "Block.h"
#include <random>


Fireball::Fireball(float x, float y, float z): Entity(x, y, z) {
    this->illustrationStack->addIllustration(
        app->loadIllustration("assets/fireball.png", GL_RGBA)
    );

    this->centeredOrigo = false;
    this->interactive = true;
    this->onGround = false;
    this->illustrationStack->animationDelay = 0.30f;
}

void Fireball::tick(float delta) {
    this->onGround = false;
   
    this->syncCollisionBoxWithIllustrationStack(delta); 
    this->updatePhysics();
    
    Scene& scene = *app->getCurrentScene();

    float py = 0.0f;

    for (std::vector<Instance*>::iterator it2 = scene.instances->begin(); it2 != scene.instances->end();) {
        if(dynamic_cast<Block*>((*it2)) == NULL) { ++it2; continue; }
        //if ((*it) == (*it2) || (*it)->interactive == false) { ++it2; continue; }

        //(*it2)->scene(delta, (*it));
        
        if (/*this->y+this->collisionBox->height >= (*it2)->y &&*/ this->intersectsWith((Entity*)(*it2))) {
            this->onGround = true;
            py = (*it2)->getY() - this->collisionBox->height; 
        }

        ++it2;
    }

    if (!this->onGround) {
        this->dy += 0.1f;
    } else {
        this->dy = 0.0f;
        this->position->y = py;
    }
}

void Fireball::draw(float delta) {
    this->illustrationStack->draw(delta);
    //this->collisionBox->draw(delta);
}

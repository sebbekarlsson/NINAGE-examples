#include "Player.h"
#include "Block.h"
#include "Fireball.h"
#include <random>
#include <algorithm>


Player::Player(float x, float y): Entity(x, y) {
    this->walkingSprite = new Sprite();
    this->standingSprite = new Sprite();

    int walkFrames = 11;

    for (int i = 1; i <= walkFrames; i++) {
        std::string number = std::to_string(i);
        
        if (i < 10) { number = "0" + number; }

        this->walkingSprite->addImage(game->loadImage(("assets/player/p2_walk" + number + ".png")));
    }

    this->standingSprite->addImage(game->loadImage("assets/p2_stand.png"));

    this->sprite = this->standingSprite;

    this->centeredOrigo = false;
    this->interactive = true;
    this->onGround = false;
    this->sprite->animationDelay = 0.30f;
}

void Player::tick(float delta) {
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
    
    if (game->keyboardDown(SDL_SCANCODE_LEFT)) {
        this->addForce(180.0f, 0.05f);
    }
    if (game->keyboardDown(SDL_SCANCODE_RIGHT)) {
        this->addForce(0.0f, 0.05f);
    }
    if (game->keyboardDown(SDL_SCANCODE_UP) && this->onGround) {
        this->addForce(270.0f, 2.0f);
    }
    if (game->keyboardDown(SDL_SCANCODE_SPACE)) {
        Fireball* ball = new Fireball(this->x, this->y);

        ball->addForce(270.0f, 1.0f);
        game->getCurrentScene()->instantiate(ball);

        //this->addForce(270.0f, 2.0f);
    }

    float camX = this->x - game->getWidth() / 2;
    float camY = this->y - game->getHeight() / 2;

    float distance =\
        std::max(
            (scene.camera->x + game->getWidth() / 2),
            (this->x + this->collisionBox->width / 2)
            ) -
        std::min(
            (scene.camera->x + game->getWidth() / 2),
            (this->x + this->collisionBox->width / 2)
        );

    if (distance > 250.0f) {
        if (scene.camera->x < camX) {
            if (scene.camera->x + (0.2f * delta) > camX) {
                scene.camera->dx = 0.0f;
            } else {
                scene.camera->dx += 0.2f;
            }
        }

        if (scene.camera->x > camX) {
            if (scene.camera->x - (0.2f * delta) < camX) {
                scene.camera->dx = 0.0f;
            } else {
                scene.camera->dx -= 0.2f;
            }
        }
    }

    scene.camera->y = camY;

    if (dx > 0 || dx < 0) {
        this->sprite = this->walkingSprite;
    } else {
        this->sprite = this->standingSprite;
    }
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

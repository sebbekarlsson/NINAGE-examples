#include "Player.h"
#include "Block.h"
#include "Fireball.h"
#include <random>
#include <algorithm>


Player::Player(float x, float y, float z): Entity(x, y, z) {
    this->walkingIll = new IllustrationStack();
    this->standingIll = new IllustrationStack();

    int walkFrames = 11;

    for (int i = 1; i <= walkFrames; i++) {
        std::string number = std::to_string(i);
        
        if (i < 10) { number = "0" + number; }

        this->walkingIll->addIllustration(
            app->loadIllustration(("assets/player/p2_walk" + number + ".png"))
        );
    }

    this->standingIll->addIllustration(
        app->loadIllustration("assets/p2_stand.png")
    );

    this->illustrationStack = this->standingIll;

    this->centeredOrigo = false;
    this->interactive = true;
    this->onGround = false;
    this->illustrationStack->animationDelay = 0.30f;
}

void Player::tick(float delta) {
    this->onGround = false;
    this->syncCollisionBoxWithIllustrationStack(delta);
    this->updatePhysics(delta);
    
    Scene& scene = *app->getCurrentScene();

    float py = 0.0f;

    for (std::vector<Instance*>::iterator it2 = scene.instances->begin(); it2 != scene.instances->end();) {
        if(dynamic_cast<Block*>((*it2)) == NULL) { ++it2; continue; }
        //if ((*it) == (*it2) || (*it)->interactive == false) { ++it2; continue; }

        //(*it2)->scene(delta, (*it));
        
        if (this->intersectsWith(delta, (Entity*)(*it2))) {
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
    
    if (app->keyboardDown(SDL_SCANCODE_LEFT)) {
        this->addForce(180.0f, 0.05f, Viewmode::D2);
    }
    if (app->keyboardDown(SDL_SCANCODE_RIGHT)) {
        this->addForce(0.0f, 0.05f, Viewmode::D2);
    }
    if (app->keyboardDown(SDL_SCANCODE_UP) && this->onGround) {
        this->addForce(270.0f, 2.0f, Viewmode::D2);
    }
    if (app->keyboardDown(SDL_SCANCODE_SPACE)) {
        Fireball* ball = new Fireball(this->getX(), this->getY(), 0);

        ball->addForce(270.0f, 1.0f, Viewmode::D2);
        app->getCurrentScene()->instantiate(ball);

        //this->addForce(270.0f, 2.0f);
    }

    float camX = this->getX() - app->getWidth() / 2;
    float camY = this->getY() - app->getHeight() / 2;

    float distance =\
        std::max(
            (scene.camera->getX() + app->getWidth() / 2),
            (this->getX() + this->collisionBox->width / 2)
            ) -
        std::min(
            (scene.camera->getX() + app->getWidth() / 2),
            (this->getX() + this->collisionBox->width / 2)
        );

    if (distance > 250.0f) {
        if (scene.camera->getX() < camX) {
            if (scene.camera->getX() + (0.2f * delta) > camX) {
                scene.camera->dx = 0.0f;
            } else {
                scene.camera->dx += 0.2f;
            }
        }

        if (scene.camera->getX() > camX) {
            if (scene.camera->getX() - (0.2f * delta) < camX) {
                scene.camera->dx = 0.0f;
            } else {
                scene.camera->dx -= 0.2f;
            }
        }
    }

    scene.camera->position->y = camY;

    if (dx > 0 || dx < 0) {
        this->illustrationStack = this->walkingIll;
    } else {
        this->illustrationStack = this->standingIll;
    }
}

void Player::draw(float delta) {
    this->illustrationStack->draw(delta);
    //this->collisionBox->draw(delta);
}

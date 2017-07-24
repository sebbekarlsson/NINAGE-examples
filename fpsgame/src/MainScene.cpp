#include "MainScene.h"
#include "Ground.h"
#include <random>


float xRotated = 0.5f;
float yRotated = 1.0f;
float zRotated = 2.5f;
bool onGround = false;
float py = 0.0f;

MainScene::MainScene(): Scene() {
    this->texture0 = app->loadImage("assets/unnamed.png");
}

void MainScene::init(float delta) {
    SDL_ShowCursor(SDL_DISABLE);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    camera->yfriction = 0.0001f;

    for (int xx = 0; xx < 16; xx++) {
        for (int yy = -20; yy < 16; yy++) {
            Ground* ground = new Ground(xx * 2, -2.2f, yy * 2);
            this->instantiate(ground);
        }
    }
}

void MainScene::tick(float delta) {
    this->tickDefault(delta);
    camera->updatePhysics(delta);

    onGround = false;
    py = 0.0f;
    

    if (app->keyboardDown(SDL_SCANCODE_W)) {
        this->camera->position->x += sin(EngineMath::toRadians(this->camera->yrotation)) * 0.08f;
        this->camera->position->z -= cos(EngineMath::toRadians(this->camera->yrotation)) * 0.08f;
    }

    if (app->keyboardDown(SDL_SCANCODE_S)) {
        this->camera->position->x += sin(EngineMath::toRadians(this->camera->yrotation - 180.0f)) * 0.08f;
        this->camera->position->z -= cos(EngineMath::toRadians(this->camera->yrotation - 180.0f)) * 0.08f;
    }

    if (app->keyboardDown(SDL_SCANCODE_A)) {
        this->camera->position->x += sin(EngineMath::toRadians(this->camera->yrotation - 90.0f)) * 0.08f;
        this->camera->position->z -= cos(EngineMath::toRadians(this->camera->yrotation - 90.0f)) * 0.08f;
    }

    if (app->keyboardDown(SDL_SCANCODE_D)) {
        this->camera->position->x += sin(EngineMath::toRadians(this->camera->yrotation + 90.0f)) * 0.08f;
        this->camera->position->z -= cos(EngineMath::toRadians(this->camera->yrotation + 90.0f)) * 0.08f;
    }

    for (std::vector<Instance*>::iterator it2 = instances->begin(); it2 != instances->end();) {
        if(dynamic_cast<Ground*>((*it2)) == NULL) { ++it2; continue; }
        //if ((*it) == (*it2) || (*it)->interactive == false) { ++it2; continue; }

        //(*it2)->scene(delta, (*it));
        
        if (camera->intersectsWith(delta, (Entity*)(*it2))) {
            onGround = true;
            py = ((*it2)->getY() + (*it2)->collisionBox->height + camera->collisionBox->height);
        }

        ++it2;
    }

    if (!onGround) {
        camera->dy -= 0.002f;
    } else {
        camera->dy = 0.0f;
        camera->position->y = py;
    }

    if (app->keyboardDown(SDL_SCANCODE_SPACE) && onGround) {
        camera->addForce(90.0f, 0.03f);
    }
}

void MainScene::draw(float delta) {
    this->drawDefault(delta);
}

void MainScene::mouseMoveEvent(
    int &mouseX,
    int &mouseY,
    int &deltaMouseX,
    int &deltaMouseY
) {
    this->camera->xrotation += (deltaMouseY * 0.25f);
    this->camera->yrotation += (deltaMouseX * 0.25f);
}

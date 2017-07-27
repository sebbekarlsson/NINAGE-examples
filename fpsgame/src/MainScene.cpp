#include "MainScene.h"
#include "Ground.h"
#include <random>


bool onGround = false;

float camprevx = 0.0f;
float camprevy = 0.0f;
float camprevz = 0.0f;

float distance_to_x0 = 0;
float distance_to_x1 = 0;

float distance_to_z0 = 0;
float distance_to_z1 = 0;

float distance_to_y1 = 0;

MainScene::MainScene(): Scene() {
}

void MainScene::init(float delta) {
    SDL_ShowCursor(SDL_DISABLE);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    camera->yfriction = 0.0001f;
    camera->position->y = 30.0f;

    for (int xx = 0; xx < 16; xx++) {
        for (int zz = 0; zz < 16; zz++) {
            Ground* ground = new Ground(xx, -3.0f, zz);
            this->instantiate(ground);
        }
    }

    Ground* ground = new Ground(4.0f, -2.0f, 4.0f);
    this->instantiate(ground);

    Ground* ground0 = new Ground(4.0f, -1.0f, 4.0f);
    this->instantiate(ground0);

    Ground* ground1 = new Ground(4.0f, 0.0f, 4.0f);
    this->instantiate(ground1);


    Ground* ground2 = new Ground(6.0f, -2.0f, 4.0f);
    this->instantiate(ground2);

    Ground* ground3 = new Ground(6.0f, -1.0f, 4.0f);
    this->instantiate(ground3);

    Ground* ground4 = new Ground(6.0f, 0.0f, 4.0f);
    this->instantiate(ground4);
}

void MainScene::tick(float delta) {
    this->tickDefault(delta);
    onGround = false;

    camera->updatePhysics(delta);

    camprevx = camera->position->x;
    camprevz = camera->position->z;
    camprevy = camera->position->y;

    distance_to_x0 = 0.0f;
    distance_to_x1 = 0.0f;
    distance_to_y1 = 0.0f;
    distance_to_z0 = 0.0f;
    distance_to_z1 = 0.0f;

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

            if (camera->position->y - camera->collisionBox->height < (*it2)->position->y) {
                distance_to_x0 = std::max((camprevx + camera->collisionBox->width), (*it2)->position->x) - std::min((camprevx + camera->collisionBox->width), (*it2)->position->x);
                distance_to_x1 = std::max((*it2)->position->x + (*it2)->collisionBox->width, camprevx) - std::min((*it2)->position->x + (*it2)->collisionBox->width, camprevx);

                distance_to_z0 = std::max((camprevz + camera->collisionBox->depth), (*it2)->position->z) - std::min((camprevz + camera->collisionBox->depth), (*it2)->position->z);
                distance_to_z1 = std::max((*it2)->position->z + (*it2)->collisionBox->depth, camprevz) - std::min((*it2)->position->z + (*it2)->collisionBox->depth, camprevz);

            }

            if (camprevy > (*it2)->position->y - (*it2)->collisionBox->height) {
                distance_to_y1 = std::max((*it2)->position->y - (*it2)->collisionBox->height, camprevy) - std::min((*it2)->position->y - (*it2)->collisionBox->height, camprevy);
            }
        }

        ++it2;
    }

    if (distance_to_x0 > 0.0f || distance_to_x1 > 0.0f) {
        camera->position->x = camprevx;
    }

    if (distance_to_z0 > 0.0f || distance_to_z1 > 0.0f) {
        camera->position->z = camprevz;
    }

    if (distance_to_y1 <= 0.0f) {
        onGround = false;
        camera->position->y = camprevy;
    }

    if (!onGround) {
        camera->dy -= 0.0007f;
    } else {
        camera->dy = 0.0f;
        camera->position->y = camprevy;
    }

    if (app->keyboardDown(SDL_SCANCODE_SPACE) && onGround) {
        camera->addForce(90.0f, 0.01f);
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

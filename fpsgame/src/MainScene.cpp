#include "MainScene.h"
#include "Ground.h"
#include <random>
#include <ninage/ModelLoader.h>
#include <glm/glm.hpp>


bool onGround = false;

float accleration = 0.08f;
float acceleration_up = 0.01f;

float camprevx = 0.0f;
float camprevy = 0.0f;
float camprevz = 0.0f;

float distance_to_y1 = 0;

float modelRot = 0.0f;

Illustration* modelIl = app->loadIllustration("assets/metrocop_sheet.tga", GL_RGBA);
Model3D *m;

MainScene::MainScene(): Scene() {}

void MainScene::init(float delta) {
    m = ModelLoader::load("assets/Police.obj");
    SDL_ShowCursor(SDL_DISABLE);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    camera->yfriction = 0.0001f;
    camera->position->y = 30.0f;
    camera->position->x += 0.5f;
    camera->position->z += 0.5f;

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

    Ground* ground5 = new Ground(7.0f, -2.0f, 4.0f);
    this->instantiate(ground5);

    Ground* ground6 = new Ground(6.0f, 0.0f, 5.0f);
    this->instantiate(ground6);
}

void MainScene::tick(float delta) {
    this->tickDefault(delta);

    if (modelRot < 360) {
        modelRot += 0.1f;
    } else {
        modelRot = 0.0f;
    }

    onGround = false;

    camera->updatePhysics(delta);

    if (app->keyboardDown(SDL_SCANCODE_W)) {
        this->camera->position->x += sin(EngineMath::toRadians(this->camera->yrotation)) * accleration;
        this->camera->position->z -= cos(EngineMath::toRadians(this->camera->yrotation)) * accleration;
    }

    if (app->keyboardDown(SDL_SCANCODE_S)) {
        this->camera->position->x += sin(EngineMath::toRadians(this->camera->yrotation - 180.0f)) * accleration;
        this->camera->position->z -= cos(EngineMath::toRadians(this->camera->yrotation - 180.0f)) * accleration;
    }

    if (app->keyboardDown(SDL_SCANCODE_A)) {
        this->camera->position->x += sin(EngineMath::toRadians(this->camera->yrotation - 90.0f)) * accleration;
        this->camera->position->z -= cos(EngineMath::toRadians(this->camera->yrotation - 90.0f)) * accleration;
    }

    if (app->keyboardDown(SDL_SCANCODE_D)) {
        this->camera->position->x += sin(EngineMath::toRadians(this->camera->yrotation + 90.0f)) * accleration;
        this->camera->position->z -= cos(EngineMath::toRadians(this->camera->yrotation + 90.0f)) * accleration;
    }

    for (std::vector<Instance*>::iterator it2 = instances->begin(); it2 != instances->end();) {
        if(dynamic_cast<Ground*>((*it2)) == NULL) { ++it2; continue; }

        if (camera->intersectsWith(delta, (Entity*)(*it2))) {

            float cam_height = camera->collisionBox->height;
            float cam_width = camera->collisionBox->width;
            float box_size = (*it2)->collisionBox->width;

            if (
                camera->position->x + (cam_width / 2) - 0.1f >= (*it2)->position->x &&
                camera->position->x - (cam_width / 2) + 0.1f <= (*it2)->position->x + box_size - 0.1f && 

                camera->position->z + (cam_width / 2) - 0.1f >= (*it2)->position->z &&
                camera->position->z - (cam_width / 2) + 0.1f <= (*it2)->position->z + box_size - 0.1f
            ) {
                camera->position->y = camprevy;
                camera->dy = 0.0f;
                
                if (camera->position->y > (*it2)->position->y) {
                    onGround = true;
                }
            }

            if (
                camera->position->y - cam_height + 0.1f <= (*it2)->position->y &&
                camera->position->y >= (*it2)->position->y - box_size + 0.1f
            ) {
                camera->position->x = camprevx;
                camera->position->z = camprevz;
            }
        }

        ++it2;
    }

    if (!onGround) {
        camera->dy -= 0.0007f;
    } else {
        if (app->keyboardDown(SDL_SCANCODE_SPACE) && onGround) {
            camera->addForce(90.0f, acceleration_up, Viewmode::D2);
        }
    }

    camprevx = camera->position->x;
    camprevz = camera->position->z;
    camprevy = camera->position->y;
}

void MainScene::draw(float delta) {
    this->drawDefault(delta);

    glPushMatrix();
    glTranslatef(5.0f, -3.0f, 2.0f);
    glRotatef(modelRot, 0.0f, 1.0f, 0.0f);
    glScalef(0.023f, 0.023f, 0.023f);
    modelIl->bind();
    m->draw();
    glPopMatrix();
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

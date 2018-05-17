#include "MainScene.h"
#include "Ground.h"
#include <random>
#include <ninage/ModelLoader.h>
#include <glm/glm.hpp>


bool onGround = false;
float acceleration = 0.08f;
float acceleration_up = 0.01f;
float camprevx = 0.0f;
float camprevy = 0.0f;
float camprevz = 0.0f;
float modelRot = 0.0f;

Illustration* modelIl = app->loadIllustration(
    "assets/metrocop_sheet.tga",
    GL_RGBA
);

Model3D *m;

/**
 * Moves the camera in a direction with an acceleration
 *
 * @param Camera* camera - camera to move
 * @param float direction - direction to move
 * @param float acceleration - the acceleration
 */
void moveCamera(Camera* camera, float direction, float acceleration) {
    float radians = EngineMath::toRadians(direction);

    camera->position->x += sin(radians) * acceleration;
    camera->position->z -= cos(radians) * acceleration;
};

MainScene::MainScene(): Scene() {}

void MainScene::init(float delta) {
    m = ModelLoader::load("assets/Police.obj");
    SDL_ShowCursor(SDL_DISABLE);
    SDL_SetRelativeMouseMode(SDL_TRUE);

    camera->yfriction = 0.0001f;
    camera->position->y = 30.0f;
    camera->position->x += 0.5f;
    camera->position->z += 0.5f;

    // place out ground so that we have something to walk on
    for (int xx = 0; xx < 16; xx++) {
        for (int zz = 0; zz < 16; zz++) {
            Ground* ground = new Ground(xx, -3.0f, zz);
            this->instantiate(ground);
        }
    }

    // placing out some random boxes
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

    onGround = false;
    
    camera->updatePhysics(delta);

    if (modelRot < 360)
        modelRot += 0.1f;
    else
        modelRot = 0.0f;

    // move forward
    if (app->keyboardDown(SDL_SCANCODE_W)) {
        moveCamera(
            this->camera,
            this->camera->yrotation,
            acceleration
        );
    }

    // move backwards
    if (app->keyboardDown(SDL_SCANCODE_S)) {
        moveCamera(
            this->camera,
            this->camera->yrotation - 180.0f, acceleration
        );
    }

    // move left
    if (app->keyboardDown(SDL_SCANCODE_A)) {
        moveCamera(
            this->camera,
            this->camera->yrotation - 90.0f,
            acceleration
        );
    }

    // move right
    if (app->keyboardDown(SDL_SCANCODE_D)) {
        moveCamera(
            this->camera,
            this->camera->yrotation + 90.0f,
            acceleration
        );
    }

    // Collision detection
    for (std::vector<Instance*>::iterator it2 = instances->begin(); it2 != instances->end();) {
        if(dynamic_cast<Ground*>((*it2)) == NULL) { ++it2; continue; }

        if (camera->intersectsWith((Entity*)(*it2))) {
            float cam_height = camera->collisionBox->height;
            float cam_width = camera->collisionBox->width;
            float box_size = (*it2)->collisionBox->width;
            float margin = 0.0f;

            if (
                camera->position->x + (cam_width / 2) - margin >= (*it2)->position->x &&
                camera->position->x - (cam_width / 2) + margin <= (*it2)->position->x + box_size - margin && 

                camera->position->z + (cam_width / 2) - margin >= (*it2)->position->z &&
                camera->position->z - (cam_width / 2) + margin <= (*it2)->position->z + box_size - margin
            ) {
                camera->position->y = camprevy;
                camera->dy = 0.0f;
                
                if (camera->position->y > (*it2)->position->y)
                    onGround = true;
            }

            if (
                camera->position->y - cam_height + 0.1f <= (*it2)->position->y &&
                camera->position->y >= (*it2)->position->y - box_size + 0.1f
            ) {
                /*
                 * set the velocity component along that axis to zero.
                 * set the position component along that axis to the “just exactly touching” distance,
                 * which is easy to calculate from the dimensions of the AABBs.
                 */
                glm::vec3* firstCollisionNorm;
                
                float _x = std::max(camera->position->x, (*it2)->position->x);
                float _z = std::max(camera->position->z, (*it2)->position->z);

                float xx = std::min((camera->position->x - cam_width / 2) + cam_width, (*it2)->position->x + box_size);
                float zz = std::min((camera->position->z - cam_width / 2) + cam_width, (*it2)->position->z + box_size);
                
                float ay = box_size;
                float ax = xx - _x;
                float az = zz - _z;

                float sx = ((*it2)->position->x + (box_size / 2)) < camera->position->x ? -1.0f : 1.0f;
                float sy = ((*it2)->position->y - (box_size / 2)) < (camera->position->y - (cam_height / 2)) ? -1.0f : 1.0f;
                float sz = ((*it2)->position->z + (box_size / 2)) < camera->position->z ? -1.0f : 1.0f;

                if (ax <= ay && ax <= az) {
                    firstCollisionNorm = new glm::vec3(sx * -1, 0.0f, 0.0f);
                } else if (ay <= az) {
                    firstCollisionNorm = new glm::vec3(0.0f, sy * -1, 0.0f);
                } else {
                    firstCollisionNorm = new glm::vec3(0.0f, 0.0f, sz * -1);
                }

                camera->position->x += firstCollisionNorm->x * acceleration;
                camera->position->z += firstCollisionNorm->z * acceleration;
            }
        }

        ++it2;
    }

    if (!onGround)
        camera->dy -= 0.0007f; // gravity
    else if (app->keyboardDown(SDL_SCANCODE_SPACE) && onGround)
        camera->addForce(90.0f, acceleration_up, Viewmode::D2); // jump

    // remember old camera position
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

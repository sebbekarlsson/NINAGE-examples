#include "MainScene.h"
#include "Ground.h"
#include <random>


float xRotated = 0.5f;
float yRotated = 1.0f;
float zRotated = 2.5f;

MainScene::MainScene(): Scene() {
    this->texture0 = app->loadImage("assets/unnamed.png");
}

void MainScene::init(float delta) {
    for (int xx = 0; xx < 64; xx++) {
        for (int yy = -20; yy < 64; yy++) {
            Ground* ground = new Ground(xx, -2.2f, yy);
            this->instantiate(ground);
        }
    }
}

void MainScene::tick(float delta) {
    this->tickDefault(delta);
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

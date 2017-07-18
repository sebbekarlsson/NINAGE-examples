#include "MainScene.h"
#include <random>


MainScene::MainScene(): Scene() {}

void MainScene::init(float delta) {
}

void MainScene::tick(float delta) {
    this->tickDefault(delta);
}

void MainScene::draw(float delta) {
    this->drawDefault(delta);
}

#include "MainScene.h"
#include "Block.h"
#include "Player.h"
#include <random>


MainScene::MainScene(): Scene() {}

void MainScene::init(float delta) {
    for (int x = 0; x < 10; x++) {
        this->instantiate(new Block(x * 70, app->getHeight() - 70.0f, 0));
    }

    for (int x = 11; x < (11+10); x++) {
        this->instantiate(new Block(x * 70, app->getHeight() + (70*2), 0));
    }

    this->instantiate(new Player(70, app->getHeight() - (70 * 3), 0));
}

void MainScene::tick(float delta) {
    this->tickDefault(delta);
}

void MainScene::draw(float delta) {
    this->drawDefault(delta);
}

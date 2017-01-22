#include "MainScene.h"
#include "Block.h"
#include "Player.h"
#include <random>


MainScene::MainScene(): Scene() {}

void MainScene::init(float delta) {
    for (int x = 0; x < 10; x++) {
        this->instantiate(new Block(x * 70, game->HEIGHT));
    }

    for (int x = 11; x < (11+10); x++) {
        this->instantiate(new Block(x * 70, game->HEIGHT + (70*2)));
    }

    this->instantiate(new Player(70, game->HEIGHT - 120.0f));
}

void MainScene::tick(float delta) {
    this->tickDefault(delta);
}

void MainScene::draw(float delta) {
    this->drawDefault(delta);
}

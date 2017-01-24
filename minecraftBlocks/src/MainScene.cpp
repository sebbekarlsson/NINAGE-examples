#include "MainScene.h"
#include "Block.h"
#include <random>


MainScene::MainScene(): Scene() {}

void MainScene::init(float delta) {
    int xStart = (game->getWidth() / 2) / 32;
    int yStart = (game->getHeight() / 2) / 32;

    for (int x = xStart; x < xStart + 32; x++) {
        for (int y = yStart; y < yStart + 32; y++) {
            this->instantiate(new Block(x * 16, y * 16));
        }
    }
}

void MainScene::tick(float delta) {
    this->tickDefault(delta);
}

void MainScene::draw(float delta) {
    this->drawDefault(delta);
}

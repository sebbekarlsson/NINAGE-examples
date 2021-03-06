#include <ninage/Ninage.h>
#include <ninage/Viewmode.h>
#include "MainScene.h"


Ninage *app;
const Uint8 *state = SDL_GetKeyboardState(NULL);

void Ninage::main() {
    this->TITLE = "FPS Game";

    MainScene* scene = new MainScene();
    this->addScene(scene);
}

int main(int argc, char* args[]) {
    app = new Ninage();
    
    app->setViewmode(Viewmode::D3);

    return app->run();
}

#include <ninage/Ninage.h>
#include "MainScene.h"


Ninage *app;
const Uint8 *state = SDL_GetKeyboardState(NULL);

void Ninage::main() {
    MainScene* scene = new MainScene();

    this->addScene(scene);
}

int main(int argc, char* args[]) {
    app = new Ninage();
    
    app->setViewMode(1);

    return app->run();
}

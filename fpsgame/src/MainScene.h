#ifndef TESTSCENE_H
#define TESTSCENE_H

#include <ninage/Ninage.h>
#include <ninage/Scene.h>
#include <ninage/SpriteImage.h>


extern Ninage *app;

class MainScene: public Scene {
    public:
        MainScene();

        void tick(float delta);
        void draw(float delta);
        void init(float delta);
        void mouseMoveEvent(
            int &mouseX,
            int &mouseY,
            int &deltaMouseX,
            int &deltaMouseY
        );

        SpriteImage* texture0;
};

#endif

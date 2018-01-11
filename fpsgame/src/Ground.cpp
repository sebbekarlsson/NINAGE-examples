#include "Ground.h"
#include <random>


Ground::Ground(float x, float y, float z): Entity(x, y, z) {
    this->illustrationStack->addIllustration(
        app->loadIllustration("assets/crate.png", GL_RGBA)
    );

    this->collisionBox->setSize(1.0f, 1.0f, 1.0f);
}

void Ground::tick(float delta) {

}

void Ground::draw(float delta) {
    //this->sprite->draw(delta);
    //this->collisionBox->draw(delta);

    this->illustrationStack->getCurrentIllustration()->bind();


    glPushMatrix();
    glColor3f(1.0f, 1.0f, 1.0f);

    glBegin(GL_QUADS);
    // Front Face
    glNormal3f(0.0f, 0.0f, 1.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f,  1.0f);	// Bottom Left
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, 0.0f,  1.0f);	// Bottom Right
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Right
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f,  1.0f,  1.0f);	// Top Left
    // Back Face
    glNormal3f(0.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);	// Bottom Right
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f,  1.0f, 0.0f);	// Top Right
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f, 0.0f);	// Top Left
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, 0.0f, 0.0f);	// Bottom Left
    // Top Face
    glNormal3f(0.0f, 1.0f, 0.0f);
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f,  1.0f, 0.0f);	// Top Left
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f,  1.0f,  1.0f);	// Bottom Left
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Bottom Right
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, 0.0f);	// Top Right
    // Bottom Face
    glNormal3f(0.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f, 0.0f, 0.0f);	// Top Right
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f, 0.0f, 0.0f);	// Top Left
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, 0.0f,  1.0f);	// Bottom Left
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f,  1.0f);	// Bottom Right
    // Right face
    glNormal3f(1.0f, 0.0f, 0.0f);
    glTexCoord2f(1.0f, 0.0f); glVertex3f( 1.0f, 0.0f, 0.0f);	// Bottom Right
    glTexCoord2f(1.0f, 1.0f); glVertex3f( 1.0f,  1.0f, 0.0f);	// Top Right
    glTexCoord2f(0.0f, 1.0f); glVertex3f( 1.0f,  1.0f,  1.0f);	// Top Left
    glTexCoord2f(0.0f, 0.0f); glVertex3f( 1.0f, 0.0f,  1.0f);	// Bottom Left
    // Left Face
    glNormal3f(0.0f, 0.0f, 0.0f);
    glTexCoord2f(0.0f, 0.0f); glVertex3f(0.0f, 0.0f, 0.0f);	// Bottom Left
    glTexCoord2f(1.0f, 0.0f); glVertex3f(0.0f, 0.0f,  1.0f);	// Bottom Right
    glTexCoord2f(1.0f, 1.0f); glVertex3f(0.0f,  1.0f,  1.0f);	// Top Right
    glTexCoord2f(0.0f, 1.0f); glVertex3f(0.0f,  1.0f, 0.0f);	// Top Left
    glEnd();

    glPopMatrix();
}

#include "headers/elements.h"
#include <sstream>

void game::racket::draw() {
    glBegin(GL_POLYGON);
        glVertex2f(this->x_pos, this->y_pos);     // bottom left corner
        glVertex2f(this->x_pos, this->y_pos + this->height);      // top left corner
        glVertex2f(this->x_pos + this->width, this->y_pos + this->height);      // top right corner
        glVertex2f(this->x_pos + this->width, this->y_pos);     // bottom right corner
    glEnd();
}

void game::racket::moveUp() {
    if(this->y_pos + this->height < 1) {
        this->y_pos+=0.05;
    }
}

void game::racket::moveDown() {
    if(this->y_pos > -1) {
        this->y_pos-=0.05;
    }
}

void game::ball::draw() {
    glBegin(GL_POLYGON);
        glVertex2f(this->x_pos, this->y_pos);     // bottom left corner
        glVertex2f(this->x_pos, this->y_pos + 0.05);      // top left corner
        glVertex2f(this->x_pos + 0.05, this->y_pos + 0.05);      // top right corner
        glVertex2f(this->x_pos + 0.05, this->y_pos);     // bottom right corner
    glEnd();
}

void RenderString(float x, float y, void *font, const unsigned char* str)
{  
  char *c;
  glRasterPos2f(x, y);

  glutBitmapString(font, str);
}

void game::drawGame(game::racket *r1,game::racket *r2) {
    int amountOfLines = 11;
    float length = (float)2 / amountOfLines;
    for(int i = 0; i < amountOfLines; i++) {
        //only draw line on even numbers
        if(i % 2 == 0) {
        float start = -1 + i*length;
        float end = start + length;
        glBegin(GL_LINES);
            glVertex2d(0, start);
            glVertex2d(0, end);
        glEnd();
        }
    }
    std::stringstream ss;
    ss << "score: " << r1->score << ":" << r2->score;
    const unsigned char* t = reinterpret_cast<const unsigned char *>(ss.str().c_str());
    RenderString(-1.0f,0.9f,GLUT_BITMAP_TIMES_ROMAN_24,t);

}
#include <iostream>
#include <GL/freeglut.h>

namespace game {
    class racket {
        public:
        float height = 0.7;
        float width = 0.06;
        float y_pos = 0-(this->height/2);
        float x_pos;
        std::string name;
        int score;
        void draw();
        void moveUp();
        void moveDown();
    };
    class ball {
        public:
        float x_pos = 0.5;
        float y_pos = 0;
        float x_speed = -0.015;
        float y_speed = -0.015;
        void draw();
    };

    void drawGame(game::racket *r1,game::racket *r2);
}
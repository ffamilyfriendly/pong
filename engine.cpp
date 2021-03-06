#include "headers/elements.h"

//elements
game::racket *p1 = new game::racket();
game::racket *p2 = new game::racket();
game::ball *ball = new game::ball();

//define things
int width = 1920;
int height = 1080;
int autismLevel = 1; //lowest 0 max 10

//funcs
void render(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); //clear screen
    game::drawGame(p1,p2);
    p1->draw();
    p2->draw();
    ball->draw();
    glutSwapBuffers();
}



void keyboard(unsigned char c, int x, int y) {
    if(c == 'w') {
        //up
        p1->moveUp();
    } else if(c == 's') {
        //down
        p1->moveDown();
    }
};



void moveBall() {
    ball->x_pos+=ball->x_speed;
    ball->y_pos+=ball->y_speed;
};

void prepare_rackets() {
    p1->x_pos = -1;
    p1->name = "player";
    p2->x_pos = 1 - p2->width;
    p2->name = "NPC";
}

void endGame(game::racket *r) {
    prepare_rackets();
    ball->x_pos = 0;
    ball->y_pos = 0;
}

void calcCol() {
    //check if wall
    if(ball->y_pos + 0.05 >= 1) ball->y_speed = ball->y_speed-ball->y_speed*2;
    if(ball->y_pos < -1) ball->y_speed = ball->y_speed * -1;

    //check rackets
    if(ball->y_pos <= p1->y_pos+p1->height && ball->y_pos > p1->y_pos && ball->x_pos <= p1->x_pos+p1->width) ball->x_speed = ball->x_speed * -1;
    if(ball->y_pos <= p2->y_pos+p2->height && ball->y_pos > p2->y_pos && ball->x_pos + 0.05 >= 1-p2->width) ball->x_speed = ball->x_speed-ball->x_speed*2;

    //check end states
    if(ball->x_pos >= 1) {p1->score++; endGame(p1);}
    else if(ball->x_pos < -1) {p2->score++; endGame(p2);}
}


//NPC thinking func
void bigThink() {
    float middle = p2->y_pos + p2->height/2;
    float ballPos = ball->y_pos;
    if(ballPos < middle) p2->moveDown();
    else p2->moveUp();
}

void update(int value) {
    moveBall();
    glutTimerFunc(1000/60,update,0);
}

void aiRun(int value) {
    bigThink();
    calcCol();
    glutTimerFunc(1000/20,aiRun,0);
}

void createWin(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(width,height);
    glutCreateWindow("pong");
}

void startGame(int argc, char **argv) {
    createWin(argc, argv);
    prepare_rackets();
    glutDisplayFunc(render);
    glutIdleFunc(render);
    glutKeyboardFunc(keyboard);
    glutTimerFunc(1000/60,update,0);
    glutTimerFunc(1000/20,aiRun,0);
    glutMainLoop();
}

int main(int argc, char **argv) {
    startGame(argc,argv);
}

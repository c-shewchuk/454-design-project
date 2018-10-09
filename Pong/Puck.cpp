//
// Created by Alex on 2018-09-20.
//

#include "Puck.h"


Puck::Puck() {
    xpos = xpos0;
    ypos = ypos0;
    srand (time(NULL));
    xspeed = rand()% 3 + 1;
    srand (time(NULL)*time(NULL));
    yspeed = rand()% 3 + 1;
}

Puck::Puck(double x, double y, double vx, double vy){
    xpos = x;
    ypos = y;
    xspeed = vx;
    yspeed = vy;

}

Puck::~Puck() {}

void Puck::slide(){
    xpos = xpos + xspeed;
    ypos = ypos + yspeed;
}

void Puck::edges() {
    if (ypos >= height || ypos <= 0)
        yspeed = -yspeed;
    if (xpos >= width || xpos <= 0) {
        xpos = 0;
        ypos = 0;
        srand (time(NULL));
        xspeed = rand()% 3 + 1;
        srand (time(NULL)*time(NULL));
        yspeed = rand()% 3 + 1;
    }
}

//
// Created by Alex on 2018-09-20.
//
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

#ifndef UNTITLED2_PUCK_H
#define UNTITLED2_PUCK_H


class Puck {
public:
    Puck(); //Default Constructor
    Puck(double, double, double, double); // xpos, ypos, xpspeed, yspeed
    ~Puck(); //Destructor

    //Acessors
    /*
    double getxpos() const;
    double getypos() const;
    double getxspeed() const;
    double getyspeed() const;
     */
    void slide();

    void edges();


private:
    double xpos;
    double ypos;
    double xspeed;
    double yspeed;
    double xpos0 = 0;
    double ypos0 = 0;
    double height = 10;
    double width = 20;

};
#endif //UNTITLED2_PUCK_H

//
//  Puck.h
//  C++TestProject
//
//  Created by Griffin Staples on 2018-10-01.
//  Copyright © 2018 Clarity. All rights reserved.
//
#include "Edges.h"
#include "Striker.h"

#ifndef Puck_h
#define Puck_h

class Puck {
private:
    int x_start;        //initial x position
    int y_start;        //initial y position
    float radius;
public:
    float x;
    float y;
    float vx;
    float vy;
    float x_m;          // x difference between next striker and puck position
    float y_m;          // y difference between next striker and puck position
    float nx;           // x normalized normal vector
    float ny;           // y normalized normal vector
    float speed;        
    float theta;
    Puck(int x_created, int y_created, float r_created);
    void move();
    void changeDirec(float new_x, float new_y);
    void drawPuck();
    void checkWallCollision(const Edges edges);
    void checkStrikerCollision(Striker striker);
    

    
    
    
};


#endif /* Puck_h */

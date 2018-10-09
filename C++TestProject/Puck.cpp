//
//  Puck.cpp
//  C++TestProject
//
//  Created by Griffin Staples on 2018-10-01.
//  Copyright © 2018 Clarity. All rights reserved.
//

#include "Puck.h"
#include "math.h"
#include <iostream>
using namespace std;

Puck::Puck(int x_created, int y_created, float r_created){
    x_start = x_created;
    y_start = y_created;
    radius = r_created;
    vy = 0;
    vx = 0;
    x = x_created;
    y = y_created;
}

void Puck::move(){
    x+= vx;
    y+= vy;
}

void Puck::changeDirec(float new_x, float new_y){
    vx = new_x;
    vy = new_y;
}

//checks for wall collision next frame and adds in frictional factors
void Puck::checkWallCollision(const Edges edges){
    if(x-edges.x_0+vx <= radius && vx < 0){
        vx *= -0.9;
        vy *= 0.9;
        x = 2*edges.x_0-x+2*radius;
    }
    else if (edges.x_1-x-vx <= radius && vx > 0){
        vx *= -0.9;
        vy *= 0.9;
        x = 2*edges.x_1-x-2*radius;
    }
    else if (edges.y_0+y+vy <= radius && vy < 0){
        vy *= -0.9;
        vx *= 0.9;
        y = 2*edges.y_0-y+2*radius;
    }
    else if (edges.y_1-y-vy <=radius && vy > 0 ){
        vy *= -0.9;
        vx *= 0.9;
        y = 2*edges.y_1-y-2*radius;
    }
    else{
        vx *= 0.99;
        vy *= 0.99;
    }
        
    }

/*
void Puck::checkStrikerCollision(Striker striker){
    x_m = x-striker.x;
    y_m = y-striker.y;
    if(sqrt(x_m*x_m+y_m*y_m)<= striker.r+radius){
        
            vx += 2*(x_m)/sqrt(x_m*x_m+y_m*y_m)+(striker.x-striker.x_past);
            vy += 2*(y_m)/sqrt(x_m*x_m+y_m*y_m)+(striker.y-striker.y_past);
    }
}
*/

//checks for puck-striker collision next frame
 void Puck::checkStrikerCollision(Striker striker){
 x_m = x+vx-2*striker.x+striker.x_past;
 y_m = y+vy-2*striker.y+striker.y_past;
 if(sqrt((x_m)*(x_m)+(y_m)*(y_m))<= striker.r+radius){
     nx = (x_m)/sqrt(x_m*x_m+y_m*y_m);
     ny = (y_m)/sqrt(x_m*x_m+y_m*y_m);
     vx += 2*nx+(striker.x-striker.x_past);
     vy += 2*ny+(striker.y-striker.y_past);
     vx*=0.8;
     vy*=0.8;
     x = (x + vx +2*ny);
     y = (y + vy -2*nx);
    }
 }


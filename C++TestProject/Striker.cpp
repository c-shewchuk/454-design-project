//
//  Striker.cpp
//  C++TestProject
//
//  Created by Griffin Staples on 2018-10-05.
//  Copyright © 2018 Clarity. All rights reserved.
//

#include "Striker.h"
using namespace std;



Striker::Striker(float radius, Edges edges){
    x = (edges.x_1-edges.x_0)/4;    //center of left side
    y = (edges.y_1-edges.y_0)/2;    //y center
    r = radius;
}

void Striker::moveStriker(int *x_point, int *y_point,Edges edges){
    x_past = x;     //store previous x for velocity calculation
    y_past = y;     //store previous y for velocity calculation
    SDL_GetMouseState(x_point, y_point);        //update striker position

    //ensure max speed of 40*root(2)
    if (sqrt((x-x_past)*(x-x_past)+(y-y_past)*(y-y_past)) > 40 ){
        if (x-x_past>0){
            x = x_past + 40*cos(atan((y-y_past)/(x-x_past)));
            y = y_past + 40*sin(atan((y-y_past)/(x-x_past)));
        }
        else{
            x = x_past - 40*cos(atan((y-y_past)/(x-x_past)));
            y = y_past - 40*sin(atan((y-y_past)/(x-x_past)));
        }
    }

    
    //set boundaries of striker
    if (x>(edges.x_1/2)-r){
        x = (edges.x_1-edges.x_0)/2-r;
    }
    else if (x<edges.x_0+r){
        x = edges.x_0+r;
    }
    if (y>edges.y_1-r){
        y = edges.y_1-r;
    }
    else if (y<edges.y_0+r){
        y = edges.y_0+r;
    }
}

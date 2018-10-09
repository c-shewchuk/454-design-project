//
//  Striker.h
//  C++TestProject
//
//  Created by Griffin Staples on 2018-10-05.
//  Copyright © 2018 Clarity. All rights reserved.
//

#include "SDL2/SDL.h"
#include "Edges.h"
#include "math.h"
using namespace std;

#ifndef Striker_h
#define Striker_h

class Striker {
public:
    Striker(float radius, Edges edges);
    float r;        //radius
    float x_past;   //previous x position
    float y_past;   //previous y position
    int x;          //current x position
    int y;          //current y position
    int *x_p = &x;  //pointer to x pos
    int *y_p = &y;  //pointer to y pos
    void moveStriker(int *x_point, int *y_point, Edges edges);
    
};
#endif /* Striker_h */

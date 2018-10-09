//
//  Edges.cpp
//  C++TestProject
//
//  Created by Griffin Staples on 2018-10-02.
//  Copyright © 2018 Clarity. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "Edges.h"
#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"
using namespace std;


Edges::Edges(int x0, int y0, int x1, int y1, int corn_rad){
    x_0 = x0;
    y_0 = y0;
    x_1 = x1;
    y_1 = y1;
    CR = corn_rad;
};


void Edges::Draw(SDL_Renderer *renderer){
    roundedRectangleColor(renderer, x_0, y_0, x_1-1,y_1-1, CR, 0xFFFFFFFF);
}

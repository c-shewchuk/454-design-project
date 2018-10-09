//
//  Edges.h
//  C++TestProject
//
//  Created by Griffin Staples on 2018-10-02.
//  Copyright © 2018 Clarity. All rights reserved.
//

#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"

#ifndef Edges_h
#define Edges_h

class Edges {
public:
    void Draw(SDL_Renderer *renderer);
    int x_0;    //top left x
    int y_0;    //top left y
    int x_1;    //bottom right x
    int y_1;    //bottom right y
    int CR;     //corner radius
    Edges(int x0, int y0, int x1, int y1, int corn_rad);
};

#endif /* Edges_h */

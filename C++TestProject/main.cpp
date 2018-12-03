//
//  main.cpp
//  C++TestProject
//
//  Created by Griffin Staples on 2018-09-30.
//  Copyright © 2018 Clarity. All rights reserved.
//

#include <iostream>
#include <SDL2/SDL.h>
#include "SDL2/SDL2_gfxPrimitives.h"
#include "Screen.h"
#include "Puck.h"
#include "Edges.h"
#include "Striker.h"
using namespace std;

const int SCREEN_WIDTH = 825;
const int SCREEN_HEIGHT  = 369;
const int corner_rad = 40;
const float puck_rad = 15;
const float striker_rad = 24;


int main() {

    //create simulation objects
    Screen screen(SCREEN_WIDTH, SCREEN_HEIGHT);;
    Puck puck(SCREEN_WIDTH/2, SCREEN_HEIGHT/2, puck_rad);
    Edges edges(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT, corner_rad);
    Striker striker(striker_rad, edges);
    
    //initialize screen
    if(screen.init() == false) {
        cout << "Error initialising SDL." << endl;
        return 1;
    }
    
    SDL_Renderer *renderer = screen.getRenderer();      //get variable renderer to use locally
    
    
    SDL_Event event;        //create SDL event
    puck.changeDirec(0,0);      //set direction
    

    int quit = 0; int time;     //declare loop variables
    while (!quit){
        
        //quit if button pressed
        if (SDL_PollEvent(&event)){
            if (event.type == SDL_QUIT)
                quit = 1;
        }
        
        time = SDL_GetTicks();      //initial time
        
      
     
        //check for collisions then move
        puck.checkWallCollision(edges);
        puck.checkStrikerCollision(striker);
        puck.move();
        striker.moveStriker(striker.x_p,striker.y_p,edges);
        
        //draw objects
        edges.Draw(renderer);
        filledCircleColor(renderer, puck.x, puck.y, puck_rad, 0xFF0000FF);
        filledCircleColor(renderer, striker.x, striker.y, striker_rad, 0xFFFFFFFF);
        screen.refresh();       //update screen
        
        
        //loop runs with a framerate of 20ms
        time = SDL_GetTicks()-time;
        if (time<20){
            SDL_Delay(time);
        }
        
    }
    
    //delete window and renderer
    screen.close();
    return 0;
}






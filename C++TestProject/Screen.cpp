//
//  Screen.cpp
//  C++TestProject
//
//  Created by Griffin Staples on 2018-10-01.
//  Copyright © 2018 Clarity. All rights reserved.
//

#include "Screen.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>

Screen::Screen(int width, int height) {
    window = NULL;
    renderer = NULL;
    //texture = NULL;
    buffer = NULL;
    SCREEN_WIDTH = width;
    SCREEN_HEIGHT = height;
}

//initialize window and buckets for pixels
bool Screen::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf ("SDL_Init Error: %s", SDL_GetError());
        return false;
    }

    //define window object
    window = SDL_CreateWindow("Air Hockey",
                     SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH,
                     SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    
    
    if (window == NULL) {
        printf ("SDL_CreateWindow Error: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }
    
    //define renderer
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    
    //destroy window if error in making renderer
    if (renderer == NULL) {
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }
    
    return true;
    
}

SDL_Renderer* Screen::getRenderer(){
    return renderer;
}
SDL_Window* Screen::getWindow(){
    return window;
}

void Screen::refresh(){
    SDL_RenderPresent(renderer);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0xFF);
    SDL_RenderClear(renderer);
}

void Screen::close() {
    delete[] buffer;
    SDL_DestroyRenderer(renderer);
    //SDL_DestroyTexture(texture);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

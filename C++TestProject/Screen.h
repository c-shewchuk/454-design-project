//
//  Screen.h
//  C++TestProject
//
//  Created by Griffin Staples on 2018-10-01.
//  Copyright © 2018 Clarity. All rights reserved.
//

#ifndef Screen_h
#define Screen_h

#include <SDL2/SDL.h>



class Screen {
private:
    SDL_Renderer *renderer;
    SDL_Window *window;
    Uint32 *buffer;
    int SCREEN_WIDTH;
    int SCREEN_HEIGHT;
    
public:
    Screen(int width, int height);
    bool init();
    void refresh();
    bool processEvents();
    void close();
    SDL_Renderer* getRenderer();
    SDL_Window* getWindow();
    
};

#endif /* Screen_h */

#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <vector>
#include "Functions.h"
#include "Vector.h"
using namespace std;

struct Mouse{
    Vector2D mouse_pos;
    bool Left_Click = false;
    bool Right_Click = false;
    //Mouse() : Mouse(Vector2D(0, 0), false, false) {}
    //Mouse(Vector2D mpos, bool lc, bool rc);
};

#endif
#ifndef __MAIN_H__
#define __MAIN_H__

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include <stdio.h>
#include <windows.h>
#include <stdint.h>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <fstream>
using namespace std;
/*
 * Struct define
 */
struct vect{
    int x;
    int y;
};

struct color{
    int r, b, g, c;
};

/*
 * Game constant variable
 */
const int SCREEN_WIDTH = 1000;
const int SCREEN_HEIGHT = 500;
const int BASE_PIXEL = 20;
const int FPS=60;
const float DELAY_TIME =1000.0f / FPS;

//Baseic
const int BASE_X_POS = BASE_PIXEL;
const int BASE_Y_POS = BASE_PIXEL;

//Text
const int TEXT_X_POS = 750;
const int TEXT_Y_POS = 50;
const int TEXT_SIZE = 24;
//Wall
const int WALL_X_BLOCK = 32;
const int WALL_Y_BLOCK = 22;
const int WALL_WIDTH = WALL_X_BLOCK * BASE_PIXEL;
const int WALL_HEIGHT = WALL_Y_BLOCK * BASE_PIXEL;

//Snake
const int BASE_SNAKE_X = BASE_X_POS + (WALL_X_BLOCK/2 - 1) * BASE_PIXEL;
const int BASE_SNAKE_Y = BASE_Y_POS + (WALL_Y_BLOCK/2 - 1) * BASE_PIXEL;
const int SNAKE_SPEED = 6;

//Path
const char FOOD_TEXTURE_PATH[100] = "./texture/food.png";
const char FONT_PATH[100] = "./fonts/Anton-Regular.ttf";
//Color
const color WINDOW_COLOR = {236, 239, 137, 0};
const color BACKGROUND_COLOR = {86, 147, 193, 0};
const color WALL_COLOR = {192, 192, 192, 255};
const color SNAKE_COLOR = {128, 255, 0, 0};

//
const string START_MESS = "PRESS SPACE TO START!";
const string LOST_MESS = "YOU LOST, YOUR SCORE IS: ";
//
static int gameFrame = 0;
static string mess;


#endif // __MAIN_H__


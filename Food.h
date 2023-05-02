#ifndef __FOOD_H__
#define __FOOD_H__

#include "store.h"

class Food{
    static vect pos;
    static bool existed;
    static SDL_Texture* texture;
public:
    static vect getPos();
    static void init(SDL_Renderer*);
    static void createFood();
    static void destroyFood();
    static void render(SDL_Renderer*);
    static void test();

};


#endif // __FOOD_H__

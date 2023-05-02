#include "Food.h"

vect Food::pos = {-1, -1};
bool Food::existed = false;
SDL_Texture* Food::texture = NULL;


vect Food::getPos(){
    return Food::pos;
}

void Food::init(SDL_Renderer* renderer){
    Food::texture = IMG_LoadTexture(renderer, FOOD_TEXTURE_PATH);

}


void Food::createFood(){
    if (!Food::existed){
        //Creare random food position
        //while(true){
            int newX = (rand() % (WALL_X_BLOCK-2)) * BASE_PIXEL + BASE_X_POS;
            int newY = (rand() % (WALL_Y_BLOCK-2)) * BASE_PIXEL + BASE_Y_POS;
            //printf("%d %d\n", newX, newY);

        //}
        Food::pos = {newX, newY};
        Food::existed = true;
    }
}

void Food::destroyFood(){
    if (Food::existed){
        Food::pos = {-1, -1};
        Food::existed = false;
    }
}

void Food::render(SDL_Renderer *renderer){
    if (Food::existed){
        SDL_Rect texture_rect = { Food::pos.x, Food::pos.y, BASE_PIXEL, BASE_PIXEL};
        SDL_RenderCopy(renderer, texture, NULL, &texture_rect);

    }
}

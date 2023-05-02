#include "Snake.h"

int Snake::length = 1;
vect Snake::head = {BASE_SNAKE_X, BASE_SNAKE_Y};
vect Snake::direction = {BASE_PIXEL, 0};
vector<vect> Snake::body;


vect Snake::getPos(){
    return Snake::head;
}

int Snake::getLength(){
    return Snake::length;
}
void Snake::init(){
    Snake::body.clear();
    Snake::direction = {BASE_PIXEL, 0};
    Snake::head = {BASE_SNAKE_X, BASE_SNAKE_Y};
    Snake::length = 1;
    Snake::body.push_back(Snake::head);
}

void Snake::updatePosition(int &frame){
    //printf("%d\n", frame);
    if (frame  < SNAKE_SPEED ) return;
    //printf("Change pos\n");
    vect newPosition = {Snake::head.x + Snake::direction.x, Snake::head.y + Snake::direction.y};
    if (newPosition.x < BASE_X_POS){
        newPosition.x = WALL_WIDTH - 2*BASE_X_POS;
    }
    else if (newPosition.y < BASE_Y_POS){
        newPosition.y = WALL_HEIGHT - 2*BASE_Y_POS;
    }
    else if (newPosition.x >= WALL_WIDTH - BASE_X_POS){
        newPosition.x = BASE_X_POS;
    }
    else if (newPosition.y >= WALL_HEIGHT - BASE_Y_POS){
        newPosition.y = BASE_Y_POS;
    }
    Snake::body.insert(Snake::body.begin(), newPosition);
    Snake::body.pop_back();
    Snake::head = newPosition;
    frame = 0;
}
void Snake::render(SDL_Renderer *renderer){
    for(vect snake:Snake::body){
        SDL_Rect rect = {snake.x, snake.y, BASE_PIXEL, BASE_PIXEL};
        SDL_SetRenderDrawColor(renderer, SNAKE_COLOR.r, SNAKE_COLOR.b, SNAKE_COLOR.g, SNAKE_COLOR.c);
        SDL_RenderFillRect(renderer, &rect);
    }
}

void Snake::updateDirection(int key){
    switch (key){
        //Key W
        case 119:{
            if (Snake::direction.y > 0 ) break;
            Snake::direction = {0, -BASE_PIXEL};
            break;
        }
        //Key S
        case 115:{
            if (Snake::direction.y < 0) break;
            Snake::direction = {0, BASE_PIXEL};
            break;
        }
        //Key A
        case 97:{
            if (Snake::direction.x > 0 ) break;
            Snake::direction = {-BASE_PIXEL, 0};
            break;
        }
        //Key D
        case 100:{
            if (Snake::direction.x < 0) break;
            Snake::direction = {BASE_PIXEL, 0};
            break;
        }
    }

}

void Snake::growUp(){
    if (Snake::length == 1){
        vect newBody = {Snake::head.x - Snake::direction.x, Snake::head.y - Snake::direction.y};
        Snake::body.push_back(newBody);
    }
    else{
        vect newBody = { 2*Snake::body.back().x - Snake::body[Snake::body.size()-2].x,
                         2*Snake::body.back().y - Snake::body[Snake::body.size()-2].y};
        Snake::body.push_back(newBody);
    }
    Snake::length++;
}

bool Snake::ateItSelf(){
    vector<vect>::iterator it;
    for(it = Snake::body.begin()+1; it != Snake::body.end(); ++it){
        if ((*it).x == Snake::head.x && (*it).y == Snake::head.y){
            return 1;
        }
    }
    return 0;
}
void Snake::test(){
    for(vect snake:Snake::body){
        printf("%X:d Y:%d\n", snake.x, snake.y);
    }
}

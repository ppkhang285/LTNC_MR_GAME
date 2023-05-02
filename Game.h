#ifndef __GAME_H__
#define __GAME_H__

#include "store.h"
#include "Snake.h"
#include "Food.h"

using namespace std;

class Game{
private:
    SDL_Window *window;
    SDL_Renderer *renderer;
    SDL_Event e;
    TTF_Font* font;
    bool quit;
    bool isRunning;
    bool isLost;
public:
    Game();
    int init();
    void printTutorial();
    void drawWall();
    void drawBackground();
    void drawScore();
    void drawMess();
    void checkEatFood();
    void update();
    void catchEvent();
    void render();
    void run();
};

#endif // __GAME_H__

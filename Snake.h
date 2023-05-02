#ifndef __SNAKE__H__
#define __SNAKE__H__

#include <vector>
#include "store.h"

using namespace std;

class Snake{
private:
    static int length;
    static vect head;
    static vect direction;
    static vector<vect> body;

public:
    static vect getPos();
    static int getLength();
    static void init();
    static void updatePosition(int&);
    static void updateDirection(int);
    static bool ateItSelf();
    static void growUp();
    static void test();
    static void render(SDL_Renderer*);


};



#endif // __SNAKE__H__

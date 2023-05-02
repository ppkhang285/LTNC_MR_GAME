
#include "main.h"
#include "Snake.h"


//

void drawWall(SDL_Renderer *renderer){
    //
    SDL_Rect topWall = {0, 0, WALL_WIDTH, BASE_PIXEL};
    SDL_Rect bottomWall = {0, WALL_HEIGHT-20, WALL_WIDTH, BASE_PIXEL};
    SDL_Rect leftWall = {0, 0, BASE_PIXEL, WALL_HEIGHT};
    SDL_Rect rightWall = {WALL_WIDTH-20, 0, BASE_PIXEL, WALL_HEIGHT};
    //
    SDL_SetRenderDrawColor(renderer, 192, 192, 192, 255);
    //
    SDL_RenderFillRect(renderer, &topWall);
    SDL_RenderFillRect(renderer, &bottomWall);
    SDL_RenderFillRect(renderer, &leftWall);
    SDL_RenderFillRect(renderer, &rightWall);
    //
    //SDL_RenderPresent(renderer);
}
int main(int argc, char *args[])
{
    // The window we'll be rendering to
    SDL_Window *window = NULL;
    SDL_Renderer *renderer = NULL;

    // The surface contained by the window
    //SDL_Surface *screenSurface = NULL;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else
    {
        // Create window
        window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL)
        {
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else
        {
            renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
            Snake::init();

            SDL_Event e;
            bool quit = false;
            //


            //
            while (quit == false)
            {
                //Enevnt handel
                while (SDL_PollEvent(&e))
                {
                    if (e.type == SDL_QUIT){
                       quit = true;
                    }
                    //Get key pressed
                    else if (e.type == SDL_KEYDOWN){
                        Snake::updateDirection(e.key.keysym.sym);
                    }

                }

                //Doing in LOOP

                gameFrame++;

                //Update
                Snake::updatePosition(gameFrame);
                //Snake::test();
                //Render
                SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
                SDL_RenderClear(renderer);
                //
                drawWall(renderer);
                Snake::render(renderer);

                //
                SDL_RenderPresent(renderer);
                SDL_Delay((int)DELAY_TIME);
            }
        }
    }

    // Destroy window
    SDL_DestroyWindow(window);

    // Quit SDL subsystems
    SDL_Quit();

    return 0;
}

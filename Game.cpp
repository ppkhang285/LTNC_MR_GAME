#include "Game.h"


Game::Game(){
    this->renderer = NULL;
    this->window = NULL;
    this->quit = false;
    this->isRunning = false;
    this->isLost = false;
}

void Game::printTutorial(){
    fstream file;
    file.open("__TUTORIAL__.txt",ios::in);
    if (file.is_open()){
        string tp;
        while(getline(file, tp)){
        cout << tp << "\n";
    }
    file.close();
   }

}
int Game::init(){
    srand(time(0));
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL){
       printf("Could not create render %s", SDL_GetError());
       return -1;
    }
    font = TTF_OpenFont(FONT_PATH, TEXT_SIZE);
    if(font == NULL) {
       printf("Font not loaded: %s\n",TTF_GetError());
       return -1;
    }
    printTutorial();
    mess = START_MESS;
    Snake::init();
    Food::init(renderer);
    Food::createFood();
    render();
    //drawMess(START_MESS);
    return 0;
}
void Game::drawWall(){
    SDL_Rect topWall = {0, 0, WALL_WIDTH, BASE_PIXEL};
    SDL_Rect bottomWall = {0, WALL_HEIGHT-20, WALL_WIDTH, BASE_PIXEL};
    SDL_Rect leftWall = {0, 0, BASE_PIXEL, WALL_HEIGHT};
    SDL_Rect rightWall = {WALL_WIDTH-20, 0, BASE_PIXEL, WALL_HEIGHT};
    //
    SDL_SetRenderDrawColor(renderer, WALL_COLOR.r, WALL_COLOR.b, WALL_COLOR.g, WALL_COLOR.c);
    //
    SDL_RenderFillRect(renderer, &topWall);
    SDL_RenderFillRect(renderer, &bottomWall);
    SDL_RenderFillRect(renderer, &leftWall);
    SDL_RenderFillRect(renderer, &rightWall);
}

void Game::drawBackground(){
    SDL_Rect background = {0, 0, WALL_WIDTH, WALL_HEIGHT};
    SDL_SetRenderDrawColor(renderer, BACKGROUND_COLOR.r, BACKGROUND_COLOR.b, BACKGROUND_COLOR.g, BACKGROUND_COLOR.c);
    SDL_RenderFillRect(renderer, &background);
}

void Game::drawMess(){
    SDL_Color textColor = {0, 0, 0,0};
    SDL_Surface* surfaceText = TTF_RenderText_Blended_Wrapped(font, mess.c_str(), textColor, 500);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, surfaceText);
    SDL_Rect textRect = {TEXT_X_POS, TEXT_Y_POS, surfaceText->w, surfaceText->h};
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_RenderPresent(renderer);
    SDL_FreeSurface(surfaceText);
    SDL_DestroyTexture(textTexture);
}

void Game::drawScore(){
    string mess = "Snake's Length:\n" + to_string(Snake::getLength());
    //printf("%s\n", mess.c_str());
    drawMess();

}

void Game::checkEatFood(){
    vect snakePos = Snake::getPos();
    vect foodPos = Food::getPos();
    if ( snakePos.x == foodPos.x && snakePos.y == foodPos.y ){
        //Snake update
        Snake::growUp();
        //Delete entire food and create new food
        Food::destroyFood();
        Food::createFood();
    }
}


void Game::catchEvent(){
    while (SDL_PollEvent(&e)){
        if (e.type == SDL_QUIT){
            quit = true;
        }
        //Get key pressed
        else if (e.type == SDL_KEYDOWN){
            Snake::updateDirection(e.key.keysym.sym);
            //SPACE
            if (e.key.keysym.sym == 32){
                if (!isLost){
                   isRunning = !isRunning;
                }
                else{
                    Snake::init();
                    Food::destroyFood();
                    Food::createFood();
                    mess = START_MESS;
                    render();
                    isLost = false;
                }
            }
             //ESC
            if (e.key.keysym.sym == 27){
                quit = true;
            }
        }

    }
}
void Game::update(){
    gameFrame++;
    if(Snake::ateItSelf()){
        isRunning = false;
        isLost = true;
    }
    checkEatFood();
    Snake::updatePosition(gameFrame);
    mess = "Snake's Length:\n" + to_string(Snake::getLength());
}

void Game::render(){
    SDL_SetRenderDrawColor(renderer, WINDOW_COLOR.r, WINDOW_COLOR.b, WINDOW_COLOR.g, WINDOW_COLOR.c); //background color
    SDL_RenderClear(renderer);
    //
    drawBackground();
    drawWall();
    drawMess();
    Food::render(renderer);
    Snake::render(renderer);

    //
    SDL_RenderPresent(renderer);
}


void Game::run(){
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0){
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
    }
    else if (TTF_Init() < 0){
        printf("TTF could not initialize! TTF_Error: %s\n",TTF_GetError());
    }
    else{
        // Create window
        window = SDL_CreateWindow("SNAKE GAME", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
        if (window == NULL){
            printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        }
        else{
            if (init() < 0) return;
            //Game main loop
            while (quit == false)
            {
                catchEvent();
                if (!isRunning) continue;
                update();
                //Handel lost case
                if (isLost){
                    mess = LOST_MESS + "\n" + to_string(Snake::getLength() - 1);
                    mess = mess + "\nPRESS SPACE TO REPLAY";
                }
                render();
                SDL_Delay((int)DELAY_TIME);
            }
        }
    }
    // Destroy window
    printf("-------------------------------\n");
    printf(">>>>>>>HAVE A NICE DAY<<<<<<<<<\n");
    printf("-------------------------------");
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    TTF_CloseFont(font);
    TTF_Quit();
    // Quit SDL subsystems
    SDL_Quit();

}

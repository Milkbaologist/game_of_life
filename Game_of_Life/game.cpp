//
//  game.cpp
//  Game_of_Life
//
//  Created by Gary Chen on 1/12/23.
//

#include "game.hpp"


bool Game::initialize(){
    if(SDL_Init(SDL_INIT_EVERYTHING)){
//            printf("Error: %s\n", SDL_GetError());
        return false;
    }
//        window = SDL_CreateWindow("Convey's_Game_of_Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
//        Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!window){
//            printf("Error: %s\n", SDL_GetError());
        return false;
    }
    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
    SDL_RenderClear(Renderer);
    return true;
}

void Game::drawGrids(){
    
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
    for(int i = 0; i <= 800; i+=20){
        SDL_RenderDrawLine(Renderer, i, 0, i, 600);
    }
    for(int i = 0; i <= 600; i+=20){
        SDL_RenderDrawLine(Renderer, 0, i, 800, i);
    }
}

void Game::drawRect(int x, int y){
    int temp_x = x * 20;
    int temp_y = y * 20;
    rect.h = 20;
    rect.w = 20;
    rect.x = temp_x;
    rect.y = temp_y;
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
    SDL_RenderFillRect(Renderer, &rect);
}

void Game::drawAllRects(){
    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
    for(int x = 0; x < 40; x++){
        for(int y = 0; y <30; y++){
            if(blocks[x][y].condition == 1){
                drawRect(x, y);
            }
        }
    }
}

void Game::resetpopulation(){
    for(int x = 0; x < 40; x++ ){
        for(int y = 0; y < 30; y++ ){
            blocks[x][y].living_population =0;
        }
    }
}

void Game::population(){
    int from_x;
    int from_y;
    int to_x;
    int to_y;
    for(int x = 0; x < 40; x++ ){
        for(int y = 0; y < 30; y++ ){
            if(blocks[x][y].condition == 1){
                from_x = x - 1;
                from_y = y -1;
                to_x = x + 1;
                to_y = y + 1;
                if(x == 0){
                    from_x = 0;
                }
                if(y == 0){
                    from_y = 0;
                }
                if(x == 39){
                    to_x = 39;
                }
                if(y == 29){
                    to_y = 29;
                }
                for(int i = from_x; i <= to_x; i++){
                    for(int j = from_y; j <= to_y; j++){
                        blocks[i][j].living_population ++;
                    }
                }
                blocks[x][y].living_population --;
            }
        }
    }
    
}

void Game::life_or_dead(){
    
    resetpopulation();
    population();
    for(int x = 0; x < 40; x++ ){
        for(int y = 0; y < 30; y++ ){
            if(blocks[x][y].living_population == 3){
                blocks[x][y].condition = 1;
            }
            else if(blocks[x][y].living_population == 2 && blocks[x][y].condition == 1){
                blocks[x][y].condition = 1;
            }
            else{
                blocks[x][y].condition = 0;
            }
        }
    }
}

void Game::game_loop(){
    int const FPS = 10;
    const int frameDelay = 1000 / FPS;
    Uint32 framestart;
    int frametime;
    
    bool quit1 = true;
    int temp_x;
    int temp_y;
    SDL_Event event;
    if(!initialize()){
        cout <<"False";
    }
    
    bool running = 0;
    int c = 0;
    
    while (quit1){
        framestart = SDL_GetTicks();
        if(running){
            life_or_dead();
        }
        
        SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
        SDL_RenderClear(Renderer);
        drawGrids();
        drawAllRects();
        SDL_RenderPresent(Renderer);
         
        while (SDL_PollEvent(&event)){

            
            if(event.key.keysym.sym == SDLK_SPACE && event.type == SDL_KEYUP){
                if(running){
                    cout << "Game Paused" << endl;
                    running = false;
                }
                else if(!running){
                    cout << "Game back on running" << endl;
                    running = true;
                }
            }
            
            if(event.type == SDL_QUIT){
                quit1 = false;
            }
            
            if(event.key.keysym.sym == SDLK_q){
                quit1 = false;
            }
            
//                if(pause){
//                    life_or_dead();
//                }
            
            
                
            if(SDL_MOUSEBUTTONDOWN == event.type) {
                SDL_GetMouseState(&temp_x, &temp_y);
                temp_x/=20;
                temp_y/=20;
                    
                if(blocks[temp_x][temp_y].condition == 1){
                    blocks[temp_x][temp_y].condition = 0;
                }
                    
                else{
                    blocks[temp_x][temp_y].condition = 1;
                }

            }
            
        }
        frametime = SDL_GetTicks() - framestart;
        if(frameDelay > frametime){
            SDL_Delay(frameDelay - frametime);
            printf("%05d: Sleep %d\n", c++, frameDelay - frametime);
        } else {
            printf("%05d: Sleep %d  333\n", c++, frameDelay - frametime);
        }
    }
    quit();
}
void Game::test(){
    initialize();
    drawGrids();
}
void Game::quit(){
    
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(Renderer);
    SDL_Quit();
}

//
//  main.cpp
//  Game_of_Life
//
//  Created by Gary Chen on 1/8/23.
//

#include <iostream>
#include <SDL2/SDL_image.h>
#include <vector>
using namespace std;

struct Game {
    SDL_Window *window;
    SDL_Renderer *Renderer;
    SDL_Rect rect;
    public:vector <vector<int>> blocks;
    
    bool initialize(){
        if(SDL_Init(SDL_INIT_EVERYTHING)){
            printf("Error: %s\n", SDL_GetError());
            return false;
        }
        window = SDL_CreateWindow("Convey's_Game_of_Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
        Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        if(!window){
            printf("Error: %s\n", SDL_GetError());
            return false;
        }
        SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
        SDL_RenderClear(Renderer);
        return true;
    }
    
    void drawGrids(){
        
        SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
        for(int i = 0; i <= 800; i+=20){
            SDL_RenderDrawLine(Renderer, i, 0, i, 600);
        }
        for(int i = 0; i <= 600; i+=20){
            SDL_RenderDrawLine(Renderer, 0, i, 800, i);
        }
    }
    
    void drawRect(int x, int y){
        int temp_x = x * 20;
        int temp_y = y * 20;
        rect.h = 20;
        rect.w = 20;
        rect.x = temp_x;
        rect.y = temp_y;
        SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
        SDL_RenderFillRect(Renderer, &rect);
    }
    
    void drawAllRects(){
        SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
        for(int x = 0; x < 40; x++){
            for(int y = 0; y <30; y++){
                if(blocks[x][y] == 2){
                    drawRect(x, y);
                }
            }
        }
    }
    
    void game_loop(){
        bool quit1 = true;
        int temp_x;
        int temp_y;
        SDL_Event event;
        initialize();
        
        while (quit1){
            while (SDL_PollEvent(&event)){
                SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
                SDL_RenderClear(Renderer);
                drawGrids();
                drawAllRects();
                SDL_RenderPresent(Renderer);
                if(event.type == SDL_QUIT){
                            quit1 = false;
                }
                while(event.type == SDL_KEYDOWN || event.type == SDL_MOUSEBUTTONDOWN){
                    if(event.key.keysym.sym == SDLK_q){
                        quit1 = false;
                        break;
                    }
                    else if(SDL_MOUSEBUTTONDOWN == event.type) {
                        SDL_GetMouseState(&temp_x, &temp_y);
                        temp_x/=20;
                        temp_y/=20;
                        blocks[temp_x][temp_y] = 2;
                        SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
                        SDL_RenderClear(Renderer);
                        drawGrids();
                        drawRect(temp_x, temp_y);
                        SDL_RenderPresent(Renderer);
                        break;
                    }
                    
                }
            }
        }
        quit();
    }
    void test(){
        initialize();
        drawGrids();
    }
    void quit(){
        SDL_DestroyRenderer(Renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
    }
};

int main(int argc, const char * argv[]) {
    
    Game game;
    vector<int> temp (30, 0);
    vector <vector<int>>blocks(40, temp);
    game.blocks = blocks;
    game.game_loop();
//    if(SDL_Init(SDL_INIT_EVERYTHING)){
//        printf("Error: %s\n", SDL_GetError());
//        return 0;
//    }
//    SDL_Window *window = SDL_CreateWindow("Cube", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
//    SDL_Renderer *Renderer;
//    Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
//    if(!window){
//        printf("Error: %s\n", SDL_GetError());
//        return 0;
//    }
//
//    SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
//    SDL_RenderClear(Renderer);
//    SDL_SetRenderDrawColor(Renderer, 0, 0, 0, 255);
//    for(int i = 0; i <= 800; i+=20){
//        SDL_RenderDrawLine(Renderer, i, 0, i, 600);
//    }
//    for(int i = 0; i <= 600; i+=20){
//        SDL_RenderDrawLine(Renderer, 0, i, 800, i);
//    }
//
//    SDL_Rect rect;
//    rect.w = 20;
//    rect.h = 20;
//    SDL_RenderPresent(Renderer);
//    SDL_Event event;
//    int temp_x = 0;
//    int temp_y = 0;

//    bool quit1 = true;
//    while (quit1){
//        while (SDL_PollEvent(&event)){
//            if(event.type == SDL_KEYDOWN){
//                if(event.key.keysym.sym == SDLK_SPACE ){
//                    quit1 = false;
//                }
//            }
//            else if(SDL_MOUSEBUTTONDOWN == event.type) {
//                SDL_GetMouseState(&temp_x, &temp_y);
//                if(temp_x <=800 && temp_y <= 600){
//                    if(temp_x > 20 && temp_y > 20 ){
//                        blocks[temp_x/20][temp_y/20] = 2;
//                        rect.x = (temp_x/20)*20;
//                        rect.y = (temp_y/20)*20;
//                        SDL_RenderFillRect(Renderer, &rect);
//                        SDL_RenderPresent(Renderer);
//                    }
//                    else{
//                        rect.x = 1;
//                        rect.y = 1;
//                        SDL_RenderFillRect(Renderer, &rect);
//                        SDL_RenderPresent(Renderer);
//                    }
//                }
//            }
//        }
//    }
//    cout << endl <<"Game is Running";
//    bool quit = false;
//    while(!quit) {
//        while (SDL_PollEvent(&event)){
//            if(event.type == SDL_QUIT){
//                quit = true;
//            }
//            //printf("type = %d, key=%d\n", event.type, event.key);
//        }
//   }
//
//    SDL_DestroyRenderer(Renderer);
//    SDL_DestroyWindow(window);
//    SDL_Quit();
//    return 0;

}

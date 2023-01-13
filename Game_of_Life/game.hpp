//
//  game.hpp
//  Game_of_Life
//
//  Created by Gary Chen on 1/12/23.
//

#ifndef game_hpp
#define game_hpp

#include <stdio.h>
#include <iostream>
#include <SDL2/SDL_image.h>
#include <vector>
using namespace std;
struct block{
    int living_population = 0;
    int condition = 0;
};

struct Game {
    
    
    SDL_Window *window = NULL;
    SDL_Renderer *Renderer;
    SDL_Rect rect;
    public:vector <vector<block>> blocks;
    
    Game() {
        window = SDL_CreateWindow("Convey's_Game_of_Life", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 600, SDL_WINDOW_SHOWN);
        Renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
        vector<block> temp (30);
        vector <vector<block>>blocks_(40, temp);
        this->blocks = blocks_;
    }
    ~Game() {
        quit();
    }

    
    bool initialize();
    
    void drawGrids();
    
    void drawRect(int x, int y);
    
    void drawAllRects();
    
    void resetpopulation();
    
    void population();
    void life_or_dead();
    
    void game_loop();
    void test();
    void quit();
};

#endif /* game_hpp */

#include <stdio.h>
#include <stdbool.h> // since we dont have native support for bool in c
#include <SDL2/SDL.h>

bool is_running = false;
SDL_Window *window = NULL;
SDL_Renderer* renderer = NULL;

bool initialize_window(void) { 

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Error Initializing SDL: %s", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow(
        NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, 0
    );
    if (!window) {
        SDL_Log("Error creating SDL window: %s", SDL_GetError());
        SDL_Quit();
        return false;
    }

    renderer = SDL_CreateRenderer(window,-1, 0);
    if (!renderer) {
        SDL_Log("Error Creationg Renderer: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return false;
    }

    return true;
}

void setup(void){

}

void process_input(void){
    SDL_Event event;

    while(SDL_PollEvent(&event)){

        switch (event.type)
        {
        case SDL_QUIT:
            SDL_Log("Quit key was pressed. Exiting window.");
            SDL_Quit();
            is_running = false;        
            break;
        case SDL_KEYDOWN:
            if (event.key.keysym.sym == SDLK_ESCAPE){
                SDL_Log("Esc key was released. Exiting window.");
                SDL_Quit();
                is_running = false;
                break;
            }
        }
    }
}

void update(void){

}

void render(void){
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_RenderPresent(renderer);
}


int main(void) {

    is_running = initialize_window();

    // Game loop
    setup();
    while (is_running) {
        process_input();
        update();
        render();
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
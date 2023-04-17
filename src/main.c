#include <stdio.h>
#include <stdbool.h> // since we dont have native support for bool in c
#include <SDL2/SDL.h>

#include "display.h"

SDL_Window *window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;

uint32_t* color_buffer = NULL;
int window_width = 800, window_height = 600;

bool is_running = false;

void setup(void){
    // allocate memory for color buffer
    color_buffer = (uint32_t*) malloc(sizeof(color_buffer) * window_width * window_height);
    if (!color_buffer) {
       fprintf(stderr, "Error Allocating memory for color buffer");
    }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);
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
    
    draw_grid();
    draw_rectangle(300, 200, 300, 150, 0xffff00ff);
    render_texture();
    clear_color_buffer(0xFF000000);

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

    free_resources();
    return 0;
}
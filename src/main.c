#include <stdio.h>
#include <stdbool.h> // since we dont have native support for bool in c
#include <SDL2/SDL.h>
#include "display.h"
#include "vector.h"

bool is_running = false;

void setup(void){
    // allocate memory for color buffer
    color_buffer = (uint32_t*) malloc(sizeof(color_buffer) * window_width * window_height);
    if (!color_buffer) {
       fprintf(stderr, "Error Allocating memory for color buffer");
    }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);

    int point_count = 0;
    for (float x = -1; x <= 1; x+= 0.25){
        for (float y = -1; y <= 1; y+= 0.25){
            for (float z = -1; z <= 1; z+= 0.25){
                vec3_t point = {x, y, z};
                cube_points[point_count++] = point;
            }
        }
    }
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
    for (int i = 0; i < N_POINTS; i++)
    {
        vec2_t projected_point = perspective_projection(cube_points[i]);
        projected_points[i] = projected_point;
    }
    
}

void render(void){
    
    draw_grid();

    for (int i = 0; i < N_POINTS; i++){
        draw_rectangle(
            projected_points[i].x + window_width / 2, 
            projected_points[i].y + window_height / 2, 
            4, 
            4, 
            0xffffff00
        );
    }

    render_color_buffer();
    clear_color_buffer(0xFF000000);

    SDL_RenderPresent(renderer);
}

int main(void) {

    is_running = initialize_window();

    setup();
    // Game loop
    while (is_running) {
        process_input();
        update();
        render();
    }

    free_resources();
    return 0;
}
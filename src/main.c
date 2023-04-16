#include <stdio.h>
#include <stdbool.h> // since we dont have native support for bool in c
#include <SDL2/SDL.h>

bool is_running = false;
SDL_Window *window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* texture = NULL;

uint32_t* color_buffer = NULL;
int window_width = 800, window_height = 600;

bool initialize_window(void) { 

    if (SDL_Init(SDL_INIT_EVERYTHING) != 0) {
        SDL_Log("Error Initializing SDL: %s", SDL_GetError());
        return false;
    }

    // Use the full resolution of the screen
    SDL_DisplayMode DM;
    if (SDL_GetCurrentDisplayMode(0, &DM) != 0) {
        SDL_Log("Error Quering the DisplayMode: %s", SDL_GetError());
    }
    else {
        window_width = DM.w;
        window_height = DM.h;
    }
    
    window = SDL_CreateWindow(
        NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_BORDERLESS || SDL_WINDOW_FULLSCREEN);
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

void clear_color_buffer(uint32_t color){
    for (int y = 0; y < window_height; y++){
        for (int x = 0; x < window_width; x++){
            color_buffer[(window_width* y) + x] = color;
        }
    }
}

void draw_grid(void){
    for (int y = 0; y < window_height; y+=10) {
        for (int x = 0; x < window_width; x+=10) {
            color_buffer[window_width*y + x] = 0xff333333;
        }
    }
}

void draw_rectangle(int x, int y, int width, int height, uint32_t color){
    if (x <= window_width && x >= 0 && y <= window_height && y >= 0 && width <= window_width && height <= window_height)
    {   
        for (int row = x; row < x + height; row++){
            for (int col = y; col < y + width; col++){
                color_buffer[row * window_width + col] = color;
            }
        }
    }
}

void render_texture(void){
    SDL_UpdateTexture(texture, NULL, color_buffer, (int) (sizeof(uint32_t) * window_width));
    SDL_RenderCopy(renderer, texture, NULL, NULL);
}

void render(void){
    
    draw_grid();
    draw_rectangle(300, 200, 300, 150, 0xffff00ff);
    render_texture();
    clear_color_buffer(0xFF000000);

    SDL_RenderPresent(renderer);
}

void clean_up(void){
    free(color_buffer);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
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

    clean_up();
    return 0;
}
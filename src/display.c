#include "display.h"

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
        NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 
        window_width, window_height, SDL_WINDOW_BORDERLESS || SDL_WINDOW_FULLSCREEN);
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

void clear_color_buffer(uint32_t color){
    for (int y = 0; y < window_height; y++){
        for (int x = 0; x < window_width; x++){
            color_buffer[(window_width* y) + x] = color;
        }
    }
}

void draw_line(int x1, int y1, int x2, int y2, uint32_t color) {
    int delta_x = x2 - x1;
    int delta_y = y2 - y1;

    int side_length = (abs(delta_x) >= abs(delta_y)) ? abs(delta_x) : abs(delta_y);
    float x_inc = delta_x / (float)side_length;
    float y_inc = delta_y / (float)side_length;

    float current_x = x1;
    float current_y = y1;

    for (int i = 0; i < side_length; i++){
        draw_pixel(round(current_x), round(current_y), color);
        current_x += x_inc;
        current_y += y_inc;
    }
}

void draw_triangle(triangle_t triangle, uint32_t color){
    draw_line(triangle.points[0].x, triangle.points[0].y, triangle.points[1].x, triangle.points[1].y, color);
    draw_line(triangle.points[1].x, triangle.points[1].y, triangle.points[2].x, triangle.points[2].y, color);
    draw_line(triangle.points[2].x, triangle.points[2].y, triangle.points[0].x, triangle.points[0].y, color);
}

void draw_grid(void){
    for (int y = 0; y < window_height; y+=10) {
        for (int x = 0; x < window_width; x+=10) {
            color_buffer[window_width*y + x] = 0xff333333;
        }
    }
}

void draw_pixel(int x, int y, uint32_t color){
    if (x >= 0 && x < window_width && y >= 0 && y < window_height) {
        color_buffer[y* window_width + x] = color;
    }
}

void draw_rectangle(int x, int y, int width, int height, uint32_t color){

    for (int row = x; row < x + width; row++){
        for (int col = y; col < y + height; col++){
            draw_pixel(row, col, color);
        }
    }
}

void render_color_buffer(void){
    SDL_UpdateTexture(texture, NULL, color_buffer, (int) (sizeof(uint32_t) * window_width));
    SDL_RenderCopy(renderer, texture, NULL, NULL);
}

void free_resources(void){
    free(color_buffer);
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}
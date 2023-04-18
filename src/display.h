#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdio.h>
#include <stdbool.h> // since we dont have native support for bool in c
#include <SDL2/SDL.h>

extern SDL_Window *window ;
extern SDL_Renderer* renderer;
extern SDL_Texture* texture;
extern uint32_t* color_buffer;
extern int window_width; 
extern int window_height;

bool initialize_window(void);
void draw_grid(void);
void draw_pixel(int x, int y, uint32_t color);
void draw_rectangle(int x, int y, int width, int height, uint32_t color);
void clear_color_buffer(uint32_t color);
void render_color_buffer();
void free_resources(void);  

#endif
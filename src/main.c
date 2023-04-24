#include <stdio.h>
#include <stdbool.h> // since we dont have native support for bool in c
#include <SDL2/SDL.h>
#include "display.h"
#include "vector.h"
#include "mesh.h"

triangle_t triangle_to_render[N_MESH_FACES];
bool is_running = false;
uint32_t previous_frame_time = 0;

void setup(void){
    // allocate memory for color buffer
    color_buffer = (uint32_t*) malloc(sizeof(color_buffer) * window_width * window_height);
    if (!color_buffer) {
       fprintf(stderr, "Error Allocating memory for color buffer");
    }

    texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING, window_width, window_height);
    if (!texture) {
       fprintf(stderr, "Error creating texture");
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

    if (FRAME_TARGET_TIME >= SDL_GetTicks() - previous_frame_time){
        SDL_Delay(FRAME_TARGET_TIME - (SDL_GetTicks() - previous_frame_time));
    };

    // how many ms have passed since the last frame
    previous_frame_time = SDL_GetTicks();
    
    cube_rotation.x += 0.01;
    cube_rotation.y += 0.01;
    cube_rotation.z += 0.01;

    for (int i = 0; i < N_MESH_FACES; i++){
        vec3_t vertices[3];
        vertices[0] = meshVertices[meshFaces[i].a - 1];
        vertices[1] = meshVertices[meshFaces[i].b - 1];
        vertices[2] = meshVertices[meshFaces[i].c - 1];

        for (int j = 0; j < 3; j++){
            vec3_t transformed_vertex = rotate_vector_x(vertices[j], cube_rotation.x);
            transformed_vertex = rotate_vector_y(transformed_vertex, cube_rotation.y);
            transformed_vertex = rotate_vector_z(transformed_vertex, cube_rotation.z);

            // move the camera away
            transformed_vertex.z -= camera_positon.z;
            
            // the triangle which needs to be projected 
            triangle_to_render[i].points[j] = perspective_projection(transformed_vertex);

            // translate the points to the center of the screen
            triangle_to_render[i].points[j].x += window_width / 2;
            triangle_to_render[i].points[j].y += window_height / 2;
        }
    }    
}

void render(void){
    
    draw_grid();

    for (int i = 0; i < N_MESH_FACES; i++){
        triangle_t triangle = triangle_to_render[i];
        draw_rectangle(triangle.points[0].x, triangle.points[0].y, 3, 3, 0xffffff00);
        draw_rectangle(triangle.points[1].x, triangle.points[1].y, 3, 3, 0xffffff00);
        draw_rectangle(triangle.points[2].x, triangle.points[2].y, 3, 3, 0xffffff00);
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
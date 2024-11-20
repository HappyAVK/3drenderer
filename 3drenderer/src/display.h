#ifndef DISPLAY_H
#define DISPLAY_H

#include <stdint.h>
#include <stdbool.h>
#include <SDL2/SDL.h>

extern SDL_Window* window; //Pointer to SDL Window

extern SDL_Renderer* renderer;

extern uint32_t* color_buffer; // Allocates color_buffer to use the first position of 32bit memory

extern SDL_Texture* color_buffer_texture ; /// Mirror of the color buffer to allow rendering

extern int window_width;
extern int window_height;

bool initialize_window(void); ///Comment these later

void draw_grid(void); ///Comment these later

void draw_rect(int x, int y, int width, int height, uint32_t color); ///Comment these later

void render_color_buffer(void); ///Comment these later

void clear_color_buffer(uint32_t color); ///Comment these later

void destroy_window(void); ///Comment these later



#endif
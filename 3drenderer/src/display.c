#include "display.h"

SDL_Window* window = NULL; //Pointer to SDL Window

SDL_Renderer* renderer = NULL;

uint32_t* color_buffer = NULL; // Allocates color_buffer to use the first position of 32bit memory

SDL_Texture* color_buffer_texture = NULL; /// Mirror of the color buffer to allow rendering

int window_width = 800;
int window_height = 600;

/* Create an SDL window*/
bool initialize_window(void){
	if (SDL_Init(SDL_INIT_EVERYTHING) != 0){ //INIT_EVERYTHING is a boilerplate function 
		fprintf(stderr, "error initializing SDL.\n"); //stderr = standard error output
		return false;
	}
	/// Use SDL to query what is the fullscreen max width and height
	SDL_DisplayMode display_mode;
	SDL_GetCurrentDisplayMode(0, &display_mode); /// monitor by int and display mode(memory point)
	
	window_width = display_mode.w;
	window_height = display_mode.h;
	
	//Create an SDL Window, SDL_CreateWindow = title, PosX, PosY, and Width, Height)	
	window = SDL_CreateWindow(NULL, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, window_width, window_height, SDL_WINDOW_BORDERLESS);
	
	if (!window){
		fprintf(stderr, "Error creating SDL window.\n");
		return false;
	}
	//Create an SDL Renderer SDL_CreateRenderer(window, default display(-1 gets the first default monitor), default flags)
	renderer = SDL_CreateRenderer(window, -1, 0);
	
	if(!renderer){
		fprintf(stderr, "Error creating SDL window.\n");
		return false;
	}
	SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);
	return true;	
}

void draw_grid(void){
	for (int y = 0 ; y < window_height; y+= 10 ){
			for (int x = 0; x < window_width; x+= 10){
				
				color_buffer[(window_width * y) + x] = 0x80808000;
			}
		}
}

void draw_rect(int x, int y, int width, int height, uint32_t color) {
	
		 
	for (int i= 0; i < height; i++){
		
		for (int j = 0; j < width; j++){
			
			int current_x = x + i;
			int current_y = y +j;
			
			draw_pixel(current_x, current_y, color);
			//color_buffer[(j * window_width)+i] = color;
		}
	}
	
}

void draw_triangle(int x0, int y0, int x1, int y1, int x2, int y2, uint32_t colour){
	draw_line(x0, y0, x1, y1, colour);
	draw_line(x1, y1, x2, y2, colour);
	draw_line(x2, y2, x0, y0, colour);
}

void draw_line(int x0, int y0, int x1, int y1, int32_t colour){
	int delta_x = (x1 - x0);
	int delta_y = (y1 - y0);
	
	int side_length = abs(delta_x) >= abs(delta_y) ? abs(delta_x) : abs(delta_y);
	
	float x_inc = delta_x / (float)side_length;
	float y_inc = delta_y / (float)side_length;
	
	float current_x = x0;
	float current_y = y0;
	
	for (int i = 0; i <= side_length; i++){
		draw_pixel(round(current_x), round(current_y), colour);
		current_x += x_inc;
		current_y += y_inc;
	}
}

void draw_pixel(int x, int y, uint32_t colour){
	if (x >= 0 && x < window_width && y>= 0 && y < window_height){
		color_buffer[(window_width * y + x)] = colour;
	}
}

void render_color_buffer(void){
	/// Copy the colour buffer to the texture for rendering
	///args: texture, rect, pixels(what we are copying), pitch(number of colors in a row)
	SDL_UpdateTexture(color_buffer_texture, NULL, color_buffer,
	(int)window_width * sizeof(uint32_t));
	
	//SDL render copy = renders the updated texture
	SDL_RenderCopy(renderer, color_buffer_texture, NULL, NULL);
}

void clear_color_buffer(uint32_t color) {
	for (int y = 0 ; y < window_height; y++ ){
		for (int x = 0; x < window_width; x++){
			color_buffer[(window_width * y) + x] = color; 
			//go through each row column and assign color
		}
	}
	
}

void destroy_window(void){
	free(color_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit(); //These functions will free memory and remove all SDL instances that we created

}



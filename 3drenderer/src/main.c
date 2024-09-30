#include <stdio.h> ///Compiller
#include <SDL2/SDL.h>
#include <stdbool.h>
#include <stdint.h>
///int main(void){
///	printf("Hello, World!\n");
///	return 0;
///
bool is_running = false;

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
void setup(void){
	color_buffer = (uint32_t*) malloc(sizeof(uint32_t) * window_width * window_height);
		//allocates the required bytes to memory to hold the color buffer
	if(!color_buffer){
		fprintf(stderr, "error allocating color buffer to memory\n");
		//return false; //TODO: MAKE THIS WORK
	}
	///Creating an SDL texture to display the colour. args=render, pixelformat, streaming(changes)
	color_buffer_texture = SDL_CreateTexture(renderer, 
	SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STREAMING,
	window_width, window_height);
}

void update(void){
	
}

void draw_grid(void){
	for (int y = 0 ; y < window_height; y+= 10 ){
			for (int x = 0; x < window_width; x+= 10){
				
				color_buffer[(window_width * y) + x] = 0x80808000;
			}
		}
}

void draw_rect(int x, int y, int width, int height, uint32_t color) {
	
		 
	for (int i= x; i < height+x; i++){
		
		for (int j = y; j < width+y; j++){
			
			
			color_buffer[(j * window_width)+i] = color;
		}
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

void render(void){
	SDL_SetRenderDrawColor(renderer, 255, 0 ,0 ,255);
	SDL_RenderClear(renderer);
	
	render_color_buffer();
	
	clear_color_buffer(0xFFFFFF00);
	draw_grid();
	draw_rect(345, 400, 120, 200, 0x00FF0000);
	
	SDL_RenderPresent(renderer);
}

void process_input(void){
	SDL_Event event;
	SDL_PollEvent(&event);
	
	switch (event.type) {
		case SDL_QUIT:
			is_running = false;
			break;
		case SDL_KEYDOWN:
			if (event.key.keysym.sym == SDLK_ESCAPE)
				is_running = false;
			break;
	}
}

void destroy_window(void){
	free(color_buffer);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit(); //These functions will free memory and remove all SDL instances that we created
		
}

int main(void){
	
	is_running = initialize_window(); 
	
	setup();
	while(is_running){
		process_input(); //check for inputs
		update();	//update the positions of objects to render based on inputs
		render();	//render 
	}
	
	destroy_window();
	
	return 0;
}
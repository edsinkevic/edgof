
#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "gof.h"


#define GRID_CELL_SIZE 50
#define GRID_WIDTH 10
#define GRID_HEIGHT 10

#define WINDOW_WIDTH (GRID_WIDTH * GRID_CELL_SIZE) + 1
#define WINDOW_HEIGHT (GRID_HEIGHT * GRID_CELL_SIZE) + 1


int main(int argc, char *argv[]) {
  gof_bear(5, 5);
  gof_bear(5, 4);
  gof_bear(5, 6);
  gof_bear(4, 5);

  gof_bear(6, 7);

  gof_bear(8, 7);

  gof_bear(2, 3);
  gof_bear(3, 2);
  gof_bear(5, 6);
  gof_bear(4, 5);

  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;
  SDL_Surface *window_surface = NULL;
  SDL_Surface *image_surface = NULL;


  SDL_Color grid_background = {22, 22, 22, 255}; // Barely Black
  SDL_Color grid_line_color = {44, 44, 44, 255}; // Dark grey
  SDL_Color grid_cursor_ghost_color = {44, 44, 44, 255};
  SDL_Color grid_cursor_color = {255, 255, 255, 255}; // White

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    fprintf(
        stderr, 
        "Could not initialize video: %s\n",
        SDL_GetError());
    goto main_error;
  }

  if (SDL_CreateWindowAndRenderer(
      WINDOW_WIDTH,
      WINDOW_HEIGHT,
      0,
      &window,
      &renderer) < 0) {
    fprintf(stderr,
        "Could not create window and renderer: %s\n",
        SDL_GetError());
    goto main_error;
  }

  SDL_SetWindowTitle(window, "GAME OF LIFE");

  SDL_bool quit = SDL_FALSE;

  while (!quit) {

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_KEYDOWN:
          if (event.key.keysym.sym == SDLK_q) {
            quit = SDL_TRUE;
          }
          if (event.key.keysym.sym == SDLK_w) {
            gof();
          }
          break;
      }
    }

    SDL_SetRenderDrawColor(
        renderer,
        grid_background.r,
        grid_background.g,
        grid_background.b,
        grid_background.a);

    SDL_RenderClear(renderer);
    
    SDL_SetRenderDrawColor(
        renderer,
        grid_line_color.r,
        grid_line_color.g,
        grid_line_color.b,
        grid_line_color.a);

    for (
        int x = 0;
        x < 1 + GRID_WIDTH * GRID_CELL_SIZE;
        x += GRID_CELL_SIZE) {
      SDL_RenderDrawLine(renderer, x, 0, x, WINDOW_HEIGHT);
    }

    for (
        int y = 0;
        y < 1 + GRID_HEIGHT * GRID_CELL_SIZE;
        y += GRID_CELL_SIZE) {
      SDL_RenderDrawLine(renderer, 0, y, WINDOW_WIDTH, y);
    }

    SDL_SetRenderDrawColor(
        renderer,
        grid_cursor_color.r,
        grid_cursor_color.g,
        grid_cursor_color.b,
        grid_cursor_color.a);


    for (int col = 0; col < N; col++) {
      for (int row = 0; row < N; row++) {
        if (gof_is_alive(row, col)) {
          SDL_Rect grid_cursor = {
            .x = col * GRID_CELL_SIZE, 
            .y = row * GRID_CELL_SIZE,
            .w = GRID_CELL_SIZE,
            .h = GRID_CELL_SIZE
          };
          SDL_RenderFillRect(renderer, &grid_cursor);
        }
      }
    }


    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;


main_error:
  if (renderer) {
    SDL_DestroyRenderer(renderer);
  }

  if (window) {
    SDL_DestroyWindow(window);
  }

  return EXIT_FAILURE;
}

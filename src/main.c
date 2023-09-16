#include <stdio.h>
#include <assert.h>
#include <time.h>
#include <SDL2/SDL.h>
#include "gof.h"


#define GRID_CELL_SIZE 3
#define GRID_WIDTH GOF_WIDTH
#define GRID_HEIGHT GOF_HEIGHT

#define WINDOW_WIDTH (GRID_WIDTH * GRID_CELL_SIZE) + 1
#define WINDOW_HEIGHT (GRID_HEIGHT * GRID_CELL_SIZE) + 1

char gof_handle_input();
void gof_render_background(SDL_Renderer *renderer);
void gof_render_grid(SDL_Renderer *renderer);
void gof_render_lives(SDL_Renderer *renderer);


int main(int argc, char *argv[]) {
  SDL_Window *window = NULL;
  SDL_Renderer *renderer = NULL;

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

  while (gof_handle_input()) {
    gof_render_background(renderer);
    gof_render_grid(renderer);
    gof_render_lives(renderer);
    SDL_RenderPresent(renderer);
  }

  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();

  return EXIT_SUCCESS;


main_error:
  if (renderer) {
    SDL_DestroyRenderer(renderer);
    renderer = NULL;
  }

  if (window) {
    SDL_DestroyWindow(window);
    window = NULL;
  }

  return EXIT_FAILURE;
}

SDL_bool draw_click_hold = SDL_FALSE;
SDL_bool delete_click_hold = SDL_FALSE;

void handle_mouse_state(
    SDL_bool draw_click_hold,
    SDL_bool delete_click_hold,
    Sint32 x,
    Sint32 y) {

  if (draw_click_hold) {
    gof_bear(y / GRID_CELL_SIZE, x / GRID_CELL_SIZE);
  } else if(delete_click_hold) {
    gof_kill(y / GRID_CELL_SIZE, x / GRID_CELL_SIZE);
  }

}

char gof_handle_input() {
  SDL_bool should_continue = SDL_TRUE;
  SDL_Event event;
  SDL_MouseButtonEvent e;
  SDL_MouseMotionEvent m;
  
  while (SDL_PollEvent(&event)) {
    switch (event.type) {
      case SDL_KEYDOWN:
        if (event.key.keysym.sym == SDLK_q) {
          should_continue = SDL_FALSE;
        }
        
        if (event.key.keysym.sym == SDLK_w) {
          gof();
        }
        break;

      case SDL_MOUSEBUTTONDOWN:
        e = event.button;
        if (e.button == SDL_BUTTON_LEFT) {
          draw_click_hold = SDL_TRUE;
        }

        if (e.button == SDL_BUTTON_RIGHT) {
          delete_click_hold = SDL_TRUE;
        }

        handle_mouse_state(
            draw_click_hold,
            delete_click_hold,
            e.x,
            e.y);

        break;

      case SDL_MOUSEBUTTONUP:
        e = event.button;

        if (e.button == SDL_BUTTON_LEFT) {
          draw_click_hold = SDL_FALSE;
        }

        if (e.button == SDL_BUTTON_RIGHT) {
          delete_click_hold = SDL_FALSE;
        }

        break;

      case SDL_MOUSEMOTION:
        m = event.motion;

        handle_mouse_state(
            draw_click_hold,
            delete_click_hold,
            m.x,
            m.y);

        break;

    }
  }

  return should_continue;
}

void gof_render_background(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 22, 22, 22, 255);
  SDL_RenderClear(renderer);
}

void gof_render_grid(SDL_Renderer *renderer) {
  SDL_SetRenderDrawColor(renderer, 44, 44, 44, 255);

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
}

void gof_render_lives(SDL_Renderer *renderer) {
  SDL_Rect grid_cursor = {
    .x = 0, 
    .y = 0,
    .w = GRID_CELL_SIZE,
    .h = GRID_CELL_SIZE
  };

  SDL_SetRenderDrawColor(renderer, 186, 82, 211, 255);

  for (int col = 0; col < GOF_WIDTH; col++) {
    for (int row = 0; row < GOF_HEIGHT; row++) {
      if (gof_is_alive(row, col)) {
        grid_cursor.x = col * GRID_CELL_SIZE;
        grid_cursor.y = row * GRID_CELL_SIZE;
        SDL_RenderFillRect(renderer, &grid_cursor);
      }
    }
  }
}

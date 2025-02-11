#include <stdio.h>
#include <assert.h>
#include "gof.h"
#include <raylib.h>
#include <stdlib.h>

#define GRID_CELL_SIZE 10
#define GRID_WIDTH GOF_WIDTH
#define GRID_HEIGHT GOF_HEIGHT

#define WINDOW_WIDTH (GRID_WIDTH * GRID_CELL_SIZE) + 1
#define WINDOW_HEIGHT (GRID_HEIGHT * GRID_CELL_SIZE) + 1

char gof_handle_input();

void gof_render_grid();

void gof_render_lives();

int main(int argc, char *argv[]) {
    InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "GAME OF LIFE");
    SetTargetFPS(144);

    while (gof_handle_input()) {
        BeginDrawing();
        ClearBackground((Color){22, 22, 22, 255});
        gof_render_grid();
        gof_render_lives();
        EndDrawing();
    }

    CloseWindow();

    return EXIT_SUCCESS;
}

char gof_handle_input() {
    bool should_continue = true;

    if (IsKeyDown(KEY_Q)) {
        should_continue = false;
    }

    if (IsKeyDown(KEY_W)) {
        gof();
    }

    Vector2 mouse = GetMousePosition();

    if (IsMouseButtonDown(MOUSE_BUTTON_LEFT)) {
        gof_bear(mouse.y / GRID_CELL_SIZE, mouse.x / GRID_CELL_SIZE);
    }

    if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
        gof_kill(mouse.y / GRID_CELL_SIZE, mouse.x / GRID_CELL_SIZE);
    }

    return should_continue;
}

void gof_render_grid() {
    const Color draw_color = {44, 44, 44, 255};

    for (
        int x = 0;
        x < 1 + GRID_WIDTH * GRID_CELL_SIZE;
        x += GRID_CELL_SIZE) {
        DrawLineV((Vector2){x, 0}, (Vector2){x, WINDOW_HEIGHT}, draw_color);
    }

    for (
        int y = 0;
        y < 1 + GRID_HEIGHT * GRID_CELL_SIZE;
        y += GRID_CELL_SIZE) {
        DrawLineV((Vector2){0, y}, (Vector2){WINDOW_WIDTH, y}, draw_color);
    }
}

void gof_render_lives() {
    Rectangle rectangle = {
        .x = 0,
        .y = 0,
        .width = GRID_CELL_SIZE,
        .height = GRID_CELL_SIZE
    };

    for (int col = 0; col < GOF_WIDTH; col++) {
        for (int row = 0; row < GOF_HEIGHT; row++) {
            if (gof_is_alive(row, col)) {
                rectangle.x = col * GRID_CELL_SIZE;
                rectangle.y = row * GRID_CELL_SIZE;
                DrawRectangleRec(rectangle, (Color){186, 82, 211, 255});
            }
        }
    }
}

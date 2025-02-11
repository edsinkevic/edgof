#pragma once
#define GOF_WIDTH 60
#define GOF_HEIGHT 60
#define ALIVE 1
#define DEAD 0

void gof_bear(int row, int col);
char gof_is_alive(int row, int col);
void gof_kill(int row, int col);
void gof();

#include "gof.h"
#include <stdio.h>

char board[GOF_N * GOF_N] = {DEAD};

int id(int row, int col) {
  return row * GOF_N + col;
}

char cell_at(int row, int col) {
  return board[id(row, col)];
}

void kill(int row, int col) {
  board[id(row, col)] = DEAD;
}

void gof_bear(int row, int col) {
  board[id(row, col)] = ALIVE;
}

void print_board() {
  for (int col = 0; col < GOF_N; col++) {
    for (int row = 0; row < GOF_N; row++) {
      printf("%d  ", board[id(row, col)]);
    }
    printf("\n");
  }
  printf("\n");
}

char in_bounds(int n) {
  return n >= 0 && n < GOF_N;
}

char gof_is_alive(int row, int col) {
  return cell_at(row, col) == ALIVE;
}

int count_neighbors(int row, int col) {
  char neighbors = 0;

  for (int _row = row - 1; _row <= row + 1; _row++) {
    for (int _col = col - 1; _col <= col + 1; _col++) {
      if (
          (_row != row || _col != col) && 
          in_bounds(row) && in_bounds(col) && 
          gof_is_alive(_row, _col)
          ) {
        neighbors++;
      }
    }
  }


  return neighbors;
}


void gof() {
  for (int col = 0; col < GOF_N; col++) {
    for (int row = 0; row < GOF_N; row++) {
      
      int count = count_neighbors(row, col);
      int alive = gof_is_alive(row, col);
      if (!alive && count == 3) {
        gof_bear(row, col);
      }

      if (alive && (count < 2 || count > 3)) {
        kill(row, col);
      } 
    }
  }
}

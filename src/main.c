
#include<stdio.h>
#include<assert.h>

#define N 10

#define ALIVE 1
#define DEAD 0

char board[N * N] = {DEAD};

int id(int row, int col) {
  return row * N + col;
}

char cell_at(int row, int col) {
  return board[id(row, col)];
}

void kill(int row, int col) {
  board[id(row, col)] = DEAD;
}

void bear(int row, int col) {
  board[id(row, col)] = ALIVE;
}

void print_board() {
  for (int col = 0; col < N; col++) {
    for (int row = 0; row < N; row++) {
      printf("%d  ", board[id(row, col)]);
    }
    printf("\n");
  }
  printf("\n");
}

char in_bounds(int n) {
  return n >= 0 && n < N;
}

char is_alive(int row, int col) {
  return cell_at(row, col) == ALIVE;
}

int count_neighbors(int row, int col) {
  char neighbors = 0;

  for (int _row = row - 1; _row <= row + 1; _row++) {
    for (int _col = col - 1; _col <= col + 1; _col++) {
      if (
          (_row != row || _col != col) && 
          in_bounds(row) && in_bounds(col) && 
          is_alive(_row, _col)
          ) {
        neighbors++;
      }
    }
  }


  return neighbors;
}


void gof() {
  //1. Any live cell with fewer than two live neighbours dies, as if by underpopulation.
  //2. Any live cell with two or three live neighbours lives on to the next generation.
  //3. Any live cell with more than three live neighbours dies, as if by overpopulation.
  //4. Any dead cell with exactly three live neighbours becomes a live cell, as if by reproduction.

  for (int col = 0; col < N; col++) {
    for (int row = 0; row < N; row++) {
      
      int count = count_neighbors(row, col);
      int alive = is_alive(row, col);
      if (!alive && count == 3) {
        printf("Birthing [%d, %d]\n", row, col);

        bear(row, col);
      }

      if (alive && (count < 2 || count > 3)) {
        printf("Killing [%d, %d]\n", row, col);
        kill(row, col);
      } 
    }
  }
}

int main() {
  bear(5, 4);
  bear(5, 5);
  bear(5, 6);
  bear(4, 5);
  bear(4, 4);
  bear(4, 3);

  for (int i = 0; i < 5; i++) {
    print_board();
    gof();
  }

  return 0;
}


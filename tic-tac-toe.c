#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

char **create_board(int size)
{
  char **board = (char **)calloc(size, sizeof(char *));
  for (int i = 0; i < size; i++)
  {
    board[i] = (char *)calloc(size, sizeof(char));
    memset(board[i], ' ', size);
  }
  return board;
}

void print_board(char **board, int size)
{
  for (int i = 0; i < size; i++)
  {
    for (int j = 0; j < size; j++)
    {
      printf("%c", board[i][j]);
      if (j != size - 1)
        printf("|");
    }
    printf("\n");
    if (i != size - 1)
    {
      for (int j = 0; j < size; j++)
      {
        printf("-");
        if (j != size - 1)
          printf("+");
      }
      printf("\n");
    }
  }
}

int main()
{
  int size = 3;
  char **board = create_board(size);
  print_board(board, size);
  for (int i = 0; i < size; i++)
    free(board[i]);
  free(board);
}
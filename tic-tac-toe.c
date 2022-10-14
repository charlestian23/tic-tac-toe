#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define true 1 
#define false 0 

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

int is_win(char** board, int size, int moveRow, int moveColumn)
{
  char symbol = board[moveRow][moveColumn];

  // Check row
  for (int i = 0; i < size; i++)
    if (board[moveRow][i] != symbol)
      return false;
  
  // Check column
  for (int i = 0; i < size; i++)
    if (board[i][moveColumn] != symbol)
      return false;

  // Check diagonal (if applicable)
  if (moveRow == moveColumn)
    for (int i = 0; i < size; i++)
      if (board[i][i] != symbol)
        return false;

  return true;
}

int is_tie(char** board, int size, int moveRow, int moveColumn)
{
  for (int i = 0; i < size; i++)
    for (int j = 0; j < size; j++)
      if (board[i][j] == ' ')
        return false;
  return !is_win(board, size, moveRow, moveColumn);
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
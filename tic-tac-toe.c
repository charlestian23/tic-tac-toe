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
  // Print column labels
  printf(" ");
  for (int i = 0; i < size; i++)
    printf(" %d", i + 1);
  printf("\n");

  for (int i = 0; i < size; i++)
  {
    // Print row label
    printf("%d ", i + 1);

    // Print board item
    for (int j = 0; j < size; j++)
    {
      printf("%c", board[i][j]);

      // Print vertical lines
      if (j != size - 1)
        printf("|");
    }
    printf("\n");

    // Print horizontal lines
    if (i != size - 1)
    {
      printf("  ");
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

char swap_piece(char current_piece)
{
  if (current_piece == 'X')
    return 'O';
  return 'X';
}

int main()
{
  int size = 3;
  char **board = create_board(size);
  int move_counter = 1;
  char current_piece = 'X';

  // Assume that the players enter valid integers
  while (move_counter < size * size)
  {
    int player_number = move_counter % 2;
    int row = -1;
    int column = -1;
    printf("Player %d, enter a row: ", player_number);
    scanf("%d", &row);
    while (row < 0 || row > size)
    {
      printf("Row %d is not a valid row. Please try again...\n", row);
      printf("Player %d, enter a different row: ", player_number);
      scanf("%d", &row);
    }
    printf("Player %d, enter a column: ", player_number);
    scanf("%d", &column);
    while (column < 0 || column > size)
    {
      printf("Column %d is not a valid row. Please try again...\n", row);
      printf("Player %d, enter a different column: ", player_number);
      scanf("%d", &column);
    }
    printf("%d %d\n", row, column);
  }

  print_board(board, size);
  for (int i = 0; i < size; i++)
    free(board[i]);
  free(board);

  return EXIT_SUCCESS;
}
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

int is_win(char **board, int size, int move_row, int move_column)
{
  char symbol = board[move_row - 1][move_column - 1];

  // Check row
  int win = true;
  for (int i = 0; i < size; i++)
    if (board[move_row - 1][i] != symbol)
    {
      win = false;
      break;
    }
  if (win)
    return true;

  // Check column
  win = true;
  for (int i = 0; i < size; i++)
    if (board[i][move_column - 1] != symbol)
    {
      win = false;
      break;
    }
  if (win)
    return true;

  // Check main diagonal (if applicable)
  win = true;
  if (move_row == move_column)
  {
    for (int i = 0; i < size; i++)
      if (board[i][i] != symbol)
      {
        win = false;
        break;
      }
    if (win)
      return true;
  }

  // Check anti-diagonal (if applicable)
  win = true;
  if (move_row + move_column - 1 == size)
  {
    for (int i = 0; i < size; i++)
      if (board[i][size - 1 - i] != symbol)
      {
        win = false;
        break;
      }
    if (win)
      return true;
  }

  return false;
}

int is_tie(char **board, int size, int moveRow, int moveColumn)
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

int get_input(char* dimension, int player_number, int size)
{
  int result;
  printf("Player %d, enter a %s: ", player_number, dimension);
  scanf("%d", &result);
  while (result < 0 || result > size)
  {
    printf("%d is not a valid %s number. Please try again...\n", result, dimension);
    printf("Player %d, enter a different %s: ", player_number, dimension);
    scanf("%d", &result);
  }
  return result;
}

int main()
{
  int size = 3;
  char **board = create_board(size);
  int move_counter = 0;
  char current_piece = 'X';

  int row = -1;
  int column = -1;

  // Assume that the players enter valid integers
  while (move_counter < size * size)
  {
    int player_number = move_counter % 2 + 1;

    print_board(board, size);
    printf("\n");

    do
    {
      row = get_input("row", player_number, size);
      column = get_input("column", player_number, size);

      if (board[row - 1][column - 1] != ' ')
        printf("That is not an empty spot on the board. Please try again...\n\n");
      else
        printf("\n");

    } while (board[row - 1][column - 1] != ' ');

    // Place the piece on the board
    board[row - 1][column - 1] = current_piece;

    if (is_win(board, size, row, column))
    {
      print_board(board, size);
      printf("Player %d wins!\n", player_number);
      move_counter = 10;
    }

    if (current_piece == 'X')
      current_piece = 'O';
    else
      current_piece = 'X';
    move_counter++;
  }

  if (is_tie(board, size, row, column))
  {
    print_board(board, size);
    printf("Tie game.\n");
  }

  for (int i = 0; i < size; i++)
    free(board[i]);
  free(board);

  return EXIT_SUCCESS;
}
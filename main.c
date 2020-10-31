#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

/* Created by Alk4de
 * Date: 2020-10-31
 *
 * A simple connect 4 game.
 */

#define O 2
#define X 1
#define BLANK 0
#define ROWS 6
#define COLUMNS 7

int **init_field( void );
int human_input( void );
void print_field( int **field );
int **insert_marker( int **field, int column, int player);
bool valid_choice( int **field, int column );
bool game_over( int **field, int player );
bool check_coord( int **field, int column , int row, int player);
int check_dir( int **field, int column, int row, int player, int x_offset, int y_offset);
bool check_boundaries( int column, int row );

int main( void ) {


  int **field = init_field();
  int col = 0;
  int current_player = X;

  while (1) {

    print_field(field);

    if ((col = human_input()) == -1) {
      break;
    } else if (col == 0) {
      printf("Invalid input\n");
    } else {

      if (valid_choice(field, col-1)) {
        
        field = insert_marker(field, col-1, current_player);
       
        /* check if game is over */
        if (game_over(field, current_player)) {
          print_field(field);
          printf("Game finished!\n");
          break;
        }
        /* switch player */
        if (current_player == X) {
          current_player = O;
        } else {
          current_player = X;
        }

      } else {
        printf("Invalid choice\n");
      }
    }
  }
 
  for (int i = 0; i < ROWS; i++) {
    free(field[i]);
  }
  free(field);
  return 0;
}

/* game_over
 * iterates through field to find if a player has won
 * true if player won
 * false otherwise
 */
bool game_over( int **field, int player ) {
  
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      if (check_coord(field, j, i, player)) {
        return true;
      }
    }
  }
  return false;
}


/* check_coord
 * checks a coordinate if it was a winning move
 * return:
 *  true if a specified coordinate is part of a streak of four markers
 *  false otherwise
 */
bool check_coord( int **field, int column, int row, int player) {
  /* Check each direction */
  for (int i = -1; i <= 1; i++) {
    for (int j = -1; j <= 1; j++) {
      if (j != 0 || i != 0) {
        if (check_dir(field, column, row, player, j, i) >= 4) {
          return true;
         }
      }
    }
  }
  return false;
}

/* check_dir
 * counts the amount of found matching markers, until other players marker is found
 * return:
 *  amount of markers of @player
 */
int check_dir( int **field, int column, int row, int player, int x_offset, int y_offset) {

  int streak = 0;
  
  while(check_boundaries(column, row)) {
    if (field[row][column] == player) {
      streak++;
    } else {
      return streak;
    }
    column += x_offset;
    row += y_offset;
  }
  return streak;
}


/* check_boundaries
 * checks if given column and row is withing the boundaries
 */
bool check_boundaries(int column, int row) {
  if (column < 0 || column > COLUMNS-1) {
    return false;
  }
  if (row < 0 || row > ROWS-1) {
    return false;
  }
  return true;
}

/* insert_marker
 * Inserts a marker as far down in the column as possible
 * return:
 *  modified field
 */
int **insert_marker( int **field, int column, int player ) {
  
  for (int i = 0; i < ROWS-1; i++) {
    if (field[i+1][column] != BLANK) {
      field[i][column] = player;
      return field; 
    }
  }
  field[ROWS-1][column] = player;
  return field;
}


/* valid_choice
 * returns whether a choice is in a blank column or not
 * MAKE SURE GIVEN COLUMN IS WITHIN THE BOUNDARIES
 * return:
 *  true if top-most coordinate in column is BLANK
 */
bool valid_choice( int **field, int column ) {
  return (field[0][column] == BLANK);
}

/* init_field
 * creates a field
 * return:
 *  a field
 */
int **init_field( void ) {

  int **field = calloc(ROWS, sizeof(double));

  for (int i = 0 ; i < ROWS; i++) {
    field[i] = calloc(COLUMNS, sizeof(double));
  }
  return field;
}

/* human_input
 * gets human input
 * return:
 *  -1 if input was to exit
 *  0 if input was out of range
 *  otherwise a number from 1 to 7.
 */
int human_input( void ) {
  fprintf(stderr, "Where do you want to place your marker? (1-7)\n'e' to exit\n");

  char c;
  char *str = fgets(&c, 1024, stdin);
  c = *str;
  if (c == 'e') {
    return -1;
  } else {
    int ans = strtol(&c, NULL, 10);
    if (ans < 1 || ans > 7) {
      return 0;
    } else {
      return ans;
    }
  }
}

/* print_field
 * print the field
 */
void print_field( int **field ) {
  
  for (int i = 0; i < ROWS; i++) {
    for (int j = 0; j < COLUMNS; j++) {
      printf("|");
      if (field[i][j] == BLANK) {
        printf("   ");
      } else if (field[i][j] == X) {
        printf(" X ");
      } else {
        printf(" O ");
      }
    }
    printf("|");
    printf("\n");
  }
}

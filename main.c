#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

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
bool game_over( int **field );
bool game_over_column( int **field, int column );
bool check_straight( int **field, int column );
bool check_diagonal( int **field, int column );

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
        
        if (current_player == X) {
          current_player = O;
        } else {
          current_player = X;
        }

      } else {
        printf("Invalid choice\n");
      }
    }
    
    if (game_over(field)) {
      print_field(field);
      printf("Game finished!\n");
      break;
    }
  }

  return 0;
}


bool game_over( int **field ) {
  
  for (int i = 0; i < COLUMNS; i++) {
    if (check_straight(field, i)) {
      return true;
    }
  }
  return false;
}

bool check_straight( int **field, int column ) {
  int x = 0;
  int o = 0;

  for (int i = 0; i < ROWS; i++) {
    if (field[i][column] == X) {
      x++;
      if (x == 4) {
        return true;
      }
    } else {
      x = 0;
    }
    if (field[i][column] == O) {
      o++;
      if (o == 4) {
        return true;
      }
    } else {
      o = 0;
    }
  }
  return false;
}


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



bool valid_choice( int **field, int column ) {
  return (field[0][column] == BLANK);
}

int **init_field( void ) {

  int **field = calloc(COLUMNS, sizeof(**field));

  for (int i = 0 ; i < ROWS; i++) {
    field[i] = calloc(COLUMNS, sizeof(*field));
  }
  //print_field(field);
  return field;
}

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

void print_field( int **field ) {
  
  printf("| 1 | 2 | 3 | 4 | 5 | 6 | 7 |\n");
  printf(" ___ ___ ___ ___ ___ ___ ___ \n");

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

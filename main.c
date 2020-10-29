#include<stdio.h>
#include<stdbool.h>
#include<stdlib.h>

#define O 2
#define X 1
#define BLANK 0
#define ROWS 6
#define COLUMNS 7

bool vs_computer( void );
int **init_field( void );



int main( void ) {

  bool b = vs_computer();

  if (b) {
    printf("Chose vs player\n");
  } else {
    printf("Chose vs computer\n");
  }

  int **field = init_field();



  return 0;
}



bool vs_computer( void ) {

  fprintf(stderr, "(enter) to play vs another player, anything else to play vs computer\n");

  char c = fgetc(stdin);

  if (c == '\n') {
    return true;
  } else {
    return false;
  }
}


int **init_field( void ) {

  int **field = calloc(COLUMNS, sizeof(**field));

  for (int i = 0 ; i < COLUMNS; i++) {
    printf("I wonder\n");
    field[i] = calloc(ROWS, sizeof(**field));
    for (int j = 0;j < ROWS; j++) {
      printf("%d\n",j);
      field[i][j] = BLANK;
    }
  }
  return field;
}

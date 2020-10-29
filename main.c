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
int human_input( void );
void print_field( int **field );

int main( void ) {

  bool b = vs_computer();

  if (b) {
    printf("Chose vs player\n");
  } else {
    printf("Chose vs computer\n");
  }

  int **field = init_field();

  int col = 0;

  while (1) {

    print_field(field);

    if ((col = human_input()) == -1) {
      break;
    }
    printf("%d\n",col);
  }

  return 0;
}



bool vs_computer( void ) {

  fprintf(stderr, "(enter) to play vs another player, anything else to play vs computer\n");

  char c = fgetc(stdin);
  fflush(stdin);

  if (c == '\n') {
    return true;
  } else {
    return false;
  }
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

/*Santiago Echevarria*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MINEVAL 9

#define PUTSC(c, f) printf("\033[%dm" f "\033[0m", 30 + c)

void main() {
  // Declare variable
  int i, j, k;
  int dimension, num_mines, num_visibles = 0, num_free = 0;
  int print_map = 1, row, col;
  int level;
  int cells;
  int perdiste = 0;
  int ganaste = 0;

  char MINESYMBOL = '*';
  char EMPTYSYMBOL = '_';
  char NOTVISIBLESYMBOL = ' ';

  int MAX_SIZE = 40;


      int MIN_SIZE              = 5;

  // Print initial menu
  printf("\n\033[34mTERMINAL MINESWEEPER by esantix\n\033[0m");

  printf("\n Choose map size [%d-%d]: ",MIN_SIZE,MAX_SIZE);
  scanf("%d", &dimension);
  while 
  
  
  
  
  (dimension < 5 
  
  || dimension > 40) {
    printf("Choose between [%d-%d]: ", MIN_SIZE,MAX_SIZE);
    scanf("%d", &dimension);
  };

  printf(" Level [1-5]: ");
  scanf("%d", &level);
  while (level < 1 || level > 5) {
    printf("Choose between [1-5]: ");
    scanf("%d", &level);
  };

  // Level to number of mines calculation
  cells = dimension * dimension;
  num_mines = (int)(dimension * dimension * level * 0.05);
  num_free = cells - num_mines;

  // Map values
  int MAP[dimension + 1][dimension + 1];
  int VISIBLE[dimension + 1][dimension + 1];
  int a = 0;

  // Start zeros
  num_free = dimension * dimension - num_mines;
  for (i = 0; i <= dimension; i++) {
    for (j = 0; j <= dimension; j++) {
      VISIBLE[i][j] = 0;
      MAP[i][j] = 0;
    };
  };

  // Place mines randomly
  for (i = 1; i <= num_mines; i++) {
    j = 1 + rand() % dimension;
    k = 1 + rand() % dimension;
    if (MAP[j][k] == MINEVAL) {
      i--;
    };
    MAP[j][k] = MINEVAL;
  };

  // Set non-bomb cell values
  for (i = 1; i <= dimension; i++) {
    for (j = 1; j <= dimension; j++) {
      VISIBLE[i][j] = 0;
      if (MAP[i][j] != MINEVAL) {
        a = 0;
        a = a + (int)(MAP[i - 1][j - 1] == MINEVAL);  // up-left
        a = a + (int)(MAP[i - 1][j] == MINEVAL);      // up
        a = a + (int)(MAP[i - 1][j + 1] == MINEVAL);  // up-right
        a = a + (int)(MAP[i][j - 1] == MINEVAL);      // left
        a = a + (int)(MAP[i][j + 1] == MINEVAL);      // right
        a = a + (int)(MAP[i + 1][j - 1] == MINEVAL);  // down-left
        a = a + (int)(MAP[i + 1][j] == MINEVAL);      // down
        a = a + (int)(MAP[i + 1][j + 1] == MINEVAL);  // down-right
        MAP[i][j] = (int)a;
      };
    };
  };

  // User turns loop
  while (print_map == 1) {
    // Print coordinates input menu
    system("clear");
    printf("\n\033[34mTERMINAL MINESWEEPER by esantix\n\033[0m");

    printf("Mines: %d\nCells to free: %d/%d \n\n", num_mines,
           num_free - num_visibles, num_free);
    k = (dimension - (dimension % 10)) / 10;

    printf("    ");
    for (i = 1; i <= dimension; i++) {
      if (i % 10 == 0) {
        printf("  ");
      } else {
        printf(" %d", i % 10);
      };
    };
    printf("\n");

    for (i = 1; i <= dimension; i++) {
      if (i < 10) {
        printf(" ");
      };
      printf("%d> ", i);

      // Imprimir valores de fila
      for (j = 1; j <= dimension; j++) {
        if (VISIBLE[i][j] == 1) {
          if (MAP[i][j] == MINEVAL) {
            printf(" %c", MINESYMBOL);
          } else if (MAP[i][j] == 0) {
            printf("  ");
          } else {
            printf(

                "|\033[%dm%d"
                "\033[0m",
                30 + MAP[i][j], MAP[i][j]);
          };
        } else {
          // Not pressed
          printf("|_");
        };
      };
      printf("|\n");
    };

    // printf("   ");
    // for (i = 1; i <= dimension; i++) {
    //   if (i % 10 == 0) {
    //     printf("  ");
    //   } else {

    //     printf(" %d", i % 10);
    //   };
    // };

    if (perdiste == 1) {
      printf("\033[31m\n\n  YOU LOOSE :(\n\n\033[0m");
      exit(1);
    };

    if (ganaste == 1) {
      printf("\033[32m\n\n  YOU WIN  :) \n\n\033[0m");
      exit(0);
    };

    // Coordinates choosing menu
    printf("\n\nRow: ");
    scanf("%d", &row);

    while (row < 1 || row > dimension) {
      printf("Choose between [1-%d]: ", dimension);
      scanf("%d", &row);
    };

    printf("Column: ");
    scanf("%d", &col);

    while (col < 1 || col > dimension) {
      printf("Choose between [1-%d]: ", dimension);
      scanf("%d", &col);
    };

    // Hacer visible la elegida
    VISIBLE[row][col] = 1;

    // Si es bomba, perder
    if (MAP[row][col] == MINEVAL) {
      perdiste = 1;
      for (i = 0; i <= dimension; i++) {
        for (j = 0; j <= dimension; j++) {
          VISIBLE[i][j] = 1;
        };
      };
    };

    // Hacer visibles vecinas
    for (k = 0; k <= num_free; k++) {
      for (i = 1; i <= dimension; i++) {
        for (j = 1; j <= dimension; j++) {
          // Si celda vecina es vacia y visible, hacer visible
          if (((VISIBLE[i - 1][j - 1] == 1 && MAP[i - 1][j - 1] == 0) ||
               (VISIBLE[i - 1][j] == 1 && MAP[i - 1][j] == 0) ||
               (VISIBLE[i - 1][j + 1] == 1 && MAP[i - 1][j + 1] == 0) ||
               (VISIBLE[i][j - 1] == 1 && MAP[i][j - 1] == 0) ||
               (VISIBLE[i][j + 1] == 1 && MAP[i][j + 1] == 0) ||
               (VISIBLE[i + 1][j - 1] == 1 && MAP[i + 1][j - 1] == 0) ||
               (VISIBLE[i + 1][j] == 1 && MAP[i + 1][j] == 0) ||
               (VISIBLE[i + 1][j + 1] == 1 && MAP[i + 1][j + 1] == 0)) &&
              (MAP[i][j] != MINEVAL)) {
            VISIBLE[i][j] = 1;
          };
        };
      };
    };

    // CAlcular cantidad de visibles
    num_visibles = 0;

    for (i = 1; i <= dimension; i++) {
      for (j = 1; j <= dimension; j++) {
        if (VISIBLE[i][j] == 1) {
          num_visibles++;
        };
      };
    };
    if (num_visibles == num_free) {
      ganaste = 1;
    };
  };
}

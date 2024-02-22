/*Santiago Echevarria*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define BOMB 9

#define PUTSC(c, f) printf("\033[%dm" f "\033[0m", 30 + c)

#define C_RED 1
#define C_GREEN 2
#define C_YELLOW 3
#define C_BLUE 4
#define C_MAGENTA 5
#define C_CYAN 6

void main() {
  int i, j, k;
  int dimension, nbombas, num_visibles = 0, num_free;
  int print_map = 1, fi, co;
  int level;
  int cells;
  int perdiste = 0;

  printf("\n TERMINAL MINESWIPPER by esantix\n\n");
  printf("\n Size [5-40]: ");
  scanf("%d", &dimension);
  while (dimension < 5 || dimension > 40) {
    printf("Choose between [5-40]: ");
    scanf("%d", &dimension);
  };
  printf(" Level [1-5]: ");
  scanf("%d", &level);

  while (level < 0 || level > 5) {
    printf("Choose between [1-5]: ");
    scanf("%d", &level);
  };

  cells = dimension * dimension;
  nbombas = (int)(dimension * dimension * level * 0.1);

  int MAP[dimension + 1][dimension + 1];
  int VISIBLE[dimension + 1][dimension + 1];
  int a = 0;

  num_free =
      dimension * dimension - nbombas;  // Cantidad de cells que no son bombas

  for (i = 0; i <= dimension; i++) {
    for (j = 0; j <= dimension; j++) {
      VISIBLE[i][j] = 0;
      MAP[i][j] = 0;
    };
  };

  // Ubicar las bombas en posiciones aleatorias
  for (i = 1; i <= nbombas; i++) {
    j = 1 + rand() % dimension;
    k = 1 + rand() % dimension;
    if (MAP[j][k] ==
        MINE_VAL)  // If there already is a bomb there, decrease count
    {
      i--;
    };
    MAP[j][k] = BOMB;  // Bombs are "9"
  };

  // The cell value is the amount of bombs around it
  // Set non-bomb cell values
  a = 0;
  for (i = 1; i <= dimension; i++) {
    for (j = 1; j <= dimension; j++) {
      VISIBLE[i][j] = 0;
      if (MAP[i][j] != BOMB) {
        a = 0;
        a = a + (int)(MAP[i - 1][j - 1] == BOMB);  // up-left
        a = a + (int)(MAP[i - 1][j] == BOMB);      // up
        a = a + (int)(MAP[i - 1][j + 1] == BOMB);  // up-right
        a = a + (int)(MAP[i][j - 1] == BOMB);      // left
        a = a + (int)(MAP[i][j + 1] == BOMB);      // right
        a = a + (int)(MAP[i + 1][j - 1] == BOMB);  // down-left
        a = a + (int)(MAP[i + 1][j] == BOMB);      // down
        a = a + (int)(MAP[i + 1][j + 1] == BOMB);  // down-right

        MAP[i][j] = (int)a;
      };
    };
  };
  // Empieza interaccion jugador
  while (print_map == 1) {
    // Actualizar pantalla
    system("clear");
    printf("Mines: %d\nCells to free %d/%d \n\n", nbombas,
           num_free - num_visibles, num_free);
    k = (dimension - (dimension % 10)) / 10;

    // Imprimir indicador decenas
    printf("   ");
    for (i = 1; i <= k; i++) {
      printf("                   %d", i);
    };
    printf("\n   ");

    // Imprimir unidades (10 --> 1)
    for (i = 1; i <= dimension; i++) {
      printf(

          " %d", i % 10);
    };
    printf("\n");

    // Ppor cada linea
    for (i = 1; i <= dimension; i++) {
      // Imprimir indice fila
      if (i < 10) {
        printf(" ");
      };
      printf(

          "%d ", i);

      // Imprimir valores de fila
      for (j = 1; j <= dimension; j++) {
        // Todas las cells estan separadas
        // printf(" ");

        if (VISIBLE[i][j] == 1) {
          // Si es bombba
          if (MAP[i][j] == 9) {
            PUTSC(C_RED, " *");
          }
          // Si es vacio
          else if (MAP[i][j] == 0) {
            printf("  ");
          }
          // Si es numero
          else {
            printf(
                "\033[%dm"
                " %d"
                "\033[0m",
                30 + MAP[i][j], MAP[i][j]);
          };
        }

        else {
          // Celda desconocida (No visible)

          printf(
              "\033[1;1;%dm"
              "  "
              "\033[0m",
              45 + j % 2);
        };
      };
      printf(" %d", i);
      printf("\n");
    };

    if (perdiste == 1) {
      printf("\n\t\tYOU LOOSE\n\n");
      exit(1);
    };

    // Menu de elegir coordenadas
    printf("\n\nRow ");
    scanf("%d", &fi);
    printf("Column ");
    scanf("%d", &co);

    // Hacer visible la elegida
    VISIBLE[fi][co] = 1;

    // Si es bomba, perder
    if (MAP[fi][co] == BOMB) {
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
          if ((VISIBLE[i - 1][j - 1] == 1 && MAP[i - 1][j - 1] == 0) ||
              (VISIBLE[i - 1][j] == 1 && MAP[i - 1][j] == 0) ||
              (VISIBLE[i - 1][j + 1] == 1 && MAP[i - 1][j + 1] == 0) ||
              (VISIBLE[i][j - 1] == 1 && MAP[i][j - 1] == 0) ||
              (VISIBLE[i][j + 1] == 1 && MAP[i][j + 1] == 0) ||
              (VISIBLE[i + 1][j - 1] == 1 && MAP[i + 1][j - 1] == 0) ||
              (VISIBLE[i + 1][j] == 1 && MAP[i + 1][j] == 0) ||
              (VISIBLE[i + 1][j + 1] == 1 && MAP[i + 1][j + 1] == 0)) {
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
      system("clear");
      printf("\n\n\n\t\tYOU WIN\n\n\n");
      print_map = 0;
    };
  };
}

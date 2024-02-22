/*Santiago Echevarria*/
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MINEVAL 9
#define PUTSC(c, f) printf("\033[%dm" f "\033[0m", 30 + c)

void main()
{

  // Declare variable
  int i, j, k;
  int dimension, num_mines, num_visibles = 0, num_free=0;
  int print_map = 1, fi, co;
  int level;
  int cells;
  int perdiste = 0;

  // Print initial menu
  printf("\n TERMINAL MINESWIPPER by esantix\n\n");

  printf("\n Size [5-40]: ");
  scanf("%d", &dimension);
  while (dimension < 5 || dimension > 40)
  {
    printf("Choose between [5-40]: ");
    scanf("%d", &dimension);
  };

  printf(" Level [1-5]: ");
  scanf("%d", &level);
  while (level < 0 || level > 5)
  {
    printf("Choose between [1-5]: ");
    scanf("%d", &level);
  };

  // Level to number of mines calculation
  cells = dimension * dimension;
  num_mines = (int)(dimension * dimension * level * 0.1);
  num_free = cells - num_mines;

  // Map values
  int MAP[dimension + 1][dimension + 1];
  int VISIBLE[dimension + 1][dimension + 1];
  int a = 0;

  // Start zeros
  num_free = dimension * dimension - num_mines;
  for (i = 0; i <= dimension; i++)
  {
    for (j = 0; j <= dimension; j++)
    {
      VISIBLE[i][j] = 0;
      MAP[i][j] = 0;
    };
  };

  // Place mines randomly
  for (i = 1; i <= num_mines; i++)
  {
    j = 1 + rand() % dimension;
    k = 1 + rand() % dimension;
    if (MAP[j][k] == MINEVAL)
    {
      i--;
    };
    MAP[j][k] = MINEVAL;
  };

  // Set non-bomb cell values
  for (i = 1; i <= dimension; i++)
  {
    for (j = 1; j <= dimension; j++)
    {
      VISIBLE[i][j] = 0;
      if (MAP[i][j] != MINEVAL)
      {
        a = 0;
        a = a + (int)(MAP[i - 1][j - 1] == MINEVAL); // up-left
        a = a + (int)(MAP[i - 1][j] == MINEVAL);     // up
        a = a + (int)(MAP[i - 1][j + 1] == MINEVAL); // up-right
        a = a + (int)(MAP[i][j - 1] == MINEVAL);     // left
        a = a + (int)(MAP[i][j + 1] == MINEVAL);     // right
        a = a + (int)(MAP[i + 1][j - 1] == MINEVAL); // down-left
        a = a + (int)(MAP[i + 1][j] == MINEVAL);     // down
        a = a + (int)(MAP[i + 1][j + 1] == MINEVAL); // down-right
        MAP[i][j] = (int)a;
      };
    };
  };

  // User turns loop
  while (print_map == 1)
  {

    // Print coordinates input menu
    system("clear");
    printf("Mines: %d\nCells to free %d/%d \n\n", num_mines, num_free - num_visibles, num_free);
    k = (dimension - (dimension % 10)) / 10;

    printf("   ");
    for (i = 1; i <= dimension; i++)
    { 
      if (i%10 == 0)
      {
        printf("  ");
      }
      else
      {
        printf(" %d", i % 10);
      };
    };
    printf("\n");

    // Ppor cada linea
    for (i = 1; i <= dimension; i++)
    {
      // Imprimir indice fila
      if (i < 10)
      {
        printf(" ");
      };
      printf(

          "%d ", i);

      // Imprimir valores de fila
      for (j = 1; j <= dimension; j++)
      {
        // Todas las cells estan separadas
        // printf(" ");

        if (VISIBLE[i][j] == 1)
        {
          // Si es bombba
          if (MAP[i][j] == 9){printf(" *");}
          // Si es vacio
          
          else if (MAP[i][j] == 0)
          {
            printf("  ");
          }
          // Si es numero
          else
          {
            printf(
                "\033[%dm"
                " %d"
                "\033[0m",
                30 + MAP[i][j], MAP[i][j]);
          };
        }

        else
        {
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

    if (perdiste == 1)
    {
      printf("\n  YOU LOOSE :(\n\n");
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
    if (MAP[fi][co] == MINEVAL)
    {
      perdiste = 1;

      for (i = 0; i <= dimension; i++)
      {
        for (j = 0; j <= dimension; j++)
        {
          VISIBLE[i][j] = 1;
        };
      };
    };

    // Hacer visibles vecinas
    for (k = 0; k <= num_free; k++)
    {
      for (i = 1; i <= dimension; i++)
      {
        for (j = 1; j <= dimension; j++)
        {
          // Si celda vecina es vacia y visible, hacer visible
          if ((VISIBLE[i - 1][j - 1] == 1 && MAP[i - 1][j - 1] == 0) ||
              (VISIBLE[i - 1][j] == 1 && MAP[i - 1][j] == 0) ||
              (VISIBLE[i - 1][j + 1] == 1 && MAP[i - 1][j + 1] == 0) ||
              (VISIBLE[i][j - 1] == 1 && MAP[i][j - 1] == 0) ||
              (VISIBLE[i][j + 1] == 1 && MAP[i][j + 1] == 0) ||
              (VISIBLE[i + 1][j - 1] == 1 && MAP[i + 1][j - 1] == 0) ||
              (VISIBLE[i + 1][j] == 1 && MAP[i + 1][j] == 0) ||
              (VISIBLE[i + 1][j + 1] == 1 && MAP[i + 1][j + 1] == 0))
          {
            VISIBLE[i][j] = 1;
          };
        };
      };
    };

    // CAlcular cantidad de visibles
    num_visibles = 0;

    for (i = 1; i <= dimension; i++)
    {
      for (j = 1; j <= dimension; j++)
      {
        if (VISIBLE[i][j] == 1)
        {
          num_visibles++;
        };
      };
    };
    if (num_visibles == num_free)
    {
      system("clear");
      printf("\n\n\n\t\tYOU WIN\n\n\n");
      print_map = 0;
    };
  };
}

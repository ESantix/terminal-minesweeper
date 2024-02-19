/*Santiago Echevarria*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define BOMB 9


#define PRINTFC(c,t,f,s) printf("\033[%d;%dm" f "\033[0m",t ,28 + c, s)
#define PUTSC(c,f)     printf("\033[%dm" f  "\033[0m", 30 + c)

#define C_RED     1
#define C_GREEN   2
#define C_YELLOW  3
#define C_BLUE    4
#define C_MAGENTA 5
#define C_CYAN    6



void main()
{
    int i, j, k;
    int dim, nbombas, nvisibles, nlibres;
    int seguir = 1, fi, co;

    // printf("\n\n\tDimension: ");
    // scanf("%d", &dim);
    // printf("\n\tCantidad de bombas:");
    // scanf("%d", &nbombas);

    dim=20;
    nbombas=100;

    int A[dim+1][dim+1];
    int VISIBLE[dim+1][dim+1];
    int a=0;

    nlibres = dim * dim - nbombas; // Cantidad de celdas que no son bombas

      for (i = 0; i <= dim; i++)
    {
        for (j = 0; j <= dim; j++)
        {
            VISIBLE[i][j] = 0;
            A[i][j] = 0;
        };
    };


    // Ubicar las bombas en posiciones aleatorias
    for (i = 1; i <= nbombas; i++)
    {
        j = 1 + rand() % dim;
        k = 1 + rand() % dim;
        if (A[j][k] == 9) // If there already is a bomb there, decrease count
        {
            i--;
        };
        A[j][k] = 9; // Bombs are "9"
    };

    // The cell value is the amount of bombs around it
    // Set non-bomb cell values
    a=0;
    for (i = 1; i <= dim; i++)
    {
        for (j = 1; j <= dim; j++)
        {
            VISIBLE[i][j] = 0;
            if (A[i][j] != BOMB)
            {
                a=0;
                a = a + (int)( A[i - 1][j - 1] == BOMB ); // up-left
                a = a + (int)( A[i - 1][j] == BOMB );     // up
                a = a + (int)( A[i - 1][j + 1] == BOMB ); //up-right
                a = a + (int)( A[i][j - 1] == BOMB );     //left
                a = a + (int)( A[i][j + 1] == BOMB );     //right
                a = a + (int)( A[i + 1][j - 1] == BOMB ); // down-left
                a = a + (int)( A[i + 1][j] == BOMB );     //down
                a = a + (int)( A[i + 1][j + 1] == BOMB ); //down-right

                A[i][j] = (int)a;
            };
        };
    };
    // Empieza interaccion jugador
    while (seguir == 1)
    {

        // Actualizar pantalla
        system("clear");
        printf("%d x %d. \t\tFaltan %d / %d \n\n\n\n\n\t",dim,dim,nlibres-nvisibles,nlibres);
        k = (dim - (dim % 10)) / 10;
        for (i = 1; i <= k; i++)
        {
            printf("                   %d",i);
        };
        printf("\n\t");
        // Imprimir mapa
        for (i = 1; i <= dim; i++)
        {
            printf(" %d", i % 10);
        };
        printf("\n");

        // Imprimir mapa
        for (i = 1; i <= dim; i++)
         for (j = 1; j <= dim; j++){
        {
            printf("%d\t",i);
            for (j = 1; j <= dim; j++)
            {
                printf(" ");
                if (VISIBLE[i][j] == 1)
                {
                    if (A[i][j] == 9)
                    {

                        PUTSC(C_RED,"*");
                    }
                    else if (A[i][j] == 0)
                    {
                     
                     
                        printf(" ");
                    }
                    else
                    {
//                        printf("%d",A[i][j]);

                        printf("\033[%dm" "%d" "\033[0m",30 + A[i][j], A[i][j]);
                     
                    };
                }
                else
                {
                     printf("#");
                     //printf("%d",A[i][j]);
                    // PUTSC(C_BLUE,"#");
                };
            };
            printf("\n");
        };
         };
        
        
        //  elegir coordenadas
        printf("\n\nFila ");
        scanf("%d", &fi);
        printf("Columna ");
        scanf("%d", &co);

        // Hacer visible la elegida
        VISIBLE[fi][co] = 1;

        // Si es bomba, perder
        if (A[fi][co] == 9)
        {
            system("clear");
            printf("\n\t\tPERDISTE\n\n");
            seguir = 0;
        };


        // Hacer visibles vecinas
        for (k = 0; k <= nlibres; k++)
        {
            for (i = 1; i <= dim; i++){
                for (j = 1; j <= dim; j++)
                {

                    // top-left
                    // if (VISIBLE[i - 1][j - 1] == 1 && A[i - 1][j - 1] == 0)
                    // {
                    //     VISIBLE[i][j] = 1;
                    // };
                    // top-center
                    if (VISIBLE[i - 1][j] == 1 && A[i - 1][j] == 0)
                    {
                        VISIBLE[i][j] = 1;
                    };
                    //top-right
                    // if (VISIBLE[i - 1][j + 1] == 1 && A[i - 1][j + 1] == 0)
                    // {
                    //     VISIBLE[i][j] = 1;
                    // };
                    // center-left
                    if (VISIBLE[i][j - 1] == 1 && A[i][j - 1] == 0)
                    {
                        VISIBLE[i][j] = 1;
                    };
                    // center-right
                    if (VISIBLE[i][j + 1] == 1 && A[i][j + 1] == 0)
                    {
                        VISIBLE[i][j] = 1;
                    };
                    // bottom-left
                    if (VISIBLE[i + 1][j - 1] == 1 && A[i + 1][j - 1] == 0)
                    {
                        VISIBLE[i][j] = 1;
                    };
                    // bottom-center
                    if (VISIBLE[i + 1][j] == 1 && A[i + 1][j] == 0)
                    {
                        VISIBLE[i][j] = 1;
                    };
                    // bottom-right
                    if (VISIBLE[i + 1][j + 1] == 1 && A[i + 1][j + 1] == 0)
                    {
                        VISIBLE[i][j] = 1;
                        };
                    };
                };
            };
        nvisibles = 0;

        for (i = 1; i <= dim; i++)
        {
            for (j = 1; j <= dim; j++)
            {
                //
                if (VISIBLE[i][j] == 1)
                {
                    nvisibles++;
                };
            };
        };
        if (nvisibles == nlibres)
        {
            system("clear");
            printf("\n\n\n\t\tGANASTE\n\n\n");
            for (i = 1; i <= dim; i++)
            {
                printf("\t");
                for (j = 1; j <= dim; j++)
                {
                    if (A[i][j] == 9)
                    {
                        printf("*");
                    }
                    else if (A[i][j] == 0)
                    {
                        printf(" ");
                    }
                    else
                    {
                        printf("%d",A[i][j]);
                    };
                    printf(" ");
                };
                printf("\n");
            };

            seguir = 0;
        };
    };
}

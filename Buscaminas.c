/*Santiago Echevarria*/
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define BOMB 9

main()
{
    int i, j, k;
    int dim, nbombas, nvisibles, nlibres;
    int seguir = 1, fi, co;
    int A[100][100], VISIBLE[100][100];
    printf("\n\n\tDimension: ");
    dim = getchar();
    printf("\n\tCantidad de bombas:");
    nbombas = getchar();
    nlibres = dim * dim - nbombas; // Cantidad de celdas que no son bombas

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
    for (i = 1; i <= dim; i++)
    {
        for (j = 1; j <= dim; j++)
        {
            if (A[i][j] != 9)
            {
                int a;
                a = a + div(A[i - 1][j - 1], BOMB).quot; // up-left
                a = a + div(A[i - 1][j], BOMB).quot;     // up
                a = a + div(A[i - 1][j + 1], BOMB).quot; //up-right
                a = a + div(A[i][j - 1], BOMB).quot;     //left
                a = a + div(A[i][j + 1], BOMB).quot;     //right
                a = a + div(A[i + 1][j - 1], BOMB).quot; // down-left
                a = a + div(A[i + 1][j], BOMB).quot;     //down
                a = a + div(A[i + 1][j + 1], BOMB).quot; //down-right
            };
        };
    };
    // Empieza interaccion jugador
    while (seguir == 1)
    {

        // Actualizar pantalla
        system("clear");
        printf(dim "x" << dim << " con " << nbombas << " bombas\t\tFaltan " << nlibres - nvisibles << " / " << nlibres << "\n\n\n\n\n\t";
        k = (dim - (dim % 10)) / 10;
        for (i = 1; i <= k; i++)
        {
            cout << "                   " << i;
        };
        cout << "\n\t";
        // Imprimir mapa
        for (i = 1; i <= dim; i++)
        {
            cout << " " << i % 10;
        };
        cout << endl
             << endl;
        for (i = 1; i <= dim; i++)
        {
            cout << i << "\t";
            for (j = 1; j <= dim; j++)
            {
                cout << " ";
                if (VISIBLE[i][j] == 1)
                {
                    if (A[i][j] == 9)
                    {
                        cout << "*";
                    }
                    else if (A[i][j] == 0)
                    {
                        cout << " ";
                    }
                    else
                    {
                        cout << A[i][j];
                    };
                }
                else
                {
                    cout << "#";
                };
            };
            cout << endl;
        };
        cout << "\n\nFila ";
        cin >> fi;
        cout << "Columna ";
        cin >> co;
        VISIBLE[fi][co] = 1;
        if (A[fi][co] == 9)
        {
            system("clear");
            cout << "\n\t\tPERDISTE\n\n";
            seguir = 0;
        };
        for (k = 0; k <= nlibres; k++)
        {
            for (i = 1; i <= dim; i++)
            {
                for (j = 1; j <= dim; j++)
                {
                    if (VISIBLE[i - 1][j - 1] == 1 && A[i - 1][j - 1] == 0)
                    {
                        VISIBLE[i][j] = 1;
                    };
                    if (VISIBLE[i - 1][j] == 1 && A[i - 1][j] == 0)
                    {
                        VISIBLE[i][j] = 1;
                    };
                    if (VISIBLE[i - 1][j + 1] == 1 && A[i - 1][j + 1] == 0)
                    {
                        VISIBLE[i][j] = 1;
                    };
                    if (VISIBLE[i][j - 1] == 1 && A[i][j - 1] == 0)
                    {
                        VISIBLE[i][j] = 1;
                    };
                    if (VISIBLE[i][j + 1] == 1 && A[i][j + 1] == 0)
                    {
                        VISIBLE[i][j] = 1;
                    };
                    if (VISIBLE[i + 1][j - 1] == 1 && A[i + 1][j - 1] == 0)
                    {
                        VISIBLE[i][j] = 1;
                    };
                    if (VISIBLE[i + 1][j] == 1 && A[i + 1][j] == 0)
                    {
                        VISIBLE[i][j] = 1;
                    };
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
                if (VISIBLE[i][j] == 1)
                {
                    nvisibles++;
                };
            };
        };
        if (nvisibles == nlibres)
        {
            system("clear");
            cout << "\n\n\n\t\tGANASTE\n\n\n";
            for (i = 1; i <= dim; i++)
            {
                cout << "\t";
                for (j = 1; j <= dim; j++)
                {
                    if (A[i][j] == 9)
                    {
                        cout << "*";
                    }
                    else if (A[i][j] == 0)
                    {
                        cout << " ";
                    }
                    else
                    {
                        cout << A[i][j];
                    };
                    cout << " ";
                };
                cout << endl;
            };

            seguir = 0;
        };
    };
}

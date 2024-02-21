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
    int dim, nbombas, nvisibles=0, nlibres;
    int seguir = 1, fi, co;
    int dificultad;
    int celdas;
    int perdiste = 0;

    printf("\n Tamaño: ");
    scanf("%d", &dim);
    printf(" Dificultad [1-5]: ");
    scanf("%d", &dificultad);

    while( dificultad < 0 || dificultad > 5){
        printf("Elija valor entre [1-5]: ");
        scanf("%d", &dificultad);
    };
    // dim=20;
    // nbombas=100;
    celdas = dim*dim;
    nbombas = (int)(dim*dim*dificultad*0.1);

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
        if (A[j][k] == BOMB) // If there already is a bomb there, decrease count
        {
            i--;
        };
        A[j][k] = BOMB; // Bombs are "9"
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
        printf("Minas: %d.  Celdas por liberar %d / %d \n\n\n\t",nbombas,nlibres-nvisibles,nlibres);
        k = (dim - (dim % 10)) / 10;

        // Imprimir indicador decenas
        for (i = 1; i <= k; i++){printf("\033[33m" "                   %d""\033[0m",i);};
        printf("\n\t");

        // Imprimir unidades (10 --> 1)
        for (i = 1; i <= dim; i++){printf("\033[33m"" %d""\033[0m", i % 10); };printf("\n");

        // Ppor cada linea
        for (i = 1; i <= dim; i++){
        
            // Imprimir indice fila
            printf("\033[33m""%d\t""\033[0m",i);

            // Imprimir valores de fila
            for (j = 1; j <= dim; j++){
                // Todas las celdas estan separadas
                //printf(" ");

                if (VISIBLE[i][j] == 1){
                    // Si es bombba
                    if (A[i][j] == 9){PUTSC(C_RED," *");}
                    // Si es vacio
                    else if (A[i][j] == 0){printf("\033[1;0;100m" "  " "\033[0m");}
                    // Si es numero
                    else {printf("\033[1;%d;47m" " %d" "\033[0m", 30 + A[i][j],A[i][j]);};
                    }

                else{
                    // Celda desconocida (No visible)
               
               printf("\033[1;1;%dm" "  " "\033[0m", 45+j%2);
                };
            };
            printf("\n");
         };
        
        if( perdiste == 1){
            printf("\n\t\tPERDISTE\n\n");
            exit(1);
        };
        
        // Menu de elegir coordenadas
        printf("\n\nFila ");
        scanf("%d", &fi);
        printf("Columna ");
        scanf("%d", &co);

        // Hacer visible la elegida
        VISIBLE[fi][co] = 1;

        // Si es bomba, perder
        if (A[fi][co] == BOMB)
        {
            perdiste = 1;
            
            for (i = 0; i <= dim; i++){
                for (j = 0; j <= dim; j++){
                    VISIBLE[i][j] = 1;
                   };
                };

        };

        // Hacer visibles vecinas
        for (k = 0; k <= nlibres; k++){
            for (i = 1; i <= dim; i++){
                for (j = 1; j <= dim; j++){
                    // Si celda vecina es vacia y visible, hacer visible
                    if (
                        (VISIBLE[i - 1][j] == 1 && A[i - 1][j] == 0) || 
                        (VISIBLE[i][j - 1] == 1 && A[i][j - 1] == 0) || 
                        (VISIBLE[i][j + 1] == 1 && A[i][j + 1] == 0) ||  
                        (VISIBLE[i + 1][j] == 1 && A[i + 1][j] == 0)){
                            VISIBLE[i][j] = 1;
                        };
                    };
                };
            };


        // CAlcular cantidad de visibles
        nvisibles = 0;

        for (i = 1; i <= dim; i++){
            for (j = 1; j <= dim; j++){
                if (VISIBLE[i][j] == 1){ nvisibles++;};
                };
            };
        if (nvisibles == nlibres)
        {
            system("clear");
            printf("\n\n\n\t\tGANASTE\n\n\n");
            seguir = 0;
        };
    };
}

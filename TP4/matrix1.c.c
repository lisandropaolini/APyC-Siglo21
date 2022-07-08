/* Programa de multiplicación de matrices paralelizado,
   utilizando MPI.  2001, Daniel Manrique. */

#include "mpi.h"
#include "matrix.c"
#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv)
{
    int localid, numprocs, namelen, rv, row, col;
    int *matrix1=NULL;
    int *matrix2=NULL;
    int *matrix3=NULL;
    double startwtime, endwtime;
    char processor_name[MPI_MAX_PROCESSOR_NAME];
    int x, y, i, k;
    int partitions, firstrow, lastrow, rowstodo;
    int *resultrow;
    int elem1, elem2, suma;
    int completerows;
    int dimension;
    char optchar;
    int opt_print = 0;
    int seed = (unsigned int) (time(0) / 2);
    MPI_Status status;

    // Inicializar mpi
    MPI_Init(&argc, &argv);

    /* determinar numero total de procesos y cual
       somos, asi como en que procesador (nodo) estamos
       corriendo. */
    MPI_Comm_size(MPI_COMM_WORLD, &numprocs);
    MPI_Comm_rank(MPI_COMM_WORLD, &localid);
    MPI_Get_processor_name(processor_name, &namelen);

    printf("soy el proceso %d de %d en %s\n",
	   localid, numprocs, processor_name);
    // Este ciclo procesa las opciones de la línea de
    // comandos y fija las banderas necesarias del
    // programa
    do {
	optchar = getopt(argc, argv, "fpd:");
	switch (optchar) {
	case 'p':
	    printf("imprimiendo matrices\n");
	    opt_print = 1;
	    break;
	case 'd':
	    dimension = atoi(optarg);
	    printf("dimension %d\n", dimension);
	    break;
	case 'f':
	    printf("matriz fija\n");
	    seed = 1;
	    break;
	}
    } while (optchar != -1);

    if (dimension == 0) {
	printf("dimension 0, pos no funcionara\n");
	return 0;
    }
    row = dimension;
    col = dimension;


    /* En MPI el proceso inicial (padre) tiene rank
       de 0, esta es la sección donde el proceso padre
       realiza su trabajo */
    if (localid == 0) {
	srandom((unsigned int) (time(0) / 2));
	// Asignar memoria para tres matrices de de row
	// x col
	matrix1 = malloc(row * col * sizeof(int));
	matrix2 = malloc(row * col * sizeof(int));
	matrix3 = malloc(row * col * sizeof(int));
	if (matrix1 == NULL || matrix2 == NULL ||
	    matrix3 == NULL ){
	    MPI_Finalize();
	    if (matrix1!=NULL) free(matrix1);
	    if (matrix2!=NULL) free(matrix2);
	    if (matrix3!=NULL) free(matrix3);
	    exit(1);
	}

	/* llenamos las dos primeras matrices
	   aleatoriamente..  la definicion de la funcion
	   randomatrix esta en el archivo matrix.c */
	randomatrix(matrix1, row, col, 5);
	randomatrix(matrix2, row, col, 5);

	/*Determinar el momento de inicio de ejecución,
	   aquí medimos cuando comenzamos realmente a
	   hacer los cálculos */
	startwtime = MPI_Wtime();

	// mostrar matrices si el usuario lo
	// solicitó...
	if (opt_print) {
	    matrix_print(matrix1, row, col);
	    printf("\n");
	    matrix_print(matrix2, row, col);
	}
	// mi registro de cuales rows ya estan
	// completos
	completerows = 0;

	/* el proceso con rank 0 transmite las dos
	   matrices a los demás, esto se hace por medio
	   de un broadcast de MPI a todos los miembros de
	   mi comunicador (MPI_COMM_WORLD) */
	rv = MPI_Bcast(matrix1,
		       row * col,
		       MPI_INT, 0, MPI_COMM_WORLD);
	printf("Root, Broadcast said %d\n", rv);
	rv = MPI_Bcast(matrix2,
		       row * col,
		       MPI_INT, 0, MPI_COMM_WORLD);
	printf("Root, Broadcast said %d\n", rv);

	// asignar un row temporal para resultados
	resultrow = malloc((col + 1) * sizeof(int));
	// esperar a tener todos los resultados
	// completos
	while (completerows < row) {
	    /* Esta llamada espera a recibir un renglón
	       ya resuelto, de cualquier proceso
	       hijo. Nótese el parametro MPI_ANY_SOURCE
	       que indica que se admiten valores de
	       cualquier proceso. */
	    MPI_Recv(resultrow,
		     col + 1,
		     MPI_INT,
		     MPI_ANY_SOURCE,
		     1, MPI_COMM_WORLD, &status);
	    printf("recibido renglon %d de %d\n",
		   resultrow[0], status.MPI_SOURCE);
	    completerows++;
	    // Este ciclo "pone" el renglon recibido en
	    // mi matriz de resultado
	    for (i = 0; i < col; i++) {
		matrix_set_cell(matrix3,
				row,
				col,
				i,
				resultrow[0],
				resultrow[i + 1]);
	    }
	}
	// terminamos el cálculo! anotar tiempo al
	// terminar..
	endwtime = MPI_Wtime();
	// mostrar la matriz de resultados si se
	// solicitó
	if (opt_print) {
	    matrix_print(matrix3, row, col);
	}
	// Y mostrar el tiempo total de cálculo
	printf("wall clock time = %f\n",
	       endwtime - startwtime);
	if (matrix1!=NULL) free(matrix1);
	if (matrix2!=NULL) free(matrix2);
	if (matrix3!=NULL) free(matrix3);

    } // AQUI termina la ejecucion del proceso padre
    else {
	/* Aqui comienza lo que ejecuten procesos con
	   rank distinto de cero, es decir los procesos
	   hijo.  Asigno espacio para dos matrices.. */
	matrix1 = malloc(row * col * sizeof(int));
	matrix2 = malloc(row * col * sizeof(int));
	if (matrix1 == NULL || matrix2 == NULL){
	    MPI_Finalize();
	    if (matrix1!=NULL) free(matrix1);
	    if (matrix2!=NULL) free(matrix2);
	    if (matrix3!=NULL) free(matrix3);
	    exit(1);
	}

	/* En MPI, si mi rank no es 0, una llamada al
	   broadcast (notar el parametro 4 que es de 0)
	   indica recibir el broadcast del proceso con ese
	   rank. */
	rv = MPI_Bcast(matrix1,
		       row * col,
		       MPI_INT, 0, MPI_COMM_WORLD);
	rv = MPI_Bcast(matrix2,
		       row * col,
		       MPI_INT, 0, MPI_COMM_WORLD);

	/*de acuerdo a las dimensiones de las matrices
	   y al numero de procesos, calcular numero de
	   particiones, renglones por particion, el
	   primer renglon que tiene que resolver este
	   proceso, y el ultimo renglon.  */
	partitions = numprocs - 1;
	rowstodo = (int) (row / partitions);
	firstrow = rowstodo * (localid - 1);
	lastrow = firstrow + rowstodo - 1;

	// el ultimo proceso amplia su limite para
	// tomar los huerfanitos
	if (localid == numprocs - 1) {
	    lastrow = lastrow + (row % partitions);
	}

/*   printf ("me toca la particion %d\n", */
/*     localid);  */
/*   printf ("en total hay %d particiones\n", */
/*     partitions);  */
/*   printf ("cada particion tiene %d renglones, */
/*     ",rowstodo);  */
/*   printf ("renglon inicial %d, ", */
/*     firstrow );  */
/*   printf ("renglon final %d\n", */
/*     lastrow);  */

	// asignar un row temporal
	resultrow = malloc((col + 1) * sizeof(int));

	// calcular cada row del grupo que me toca.
	for (i = firstrow; i <= lastrow; i++) {
	    /* printf ("proceso %d[%s] haciendo row
	       %d\n",localid,processor_name,i); */
	    /* el elemento que estoy calculando esta en
	       y,x entonces lo que va a variar va a ser
	       la x porque la y es fija por renglon */
	    y = i;
	    for (x = 0; x < col; x++) {
		//              printf ("calculando
		//              elemento
		//              (%d,%d)\n",x,y);
		suma = 0;
		for (k = 0; k < col; k++) {
		    elem1 = matrix_get_cell(matrix1,
					    row,
					    col, k, y);
		    elem2 = matrix_get_cell(matrix2,
					    row,
					    col, x, k);
		    suma += elem1 * elem2;
		    //      printf ("%d*%d +
		    //      ",elem1,elem2);
		}
		resultrow[x + 1] = suma;
	    }
	    // ya tengo calculado el renglon ahora se
	    // lo tengo que mandar al proceso padre
	    resultrow[0] = i;
	    MPI_Send(resultrow,
		     col + 1,
		     MPI_INT, 0, 1, MPI_COMM_WORLD);
	    //      printf ("enviado row %d\n",i);
	}
    if (matrix1!=NULL) free(matrix1);
    if (matrix2!=NULL) free(matrix2);
    if (matrix3!=NULL) free(matrix3);	
    } // termina seccion de calculo proceso hijo

    // Terminamos la sesión de MPI
    MPI_Finalize();

    // y listo.
    return 0;
}
#include "mpi.h"
#include <stdio.h>
#include <stdlib.h>
#include<time.h>

// entrada, para definir orden de matriz cuadradas
#define MATSIZE 5

// numero de filas matriz A
#define NRA MATSIZE
// numero de columnas matriz A
#define NCA MATSIZE
// numero de columnas matriz B
#define NCB MATSIZE
// id master
#define MASTER 0

// tipos de mensaje
#define FROM_MASTER 1
#define FROM_WORKER 2

int main (int argc, char *argv[])
{
int	numtasks,           /* numero de particiones */
	taskid,                /* id de tarea */
	numworkers,            /* nro de workers */
	source,                /* task id origen */
	dest,                  /* task id destino */
	mtype,                 /* tipo de mensaje */
	rows,                  /* fila de la matriz A enviada al worker */
	averow, extra, offset, /* para determinar la fila a enviar al worker */
	i, j, k, rc;           /* de apoyo */
double	a[NRA][NCA],     /* matriz A */
	b[NCA][NCB],           /* matriz B  */
	c[NRA][NCB];           /* matriz C para los resutltados */
MPI_Status status;
srand(time(0));
MPI_Init(&argc,&argv);
MPI_Comm_rank(MPI_COMM_WORLD,&taskid);
MPI_Comm_size(MPI_COMM_WORLD,&numtasks);
if (numtasks < 2 ) {
  printf("Se necesita como minimo 2 para MPI. FIN...\n");
  MPI_Abort(MPI_COMM_WORLD, rc);
  exit(1);
  }
numworkers = numtasks-1;


/**************************** master task ************************************/
   if (taskid == MASTER)
   {
      printf("mpi_mm comienza con %d tareas.\n",numtasks);

      /* se comienza cargando las 2 matrices */
      for (i=0; i<NRA; i++)
         for (j=0; j<NCA; j++){
            int random = rand() % (10); // obtengo random del 0 al 9
            a[i][j]= (double) random;
         }
      for (i=0; i<NCA; i++)
         for (j=0; j<NCB; j++){
            int random = rand() % (10); // obtengo random del 0 al 9
            b[i][j]= (double) random;
         }

      /* INICIO, SE TOMARA COMO MOMENTO 0 */
      double start = MPI_Wtime();

      /* comienzo enviando matriz de datos a los workers */
      averow = NRA/numworkers;
      extra = NRA%numworkers;
      offset = 0;
      mtype = FROM_MASTER;
      for (dest=1; dest<=numworkers; dest++)
      {
         rows = (dest <= extra) ? averow+1 : averow;
         MPI_Send(&offset, 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);
         MPI_Send(&rows, 1, MPI_INT, dest, mtype, MPI_COMM_WORLD);
         MPI_Send(&a[offset][0], rows*NCA, MPI_DOUBLE, dest, mtype,
                   MPI_COMM_WORLD);
         MPI_Send(&b, NCA*NCB, MPI_DOUBLE, dest, mtype, MPI_COMM_WORLD);
         offset = offset + rows;
      }

      /* Se recibe resultado de los workers */
      mtype = FROM_WORKER;
      for (i=1; i<=numworkers; i++)
      {
         source = i;
         MPI_Recv(&offset, 1, MPI_INT, source, mtype, MPI_COMM_WORLD, &status);
         MPI_Recv(&rows, 1, MPI_INT, source, mtype, MPI_COMM_WORLD, &status);
         MPI_Recv(&c[offset][0], rows*NCB, MPI_DOUBLE, source, mtype, 
                  MPI_COMM_WORLD, &status);
      }

      /* Imprimimos los resultados en archivo */

      int random = rand() % (100000); // obtengo random del 0 al 99999
      char text[20];
      sprintf(text, "%d", random);

      /* Formato nombre de archivo */
      /* "salida" + random + .txt */
      sprintf(text, "Salida%d.txt", random);

      FILE *out_file = fopen(text, "w"); // solo escritura 

      if (out_file == NULL) 
            {   
              printf("Error! al abrir el archivo\n"); 
              exit(-1);
            } 
            
      fputs("******************************************************\n", out_file);
      fputs("Matriz A:\n", out_file);
      for (i=0; i<NRA; i++)
      {
         fputs("\n ", out_file);
         for (j=0; j<NCB; j++){
            fprintf(out_file, "%6.2f   ", a[i][j]); 
         } 
      }
      fputs("\n******************************************************\n", out_file);

      fputs("******************************************************\n", out_file);
      fputs("Matriz B:\n", out_file);
      for (i=0; i<NRA; i++)
      {
         fputs("\n", out_file);
         for (j=0; j<NCB; j++) 
            fprintf(out_file, "%6.2f   ", b[i][j]);
      }
      fputs("\n******************************************************\n", out_file);

      fputs("******************************************************\n", out_file);
      fputs("Matriz AB, resultante:\n", out_file);
      for (i=0; i<NRA; i++)
      {
         fputs("\n", out_file);
         for (j=0; j<NCB; j++) 
            fprintf(out_file, "%6.2f   ", c[i][j]);
      }
      fputs("\n******************************************************\n", out_file);
      

      /* medicion de tiempo final */
      double finish = MPI_Wtime();
      printf("Finalizo en %f segundos.\n", finish - start);
   }


/**************************** worker ************************************/
   if (taskid > MASTER)
   {
      mtype = FROM_MASTER;
      MPI_Recv(&offset, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD, &status);
      MPI_Recv(&rows, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD, &status);
      MPI_Recv(&a, rows*NCA, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD, &status);
      MPI_Recv(&b, NCA*NCB, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD, &status);

      for (k=0; k<NCB; k++)
         for (i=0; i<rows; i++)
         {
            c[i][k] = 0.0;
            for (j=0; j<NCA; j++)
               c[i][k] = c[i][k] + a[i][j] * b[j][k];
         }
      mtype = FROM_WORKER;
      MPI_Send(&offset, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD);
      MPI_Send(&rows, 1, MPI_INT, MASTER, mtype, MPI_COMM_WORLD);
      MPI_Send(&c, rows*NCB, MPI_DOUBLE, MASTER, mtype, MPI_COMM_WORLD);
   }
   MPI_Finalize();
}
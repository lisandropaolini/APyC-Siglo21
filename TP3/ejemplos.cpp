#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cerrno>
#include <cstdio>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;
int
main (int argc, char **argv)
{
  static const int PROC = 8;	// PROC fija cantidad de procesos a crear
  int status, procNum;		// procNum almacena el nC:mero del proceso
  pid_t pid;			// pid almacena el id del proceso
  for (procNum = 0; procNum < PROC; procNum++)
    {
      pid = fork ();		// llamada al sistema fork()
      if (pid == 0)
	{			// si el proceso se crea bien, termina el for
	  break;
	}
      else if (pid == -1)
	{			// si hay error termina la operaciC3n
	  perror ("ERROR al hacer llamada fork()");
	  exit (1);
	  break;
	}
    }
  if (pid == 0)
    {				// LC3gica del proceso Hijo
      cout << "Soy el proceso " << procNum << " mi id es " << getpid () <<
	" mi padre es " << getppid () << endl;

      exit (0);
    }
  else
    {				// LC3gica del proceso Padre
      for (int i = 0; i < PROC; i++)
	{			// esperar a que todos los hijos terminen

	  if ((pid = wait (NULL)) >= 0)
	    {
	      cout << "Proceso " << pid << " terminado" << endl;
	    }
	}

      cout << "Soy el padre " << getpid () << endl;
    }
  return 0;			// Fin
}

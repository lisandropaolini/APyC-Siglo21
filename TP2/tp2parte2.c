#include <unistd.h>
#include <stdio.h>>

int var = 22;


int main(void)
{
    pid_t pidC;
    printf("Proceso PID = %d  comienza  \n", getpid);
    pidC = fork();

    printf("proceso PID = %d , pidC = %d  ejecutandose \n", getpid(), pidC);

    if(pidC > 0) /*proceso padre valor mayor que 0*/
    {
        var = 44;
    }
    else if(pidC == 0) /*proceso hijo valor igual a 0*/
    {
        var = 33;
    }
    else /*error cuando el proceso no pude ser creado*/
    {

    }

    while(1)
    {
        sleep(2);
        printf("proceso PID = %d , var = %d  ejecutandose \n", getpid(), var);
    }

    return 0;
}

# APyC-Siglo21


## TP2

### Consigna 1

Implementar un algoritmo en C que reciba como argumento dos números enteros, N y M. Tales números serán utilizados para crear N hilos (threads) de tipo 1 y M hilos (threads) de tipo 2. A continuación se describe la funcionalidad que deberán implementar cada uno de los hilos:

Hilo de tipo 1: Deberán mostrar por pantalla el mensaje: “Instancia x del hilo 1”, siendo x el número de hilo creado (entre 0 y N-1). Posteriormente se suspenderá por un tiempo aleatorio entre 0 y 2 segundos (para ello utilizaremos la llamada usleep o sleep), finalmente incrementará la variable global “Compartida”.

Hilo de tipo 2: Deberán mostrar por pantalla el siguiente mensaje: “Instancia y del hilo 2”, siendo “y” el número de hilo creado (entre 0 y M-1). Posteriormente se suspenderá por un tiempo aleatorio entre 0 y 2 segundos. Para finalizar leerán y mostrarán por pantalla el valor de la variable global “Compartida”.

Cuando los hilos finalicen su ejecución, el padre debe mostrar por pantalla “Se ha finalizado la ejecución”. Ver funcionamiento de pthread_create y pthread_join.


### Consigna 2

Continuando con lo realizado en la consigna 1, pero esta vez utilizando procesos en vez de hilos. Para ello deberán crear, por medio de la llamada fork, N procesos tipo 1 y M procesos de tipo 2. 

Realicen un análisis del comportamiento de ambas implementaciones, y describan el comportamiento observado, diferencias, describir.


	g++ consigna1.cpp -o consigna1.out -pthread -std=c++11
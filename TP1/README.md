# APyC-Siglo21


## TP1

### Consigna 1
Basado en la situación problemática, se debe analizar el comportamiento de los algoritmos presentados, estudiando sus particularidades desde el punto de vista de la implementación. Para llevar a cabo esta tarea es necesario ejecutar los algoritmos y luego de realizar diversas ejecuciones, documentar y explicar el comportamiento de tales programas.

### Consigna 2
Con base en el enfoque presentado en el algoritmo 2, desarrollar una nueva versión del programa en el que se ejecuten 15 procesos, de manera que el proceso i-ésimo se pause un tiempo aleatorio (definir un rango en milisegundos que pueda ser perceptible), y que por pantalla se muestre el mensaje correspondiente (“Soy el proceso 1”, “Soy el proceso 2”, ... ,“Soy el proceso n”) un número aleatorio de veces. 

### Consigna 3
Tal como se puede observar, los algoritmos anteriores son claros cuando el comportamiento del proceso puede estar encapsulado en una única función. Pero termina siendo confuso cuando los procesos necesitan llevar a cabo tareas de mayor complejidad. Para ello, un enfoque más general consiste en encapsular (en una clase de objetos) el comportamiento de un proceso, creando las instancias necesarias, y de este modo lanzar la función deseada del objeto en un thread. Analice de qué manera podría implementar este enfoque, describa las características y esboce una implementación del algoritmo. 


#### Formato entregable

Se deberá entregar fichero .zip que contenga el código fuente desarrollado y un informe en formato PDF. 
Se valorará la claridad del código y debidamente comentado. 
Adicionalmente se considera mayor puntaje si se incluye tratamiento correcto de errores, es decir, en caso de producirse errores deberá informarse al usuario del tipo de error ocurrido.
Breve informe que incluye el trabajo teórico realizado y la resolución/análisis de los ejercicios planteados. 
En dicho informe se deberá destinar una sección a describir la modalidad de trabajo, y dificultades encontradas y cómo fueron solucionadas (en caso de haberlas).


	g++ algoritmo1.cpp -o algoritmo1.out -pthread -std=c++11
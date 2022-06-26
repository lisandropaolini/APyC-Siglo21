# APyC-Siglo21


## TP3



### Consigna 1

En grupos de no más de 4 integrantes, diseñar y desarrollar una aplicación que permita simular el juego de cartas del siete y medio. La aplicación deberá operar con varios procesos mediante un modelo cliente/servidor, clientes=jugadores, y servidor={distribuir las cartas, recoger las decisiones de los jugadores, hasta que se declare un ganador}.

La ejecución de la partida será mediante el comando: iniciar_juego N, N será el número de jugadores que participan en la primera partida. Como resultado de la ejecución se publica el ganador de la partida, así como una tabla describiendo la situación de cada jugador (cuántos puntos posee, se plantó o abandonó).

El proceso iniciar_juego será el encargado de gestionar la partida, será el que repartirá las cartas por turnos, mantendrá el estado de la partida a partir de las decisiones de los jugadores, y decidirá finalmente el ganador de la partida.

El proceso jugador será el que implementará la lógica del jugador en la partida, en base a las cartas que reciba del repartidor (iniciar_juego), y de su propio estado (puntos) decidirá si continúa en el juego pidiendo más cartas, se queda ahí, o abandona (porque se pasó). Esta lógica de juego se deja abierta, de forma que se implemente como cada grupo lo decida, pudiendo llegar a ser simplemente aleatoria: según un número aleatorio el jugador decide plantarse, pedir carta, o abandonar.

	a) Recordar que la generación de los N procesos jugadores deberá realizarse a través del uso de forks, y la comunicación repartidor/jugador se efectuará mediante pipes.
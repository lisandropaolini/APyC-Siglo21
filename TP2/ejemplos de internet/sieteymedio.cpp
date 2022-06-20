#include <iostream>

using namespace std;

#define SI 1
#define NO 0

int mazo[40];

void CargarMazo ();
int ExtraerCarta ();
float Jugar (int JuegaHumano, float ValorAVencer);

main ()
{
  int seguimos = SI;
  char jugamos;
  float puntosHumano, puntosComputadora;

  while (seguimos)
    {
      CargarMazo ();
      puntosComputadora = 0;
      puntosHumano = Jugar (SI, puntosComputadora);
      if (puntosHumano > 0)
	puntosComputadora = Jugar (NO, puntosHumano);
      if (puntosHumano > puntosComputadora)
	{
	  cout << endl << endl << "FELICIDADES!!!... Ganaste..." << endl;
	}
      else
	{
	  cout << endl << endl << "Lo siento... te gane..." << endl;
	}

      cout << endl << "Jugamos al siete y medio?... (S/N)";
      cin >> jugamos;
      seguimos = (jugamos == 's' || jugamos == 'S') ? SI : NO;
    }
}

void
CargarMazo ()
{
  for (int p = 0; p < 4; p++)
    for (int n = 0; n < 10; n++)
      mazo[p * 10 + n] = n + 1;
}

int
ExtraerCarta ()
{
  int x, d;
  x = rand () % 40;
  while (mazo[x] == NO)
    x = (rand () % 40);
  d = (mazo[x] > 7) ? mazo[x] + 2 : mazo[x];
  mazo[x] = NO;
  return d;
}

float
Jugar (int JuegaHumano, float PuntosAvencer)
{
  int seguimos = SI;
  char respuesta;
  float puntos = 0;
  int carta;
  if (JuegaHumano)		// Juega humano
    cout << endl << "Es tu turno de jugar al siete y medio..." << endl;
  else				// Juega computadora
    cout << endl << "Es mi turno de jugar..." << endl;

  while (seguimos)
    {
      carta = ExtraerCarta ();
      puntos += (carta > 7) ? 0.5 : carta;
      cout << "Salio un " << carta << " y la punturacion es " << puntos;

      if (puntos > 7.5)
	return -1;

      if (JuegaHumano)
	{			// Juega humano
	  cout << "... Seguimos?";
	  cin >> respuesta;
	  seguimos = (respuesta == 's' || respuesta == 'S') ? SI : NO;
	}
      else
	{			// Juega computadora
	  seguimos = (puntos < PuntosAvencer) ? SI : NO;
	  cout << endl;
	}
    }
  return puntos;
}

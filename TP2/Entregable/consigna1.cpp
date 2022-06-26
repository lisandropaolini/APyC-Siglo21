#include<iostream>
#include<string>
#include<stdexcept>
#include<cctype>
#include <stdio.h>
#include<stdlib.h>
#include<time.h>
#include<thread>
#include<chrono>
#include<vector>
using namespace std;

// Se utiliza para obtener el tiempo de espera en cada hilo
int getRandomEspera(){
    srand(time(0)); //semilla
    return rand() % (2000 + 1);
}

void hiloTipo1(int i){
  cout << "Instancia "+ to_string(i)+" del hilo 1" +"\n";
  this_thread::sleep_for(chrono::milliseconds(getRandomEspera()));
}

void hiloTipo2(int i){
  cout << "Instancia "+ to_string(i)+" del hilo 2" +"\n";
  this_thread::sleep_for(chrono::milliseconds(getRandomEspera()));
}

void validaEntrada(int argc, char *argv[]){

  if (argc < 2) {
    throw invalid_argument ("Valor de N y M no ingresado !");
  }
  if (argc < 3) {
    throw invalid_argument ("Valor de M no ingresado !");
  }
  try {
    string m = argv[1];
    int num = 0;
    num = std::stoi(m);
    cerr << "Valor de N " + m + "\n";

    string n = argv[2];
    num = std::stoi(n);
    cerr << "Valor de M " + n + "\n";
  } catch (exception& e) {
    throw invalid_argument("Parametros no valido");
  }
}

int main (int argc, char *argv[])
{

// try que se utiliza para validar los parametros de entrada
  try {
    // si falta un parametro o no es valido el numero, sale con mensaje de error
    validaEntrada(argc, argv);
  } catch (exception& e) {
    cerr << e.what () << endl;
    exit (EXIT_FAILURE);
  }

  int valorM = 0;
  int valorN = 0;

  try {
    string m = argv[1];
    valorM = std::stoi(m);
    string n = argv[2];
    valorN = std::stoi(n);

  } catch (exception& e) {
    cerr << e.what () << endl;
    exit (EXIT_FAILURE);
  }

      std::vector<thread> threadsM(valorM);
      std::vector<thread> threadsN(valorN);

    for (int i =0; i < valorM ; i ++) {
        threadsM[i] = thread(hiloTipo1, i); 
    }
    for (auto& th : threadsM) {
        th.join();
    }

    for (int i =0; i < valorN ; i ++) {
        threadsN[i] = thread(hiloTipo2, i); 
    }
    for (auto& th : threadsN) {
        th.join();
    }

}

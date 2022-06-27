#include<iostream>
#include<thread>
#include<vector>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<time.h>
using namespace std;

int variableGlobal;

// Se utiliza para obtener el tiempo de espera en cada hilo
int getRandomEspera(){
    int random = rand() % (2 + 1);
    // cout << "random "+ to_string(random)+ "\n";
    return random;
}

void hiloTipo1(int i){
  cout << "Instancia "+ to_string(i)+" del hilo 1" +"\n";
  sleep(getRandomEspera());
  ++variableGlobal;
}

void hiloTipo2(int i){
  cout << "Instancia "+ to_string(i)+" del hilo 2" +"\n";
  sleep(getRandomEspera());
  cout << "Variable Global Compartida "+ to_string(variableGlobal)+ "\n";
}

void validaEntrada(int argc, char *argv[]){

  if (argc < 2) {
    throw invalid_argument ("Valor de N y M no ingresado !");
  }
  if (argc < 3) {
    throw invalid_argument ("Valor de M no ingresado !");
  }
  try {
    string n = argv[1];
    string m = argv[2];
    int num = 0;
    num = std::stoi(n);
    num = std::stoi(m);

    cerr << "Valor de N " + n + "\n";
    cerr << "Valor de M " + m + "\n";
  } catch (exception& e) {
    throw invalid_argument("Parametros no valido");
  }
}

int main (int argc, char *argv[]){

// try que se utiliza para validar los parametros de entrada
  try {
    // si falta un parametro o no es valido el numero, sale con mensaje de error
    validaEntrada(argc, argv);
  } catch (exception& e) {
    cerr << e.what () << endl;
    exit (EXIT_FAILURE);
  }

  int valorN = 0;
  int valorM = 0;

  try {
    string n = argv[1];
    valorN = std::stoi(n);
    string m = argv[2];
    valorM = std::stoi(m);

  } catch (exception& e) {
    cerr << e.what () << endl;
    exit (EXIT_FAILURE);
  }

  variableGlobal=0; 
  int id = fork ();
  // pid_t pid = fork();
  
  if (id == 0) {       //proceso hijo

    for (int i =0; i < valorN ; i ++) {
      hiloTipo1(i);
    }
  } else {       //proceso padre

    for (int i =0; i < valorM ; i ++) {
      hiloTipo2(i);
    }
  }

  if (id != 0) {
    int child_status;
    waitpid(id, &child_status, 0);      //espera a que termine el proceso hijo
    cout << "Se ha finalizando la ejecución\n";
  }


    // cout << "Variable Global Compartida Valor Final "+ to_string(variableGlobal)+ "\n";
}

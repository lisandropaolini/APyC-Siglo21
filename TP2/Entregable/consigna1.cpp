#include<iostream>
#include<thread>
#include<vector>
#include<unistd.h>
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

int main (int argc, char *argv[])
{

  variableGlobal=0;

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
    string m = argv[2];
    valorN = std::stoi(n);
    valorM = std::stoi(m);
  } catch (exception& e) {
    cerr << e.what () << endl;
    exit (EXIT_FAILURE);
  }

  std::vector<thread> threadsN(valorN);
  std::vector<thread> threadsM(valorM);

  for (int i =0; i < valorN ; i ++) {
      threadsN[i] = thread(hiloTipo1, i); 
  }
  for (int i =0; i < valorM ; i ++) {
      threadsM[i] = thread(hiloTipo2, i); 
  }
  for (auto& th : threadsN) {
      th.join();
  }
  for (auto& th : threadsM) {
      th.join();
  }

  cout << "Se ha finalizando la ejecución\n";
    // cout << "Variable Global Compartida Valor Final "+ to_string(variableGlobal)+ "\n";
}

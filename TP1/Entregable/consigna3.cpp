#include<iostream>
#include<thread>
#include<string>
#include<chrono>
#include<vector>
#include<time.h>

using namespace std;

class Mensaje{
    public:
        string texto;
    Mensaje(){
    }
};

class SaludoConTiempoRandom{
public:
    Mensaje mensaje;
    int demora;
    SaludoConTiempoRandom(string m){
        mensaje.texto = m;

        // al crear el saludo, obtengo el random para la cantidad de demora
        demora = rand() % 500 + 200; 
    }
};

void miOtroSaludo(SaludoConTiempoRandom saludo){

    int veces = 1 + rand() % (10);

    // itero el mensaje una cantidad random
    for (int i =1; i <= veces ; i ++) {

        // mensaje de salida por pantalla
        cout << saludo.mensaje.texto +" - " +to_string(i)+ "/" + to_string(veces) +"\n"; 

        this_thread::sleep_for(chrono::milliseconds(saludo.demora));
    }
}

void generarThreads(int n){
    std::vector<thread> threads(n);
    
    //for para iterar la cantidad de hilos que se generaran
    for (int i = 0; i < n; i++) { 
        string tab = "";

        //for para generar el TAB para distinguir a simple vista el proceso
        for (int j = 0; j < i; j++) { 
            tab = tab + "\t";
        }

        // numero de hilo del saludo
        string m = tab + "Soy el Proceso " + to_string(i+1); 

        SaludoConTiempoRandom saludo(m);

        // genero el hilo dentro del vector
        threads[i] = thread(miOtroSaludo, saludo);        
    }

    for (auto& th : threads) {
        th.join();
    }
}

int main(){
    //semilla
    srand(time(0)); 

    // se inicia el proceso con parametro random, hilos a generar
    int hilosRnd = rand() % 15;

    cout << "Hola, estoy generando " + to_string(hilosRnd) + " procesos de forma random \n\n";
    generarThreads(hilosRnd);
}


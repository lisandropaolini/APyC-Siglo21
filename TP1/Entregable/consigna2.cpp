#include<iostream>
#include<thread>
#include<string>
#include<chrono>
#include <vector>
using namespace std ;

void miSaludo(string m, int veces){

    for (int i =1; i <= veces ; i ++) {
        // mensaje de salida por pantalla
        cout << m+"\n"; 

        //obtengo el random para la demora
        int demora = rand() % 400 + 300; 

        this_thread::sleep_for(chrono::milliseconds(demora));
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
        string m = tab + "Soy el proceso " + to_string(i+1); 

        // genero el hilo dentro del vector
        threads[i] = thread(miSaludo, m, 3);        
    }

    for (auto& th : threads) {
        th.join();
    }
}

int main(){
    //semilla
    srand(time(0)); 
    
    // se inicia el proceso con parametro de 15, hilos a generar
    generarThreads(15);
}

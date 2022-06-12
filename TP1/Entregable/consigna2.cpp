#include<iostream>
#include<thread>
#include<string>
#include<chrono>
#include <vector>
using namespace std ;
void saludo(string m, int veces){

    int numero, min, max, demora;
    srand(time(0)); //semilla

    for (int i =1; i <= veces ; i ++) {
        cout << m+"\n"; // mensaje de salida por pantalla

        demora = rand() % 100 + 500; //obtengo el random para la demora

        this_thread::sleep_for(chrono::milliseconds(demora));
    }
}

void generarThreads(int n){
    std::vector<thread> threads(n);
    for (int i = 0; i < n; i++) {
        string tab = "";
        for (int j = 0; j < i; j++) {
            tab = tab + "\t";
        }
        int soyInt = i+1;
        string m = tab + "Soy el proceso " + to_string(soyInt);
        threads[i] = thread(saludo, m, 3);        
    }

    for (auto& th : threads) {
        th.join();
    }
}

int main(){
    generarThreads(15);
}

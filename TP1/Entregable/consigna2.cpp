#include<iostream>
#include<thread>
#include<string>
#include<chrono>
#include <vector>
using namespace std ;
void saludo(string m, int demora, int veces){
    for (int i =1; i <= veces ; i ++) {
        cout << m+"\n";
        this_thread::sleep_for(chrono::milliseconds(demora));
    }
}
// int main(){
//     thread P[15];
//     for (int i =1; i <= 15 ; i ++) {
//         string m = "Soy " + to_string(i);
//         P[i]=thread(&saludo, m, 100, 3);
//     }

//     cout << "join \n";

//     for (int i =1; i <= 15 ; i ++) {
//         P[i].join();
//     }

//     cout << "Fin \n";
//     return 0;
// }

void generarThreads(int n){
    std::vector<thread> threads(n);
    for (int i = 0; i < n; i++) {
        string tab = "";
        for (int j = 0; j < i; j++) {
            tab = tab + "\t";
        }
        int soyInt = i+1;
        string m = tab + "Soy el proceso " + to_string(soyInt);
        threads[i] = thread(saludo, m, 100, 3);
    }

    for (auto& th : threads) {
        th.join();
    }
}

int main(){
    generarThreads(15);
}
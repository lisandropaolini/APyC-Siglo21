#include<iostream>
#include<string>
using namespace std ;

int main(int argc, char *argv[]) {

    if (argc < 2) {
        cerr << "Valor de N y M no ingresado !" << endl;
        exit(EXIT_FAILURE);
    }

    if (argc < 3) {
        cerr << "Valor de M no ingresado !" << endl;
        exit(EXIT_FAILURE);
    }

    string m= argv[1];
    cerr << "Valor de N " + m+"\n";
    m=  argv[2];
    cerr << "Valor de M " + m+"\n";

    exit(EXIT_SUCCESS);
}
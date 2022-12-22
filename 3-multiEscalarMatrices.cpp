#include <string>
#include <iostream>
#include <iomanip>

using namespace std;

class Matrices{
public:
    Matrices(int filas, int columnas);
    void rellenar();
    void imprimir();
    float matriz[10][10];
    int filas;
    int columnas;
private:
protected:
};

void multiEscalarMatriz(Matrices& matriz, float& escalar);

int main(){
    string nombre;
    int filas, columnas;
    float escalar;
    cout << "Ingrese la cantidad de la filas de la matriz: " << endl;
    cin >> filas;
    cout << "Ingrese la cantidad de la columnas de la matriz: " << endl;
    cin >> columnas;
    Matrices matriz(filas, columnas);
    matriz.rellenar();

    cout << "Ingrese el escalar para la multiplicacion: " << endl;
    cin >> escalar;

    multiEscalarMatriz(matriz, escalar);

    return 0;
}

Matrices::Matrices(int filas, int columnas){
    this->filas = filas;
    this->columnas = columnas;
}

void Matrices::rellenar(){
    for(int i = 0; i < filas; i++){
        for(int j = 0; j < columnas; j++){
            cout << "Ingrese el valor de la matriz [" << i << "][" << j << "]: ";
            cin >> matriz[i][j];
            cout << endl;
        }
    }
}

void Matrices::imprimir(){
    for(int i = 0 ; i < filas ; i++){
        cout << "|";
        for(int j = 0 ; j < columnas ; j++){
            cout << setw(7) << matriz[i][j] << " ";
            }
        cout << "|" << endl;
    }
    cout << endl;
}

void multiEscalarMatriz(Matrices& matriz, float& escalar){
    Matrices temp(matriz.filas, matriz.columnas);
    for(int i = 0; i < matriz.filas; i++){
        for(int j = 0; j < matriz.columnas; j++){
            temp.matriz[i][j] = matriz.matriz[i][j] * escalar;
        }
    }

    cout << "El resultado de la multiplicacion por el escalar es:" << endl;
    temp.imprimir();
}

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

void multiplicarMatrices(Matrices& M01, Matrices& M02);

int main(){
    string nombre;
    int filas, columnas;
    cout << "Ingrese la cantidad de la filas de la matriz 01: " << endl;
    cin >> filas;
    cout << "Ingrese la cantidad de la columnas de la matriz 01: " << endl;
    cin >> columnas;
    Matrices matriz01(filas, columnas);
    matriz01.rellenar();

    cout << "Ingrese la cantidad de la filas de la matriz 02: " << endl;
    cin >> filas;
    cout << "Ingrese la cantidad de la columnas de la matriz 02: " << endl;
    cin >> columnas;
    Matrices matriz02(filas, columnas);
    matriz02.rellenar();

    multiplicarMatrices(matriz01, matriz02);

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
            cout << setw(5) << matriz[i][j] << " ";
            }
        cout << "|" << endl;
    }
    cout << endl;
}

void multiplicarMatrices(Matrices& M01, Matrices& M02){
    if(M01.filas == M01.columnas && M02.filas == M02.columnas){ // cuadradas?
        if(M01.filas != M02.columnas){
            cout << "Las matrices no tienen las mismas dimensiones" << endl;
            return;
        }
    }else {
        if(M01.columnas != M02.filas){
            cout << "No se puede operar, las columnas de la matriz '01' y las filas de la matriz '02' no coinciden ..." << endl;
            return;
        }
    }

    Matrices temp(M01.filas, M02.columnas);
    for(int i = 0; i < M01.filas; i++){
        for(int j = 0; j < M02.columnas; j++){
            temp.matriz[i][j] = 0;
            for(int z = 0; z < M01.columnas; z++){
                temp.matriz[i][j] += M01.matriz[i][z] * M02.matriz[z][j];
            }
        }
    }

    cout << "El resultado de la suma es:" << endl;
    temp.imprimir();
}

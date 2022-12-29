#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

class Matrices{
public:
    Matrices(int filas, int columnas);
    void rellenar();
    void imprimir();
    void metodoGauss();
    void pivoteoMatriz(int filInit, int colInit);
    float matriz[10][10];
    int filas;
    int columnas;
private:
protected:
};

int main(){
    string nombre;
    int filas, columnas;
    cout << "Ingrese la cantidad de la filas de la matriz: " << endl;
    cin >> filas;
    cout << "Ingrese la cantidad de la columnas de la matriz: " << endl;
    cin >> columnas;

    if(filas != (columnas-1)){
        cout << "No se puede calcular, la matriz es incorrecta... " << endl;
        return 0;
    }

    Matrices matriz(filas, columnas);
    matriz.rellenar();
    cout << "La matriz tiene los elementos:" << endl;
    matriz.imprimir();
    matriz.metodoGauss();

    return 0;
}


void Matrices::metodoGauss(){
    Matrices temporal(filas, columnas);

    for(int i=0; i < filas; i++){ // copiar datos de la matriz original
        for(int j=0; j < columnas; j++){
            temporal.matriz[i][j] = matriz[i][j];
        }
    }

    temporal.pivoteoMatriz(0, 0); // ordenar de mayor a menor
    cout << "\nLuego de ordenas las ecuaciones de mayor a menor obtenemos: " << endl;
    temporal.imprimir();

    int iterador = 1;
    for(int k = 0; k < filas; k++){// recorremos la diagonal para ver si existe un elemento igual a CERO
        if(temporal.matriz[k][k] == 0){
            cout << "La matriz no tiene solucion, un elemento de la diagonal es 0..." << endl;
            return;
        } else {// metodo de gauss
            for(int i = k+1; i < filas; i++){ // recorremos la fila
                double aux = temporal.matriz[i][k]; // evitar perder el valor original
                for(int j = k; j < columnas; j++){ // recorremos las columnas de la fila
                    temporal.matriz[i][j] = temporal.matriz[i][j] - ((aux/temporal.matriz[k][k]) * temporal.matriz[k][j]);
                    temporal.matriz[i][j] = trunc(temporal.matriz[i][j]*1000)/1000;// redondear
                }
                cout << "\n0" << iterador++ << " iteracion:" << endl;
                temporal.imprimir();
            }
        }
    }

    // Vertificar que los elementos operados sean igual a CERO(matriz escalonada)
    bool fallo = false;
    for(int i=1; i < temporal.filas; i++){
        for(int j=0; j < i; j++){
            if(temporal.matriz[i][j] != 0)
                fallo = true; // alguno de los elementos de la escalera inferior es diferente de CERO
        }
    }

    if(fallo){
        cout << "Imposible calcular las incognitas, el metodo de GAUSS fallo..." << endl;
        return;
    }

     /**************************** obtener el valor de las incognitas *****************************/
    int filT = temporal.filas;
    int colT = temporal.columnas;
    double* incognitas = new double[filT];

    // obtenemos la ultima incognita para operar el resto
    incognitas[filT-1] = temporal.matriz[filT-1][colT-1]/temporal.matriz[filT-1][colT-2];
    double operacion = 0;
    for(int i=filT-2; i >= 0; i--){
        for(int j=i+1; j < colT-1; j++){
            operacion += temporal.matriz[i][j] * incognitas[j];
        }
        incognitas[i] = (temporal.matriz[i][temporal.columnas-1]-operacion)/temporal.matriz[i][i];
        operacion = 0; // reiniciando sumador
    }

    // imprimir valor de las incognitas
    int caracter = 97;
    cout << "El valor de las incognitas es: " << endl;
    for(int i = 0; i < filT; i++)
        cout << (char)(caracter+i) << " = " << incognitas[i] << endl;

}

void Matrices::pivoteoMatriz(int filInit, int colInit){
    float mayor, comparar, aux1, aux2;
    for(int k = filInit; k < filas; k++){
        mayor = abs(matriz[k][colInit]);
        for(int i = k+1; i < filas; i++){
            comparar = abs(matriz[i][colInit]);
            if(mayor < comparar){
                mayor = comparar;
                for(int j = 0; j < columnas; j++){ // intercambiamos filas
                    aux1 = matriz[k][j];
                    aux2 = matriz[i][j];
                    matriz[k][j] = aux2;
                    matriz[i][j] = aux1;
                }
            }
        }
    }
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
    int caracter = 97;
    for(int i = 0 ; i < filas ; i++){
        cout << "|";
        for(int j = 0 ; j < columnas ; j++){
            if(j == columnas-1){
                cout << "  = ";
                cout << setw(5)  << setprecision(3) << matriz[i][j] << " ";
            } else {
                cout << setw(7)  << setprecision(3) << matriz[i][j];
                cout << (char)(caracter+j) << " ";
            }
        }
        cout << "|" << endl;
    }
    cout << endl;
}

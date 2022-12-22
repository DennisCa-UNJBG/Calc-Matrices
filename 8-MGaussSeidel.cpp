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
    void metodoGaussSeidel();
    void pivoteoMatriz(int filInit, int colInit);
    bool EpsilonSeidel(double* oldSol, double* newSol, int cantidad);
    bool DiagonalDominante();
    void imprimirIncognitas(double* array);
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
    matriz.metodoGaussSeidel();

    return 0;
}

void Matrices::imprimirIncognitas(double* array){
    int caracter = 97;
    for(int i = 0; i < this->filas; i++)
        cout << "\t" << (char)(caracter+i) << " = " << array[i] << endl;
}

bool Matrices::EpsilonSeidel(double* oldSol, double* newSol, int cantidad){
    double EPSILON = 0.01; // error iterativo como tolerancia
    double aux = 0;
    for(int i = 0; i < cantidad; i++){
        aux = ((newSol[i] - oldSol[i]) / newSol[i]) * 100;
        //cout << newSol[i] << " - " << oldSol[i] << " '"<< aux <<"' --"; // para ver los calculos
        if(abs(aux) < EPSILON)
            return false;
    }
    cout << endl;
    return true;
}

bool Matrices::DiagonalDominante(){
    for(int i=0; i < this->filas; i++){
        float sumador = 0;
        for(int j=0; j < this->columnas-1; j++){
            if(i == j)
                continue;

            sumador += abs(this->matriz[i][j]);
        }
        if(abs(this->matriz[i][i]) < sumador) // si la diagonal no es dominante abortamos
            return false;
    }

    return true;
}

void Matrices::metodoGaussSeidel(){
    // usamos una variable temporal para no afectar a la matriz original
    Matrices* temporal = new Matrices(this->filas, this->columnas);
    // copiar datos de la matriz original
    for(int i=0; i < this->filas; i++){
        for(int j=0; j < this->columnas; j++){
            temporal->matriz[i][j] = this->matriz[i][j];
        }
    }
    // creando vector dominante
    for(int i = 0; i < this->filas; i++)
        temporal->pivoteoMatriz(i, i); // ordenar ecuaciones por el primer elemento de mayor a menor

    cout << "\nLuego de ordenar las ecuaciones obtenemos el vector dominante: " << endl;
    temporal->imprimir();

    if(!temporal->DiagonalDominante()){
        cout << "ERROR: La diagonal no cumple con el requisito de ser dominante." << endl;
        return;
    }

    // crear nueva matriz para las incognitas
    double* incognitasOld = new double[temporal->filas];
    double* incognitasNew = new double[temporal->filas];
    for(int i = 0; i < temporal->filas; i++)
        incognitasOld[i] = 0; // rellenando matriz para evitar errores

    for(int i = 0; i < temporal->filas; i++)
        incognitasNew[i] = -10; // rellenando matriz para evitar errores

    // gauss seidel
    double sumador = 0;
    int k = 0;
    while (EpsilonSeidel(incognitasOld, incognitasNew, temporal->filas)){
        for(int i = 0; i < temporal->filas; i++){
            for(int j = 0; j < temporal->columnas-1; j++){
                if(i == j)
                    continue; // si i == J nose realiza ninguna operación
                sumador += temporal->matriz[i][j] * incognitasOld[j];
            }
            incognitasOld[i] = incognitasNew[i];
            incognitasNew[i] = (temporal->matriz[i][temporal->columnas-1] - sumador) / temporal->matriz[i][i];
            sumador = 0;
        }
        cout << "\n\t0" << k+1 << " iteracion:" << endl;
        temporal->imprimirIncognitas(incognitasNew);
        k++;
    }

    // liberar memoria
    delete []incognitasOld;
    delete []incognitasNew;
    delete temporal;
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

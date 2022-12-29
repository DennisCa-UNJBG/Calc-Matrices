#include <string>
#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

class Matrices{
public:
    Matrices(int orden);
    ~Matrices();
    void rellenar();
    void imprimir();
    double determinante(double** matriz, int filas);
    double cofactor(double** matriz, int orden, int fila, int columna);
    double calcularDeterminante();
    double** matriz;
    int orden;
private:
protected:
};

int main(){
    string nombre;
    int filas, columnas;
    double determinante;

    cout << "Ingrese la cantidad de la filas de la matriz: " << endl;
    cin >> filas;
    cout << "Ingrese la cantidad de la columnas de la matriz: " << endl;
    cin >> columnas;
    if(filas != columnas)
        cout << "No se puede calcular la determinante de la matriz, no es cuadrada... " << endl;
    else{
        Matrices matriz01(filas);
        matriz01.rellenar();
        determinante = matriz01.calcularDeterminante();
        cout << "La determinante de la matriz es: " << determinante << endl;
    }

    return 0;
}

Matrices::Matrices(int filas){
    this->orden = filas;

    matriz = new double*[filas];
    for(int i = 0; i < filas; i++)
        matriz[i] = new double[filas];
}

Matrices::~Matrices(){
    for (int i = 0; i < this->orden; i++)
        delete[] matriz[i];

    delete[] matriz;
}

void Matrices::rellenar(){
    for(int i = 0; i < orden; i++){
        for(int j = 0; j < orden; j++){
            cout << "Ingrese el valor de la matriz [" << i << "][" << j << "]: ";
            cin >> matriz[i][j];
            cout << endl;
        }
    }
}

void Matrices::imprimir(){
    for(int i = 0 ; i < orden ; i++){
        cout << "|";
        for(int j = 0 ; j < orden ; j++){
            cout << setw(7) << matriz[i][j] << " ";
            }
        cout << "|" << endl;
    }
    cout << endl;
}

double Matrices::cofactor(double** matriz, int orden, int fila, int columna){
    int n = orden - 1;
    double** submatriz = new double*[n];

    for (int i = 0; i < n; i++)
        submatriz[i] = new double[n];

    int x = 0;
    int y = 0;

    for (int i = 0; i < orden; i++){
        for (int j = 0; j < orden; j++){
            if (i != fila && j != columna){
                submatriz[x][y] = matriz[i][j];
                y++;
                if (y >= n){ //seguir copiando
                    x++;
                    y = 0;
                }
            }
        }
    }
    int det = determinante(submatriz, n);
    delete []submatriz; // liberar memoria
    return pow(-1.0, fila + columna) * det;
}

double Matrices::determinante(double** matriz, int orden){
    int det = 0;
    if (orden == 1)
        det = matriz[0][0];
    else{
        for (int j = 0; j < orden; j++)
            det = det + matriz[0][j] * cofactor(matriz, orden, 0, j);
    }
    return det;
}

double Matrices::calcularDeterminante(){
    double deter = determinante(matriz, orden);
	return deter;
}

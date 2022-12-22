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
    Matrices* calcularInversa(double& deter);
    Matrices* traspuesta();
    double** matriz;
    int orden;
private:
protected:
};

int main(){
    string nombre;
    int filas, columnas;
    double determinante = 0;

    cout << "Ingrese la cantidad de la filas de la matriz: " << endl;
    cin >> filas;
    cout << "Ingrese la cantidad de la columnas de la matriz: " << endl;
    cin >> columnas;
    if(filas != columnas){
        cout << "No se puede calcular la determinante de la matriz, no es cuadrada... " << endl;
        return 0;
    }

    Matrices matriz01(filas);
    matriz01.rellenar();
    determinante = matriz01.calcularDeterminante();

    Matrices* inversa = matriz01.calcularInversa(determinante);
    cout << "La determinante de la matriz es: " << determinante << endl;
    cout << "La inversa de la matriz es: "<< endl;
    inversa->imprimir();

    return 0;
}

Matrices* Matrices::traspuesta(void){
    Matrices* resultado = new Matrices(this->orden);
    for (int i = 0; i < this->orden; i++){
        for (int j = 0; j < this->orden; j++){
            resultado->matriz[i][j] = this->matriz[j][i];
        }
    }
    return resultado;
}

Matrices* Matrices::calcularInversa(double& deter){
    Matrices* resultado = new Matrices(this->orden);
    // encontramos la matriz de cofactores
    for(int i = 0; i < this->orden; i++){
        for(int j = 0; j < this->orden; j++){
            resultado->matriz[i][j] = 0; // para evitar problemas
            resultado->matriz[i][j] = cofactor(this->matriz, orden, i, j);
        }
    }
    //transpuesta de la matriz
    Matrices* aux = resultado;
    resultado = aux->traspuesta();
    delete aux;
    // multiplicar por la determinante
    for(int i = 0; i < this->orden; i++){
        for(int j = 0; j < this->orden; j++){
            resultado->matriz[i][j] = resultado->matriz[i][j] / deter;
            // 'trunc' -> limitar los decimales
            resultado->matriz[i][j] = trunc((resultado->matriz[i][j]) * 1000)/1000.0f;
        }
    }
    return resultado;
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
                if (y >= n){
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

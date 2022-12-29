#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Declaración de la clase que representa una polinomio
class Polinomio{
public:
    Polinomio(int cant_terminos);
    double evaluarPoliUno(double x);
    double evaluarPoliDos(double x);
    void obtenerEpsilon();
    void imprimir();

private:
    int cant_terminos;
    double *coeficientes; // Coeficientes del polinomio
};

int main()
{
    int cant_terminos_01 = 0;
    cout << "Ingrese la cantidad de terminos del primer polinomio: " << endl;
    cin >> cant_terminos_01;

    Polinomio f(cant_terminos_01);

    int cant_terminos_02 = 0;
    cout << "Ingrese la cantidad de terminos del segundo polinomio: " << endl;
    cin >> cant_terminos_02;

    double valorOld = 2; // Valor inicial
    double eps = 0.07; // Tolerancia
    int maxIter = 100; // Número máximo de iteraciones
    bool cancelar = false;

    int i = 0;      // Contador de iteraciones
    double valorNew = valorOld; // Valor actual

    cout << "La polinomio ingresado es: " << endl;
    f.imprimir();

    cout << "Resultados:" << endl;
    cout << setw(10) << "Iteraciones"
        << setw(10) << "X Old"
        << setw(10) << "X New"
        << setw(10) << "|Xnew - Xold|" << endl;
    // Iteramos hasta que el valor actual sea suficientemente cercano a la raíz
    while (!cancelar && (i < maxIter)){
        // Aplicamos el algoritmo de Newton-Raphson
        //valorNew = (valorOld - (f.evaluarPoli(valorOld) / f.evaluarDerivada(valorOld)));
        cout << setw(10) << i
        << setw(10) << valorOld
        << setw(10) << valorNew
        << setw(10) << abs(valorNew - valorOld) << endl;
        if(eps > abs(valorNew - valorOld))
            cancelar = true;
        valorOld = valorNew; // Actualizamos el valor actual
        i++; // Incrementamos el contador de iteraciones
    }

    // Mostramos el resultado
    cout << "La raiz aproximada es: " << valorNew << endl;

    return 0;
}


// Constructor que recibe los coeficientes del polinomio
Polinomio::Polinomio(int cant_terminos){
    this->cant_terminos = cant_terminos;
    this->coeficientes = new double[cant_terminos+1];

    for (int i = 0; i <= cant_terminos; i++){
        cout << "Ingrese el coeficiente X^" << i <<"= ";
        cin >> coeficientes[i];
    }
}

void Polinomio::imprimir(){
    for (int i = grado; i >= 0; i--){
        cout << coeficientes[i]<< "X^" << i << "  ";
    }
    cout << endl;
}

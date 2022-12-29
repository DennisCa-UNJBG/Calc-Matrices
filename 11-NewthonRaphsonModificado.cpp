#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Declaración de la clase que representa una polinomio
class Polinomio{
public:
    Polinomio(int grado);
    double evaluarPoli(double x);
    double evaluarDerivada(double x);
    double evaluarSegundaDerivada(double x);
    void obtenerDerivada();
    void obtenerSegundaDerivada();
    void imprimir();

private:
    int grado; // Grado del polinomio
    double *coeficientes; // Coeficientes del polinomio
};

int main()
{
    int grado = 0;
    cout << "Ingrese el grado del polinomio: " << endl;
    cin >> grado;

    Polinomio f(grado);

    double valor1 = 2; // Valor inicial
    double eps = 0.07; // Tolerancia
    int maxIter = 100; // Número máximo de iteraciones
    bool cancelar = false;

    int i = 1;      // Contador de iteraciones
    double valor2 = valor1; // Valor actual

    cout << "La polinomio ingresado es: " << endl;
    f.imprimir();

    cout << "La derivada del polinomio es: " << endl;
    f.obtenerDerivada();

    cout << "Resultados:" << endl;
    cout << setw(10) << "Iteraciones"
        << setw(10) << "X Old"
        << setw(10) << "X New"
        << setw(15) << "|Xnew - Xold|" << endl;
    // Iteramos hasta que el valor actual sea suficientemente cercano a la raíz
    while (!cancelar && (i < maxIter)){
        // Aplicamos el algoritmo de Newton-Raphson
        valor2 = valor1 - (f.evaluarPoli(valor1) * f.evaluarDerivada(valor1)) / (pow(f.evaluarDerivada(valor1), 2) - (f.evaluarPoli(valor1) * f.evaluarSegundaDerivada(valor1)));
        cout << setw(10) << i
        << setw(10) << valor1
        << setw(10) << valor2
        << setw(15) << abs(valor2 - valor1) << endl;
        if(eps > abs(valor2 - valor1))
            cancelar = true;
        valor1 = valor2; // Actualizamos el valor actual
        i++; // Incrementamos el contador de iteraciones
    }

    // Mostramos el resultado
    cout << "La raiz aproximada es: " << valor2 << endl;

    return 0;
}


// Constructor que recibe los coeficientes del polinomio
Polinomio::Polinomio(int grado){
    this->grado = grado;
    this->coeficientes = new double[grado+1];

    for (int i = 0; i <= grado; i++){
        cout << "Ingrese el coeficiente X^" << i <<"= ";
        cin >> coeficientes[i];
    }
}

    // Método para evaluarPoli el polinomio en un punto dado
double Polinomio::evaluarPoli(double x){
    double result = 0;
    for (int i = grado; i >= 0; i--){
        result += coeficientes[i] * pow(x, i);
    }
    //cout << result << endl;
    return result;
}

// Método para evaluar la segunda derivada del polinomio en un punto dado
double Polinomio::evaluarSegundaDerivada(double x){
    double result = 0;
    for (int i = grado; i >= 2; i--){
        result += coeficientes[i] * i * (i-1) * pow(x, i - 2);
    }
    //cout << result << endl;
    return result;
}

// Método para evaluar la derivada del polinomio en un punto dado
double Polinomio::evaluarDerivada(double x){
    double result = 0;
    for (int i = grado; i >= 1; i--){
        result += i * coeficientes[i] * pow(x, i - 1);
    }
    //cout << result << endl;
    return result;
}

void Polinomio::obtenerSegundaDerivada(){
    for (int i = grado; i >= 2; i--){
        cout << coeficientes[i] * i *(i-1) << "X^" << (i - 2) << "  ";
    }
    cout << endl;
}

void Polinomio::obtenerDerivada(){
    for (int i = grado; i >= 1; i--){
        cout << coeficientes[i] * i << "X^" << (i - 1) << "  ";
    }
    cout << endl;
}

void Polinomio::imprimir(){
    for (int i = grado; i >= 0; i--){
        cout << coeficientes[i]<< "X^" << i << "  ";
    }
    cout << endl;
}

#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

// Declaración de la clase que representa una polinomio
class Polinomio{
public:
    Polinomio(int grado);
    double evaluarPoli(double x);
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

    double xa = 0;
    double xb = 1;
    double eps = 0.07; // Tolerancia
    int maxIter = 30; // Número máximo de iteraciones
    bool cancelar = false;
    int i = 1;      // Contador de iteraciones
    double xrOld = 0;
    double xrNew = 0;

    cout << "La polinomio ingresado es: " << endl;
    f.imprimir();

    cout << "Resultados:" << endl;
    cout << setw(10) << "Iteraciones"
        << setw(10) << "xa"
        << setw(10) << "xb"
        << setw(12) << "xr"
        << setw(12) << "f(xa)*f(xr)"
        << setw(12) << "Epsilon" << endl;

    // Iteracion 0
    xrNew = (xa + xb)/2;

    cout << setw(10) << i-1
        << setw(10) << xa
        << setw(10) << xb
        << setw(10) << xrNew
        << setw(12) << f.evaluarPoli(xrNew) * f.evaluarPoli(xa)
        << setw(12) << "---" << endl;
    // Aplicamos el algoritmo
    if (f.evaluarPoli(xrNew) * f.evaluarPoli(xa) < 0)
        xb = xrNew;
    else
        xa = xrNew;
    xrOld = xrNew;

    // Iteramos el resto
    while (!cancelar && (i < maxIter)){
        xrNew = (xa + xb)/2; // Hallar el punto medio del intervalo

        cout << setw(10) << i
        << setw(10) << xa
        << setw(10) << xb
        << setw(10) << xrNew
        << setw(12) << f.evaluarPoli(xrNew) * f.evaluarPoli(xa)
        << setw(12) << abs((xrNew - xrOld)/xrNew) * 100 << endl;

        // Aplicamos el algoritmo
        if (f.evaluarPoli(xrNew) * f.evaluarPoli(xa) < 0)
            xb = xrNew;
        else
            xa = xrNew;

        if((abs((xrNew - xrOld)/xrNew) * 100) < eps)
            cancelar = true;
        xrOld = xrNew;
        i++; // Incrementamos el contador de iteraciones
    }

    // Mostramos el resultado
    cout << "La raiz aproximada es: " << xrNew << endl;

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

void Polinomio::imprimir(){
    for (int i = grado; i >= 0; i--){
        cout << coeficientes[i]<< "X^" << i << "  ";
    }
    cout << endl;
}

#include <iostream>
#include <cmath>

using namespace std;

// Declaración de la clase que representa una función polinomial
class Polynomial
{
public:
    // Constructor que recibe los coeficientes del polinomio
    Polynomial(int degree, double coefficients[])
    {
        this->degree = degree;
        this->coefficients = coefficients;
    }

    // Método para evaluar el polinomio en un punto dado
    double evaluate(double x)
    {
        double result = 0;
        for (int i = 0; i <= degree; i++)
        {
            result += coefficients[i] * pow(x, i);
        }
        return result;
    }

    // Método para evaluar la derivada del polinomio en un punto dado
    double derivative(double x)
    {
        double result = 0;
        for (int i = 1; i <= degree; i++)
        {
            result += i * coefficients[i] * pow(x, i - 1);
        }
        return result;
    }

private:
    // Grado del polinomio
    int degree;

    // Coeficientes del polinomio
    double *coefficients;
};

int main()
{
    double coefs[] = {-5, -2, 0, 1}; // Coeficientes del polinomio x^3 - 2x - 5
    Polynomial f(3, coefs);          // Creamos una instancia de la clase que representa el polinomio

    double x0 = 2;        // Valor inicial
    double eps = 0.00001; // Tolerancia
    int maxIter = 100;    // Número máximo de iteraciones

    int i = 0;      // Contador de iteraciones
    double x1 = x0; // Valor actual

    // Iteramos hasta que el valor actual sea suficientemente cercano a la raíz
    while (fabs(f.evaluate(x1)) > eps && i < maxIter)
    {
        x1 = x0 - f.evaluate(x0) / f.derivative(x0); // Aplicamos el algoritmo de Newton-Raphson
        x0 = x1;                                     // Actualizamos el valor actual
        i++;                                         // Incrementamos el contador de iteraciones
    }

    // Mostramos el resultado
    cout << "La raíz aproximada es: " << x1 << endl;

    return 0;
}

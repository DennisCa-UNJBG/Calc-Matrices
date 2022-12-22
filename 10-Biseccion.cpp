#include <iostream>
#include <cmath>

using namespace std;

// Clase que representa una ecuación polinómica
class EcuacionPolinomica {
private:
    // Coeficientes de la ecuación polinómica
    double coeficientes[4];
    
public:
    // Constructor de la clase
    EcuacionPolinomica(double a, double b, double c, double d) {
        coeficientes[0] = a;
        coeficientes[1] = b;
        coeficientes[2] = c;
        coeficientes[3] = d;
    }
    
    // Método que evalúa la ecuación polinómica en un punto dado
    double evaluar(double x) {
        // Se recorren los coeficientes de la ecuación polinómica
        double resultado = 0.0;
        for (int i = 0; i < 4; i++) {
            // Se suma el término correspondiente al coeficiente multiplicado por la potencia de x
            resultado += coeficientes[i] * pow(x, 3-i);
        }
        return resultado;
    }
};

// Implementación del método de la bisección
double biseccion(EcuacionPolinomica ecuacion, double a, double b, double tol) {
    // Verificar que la función cambie de signo en el intervalo [a,b]
    if (ecuacion.evaluar(a) * ecuacion.evaluar(b) >= 0) {
        cout << "El método no garantiza la existencia de una raíz en el intervalo dado" << endl;
        return NAN; // retornar NaN (Not-a-Number)
    }
    
    double c = a;
    while ((b-a) >= tol) {
        // Hallar el punto medio del intervalo
        c = (a+b)/2;
        
        // Si el punto medio es una raíz, retornar su valor
        if (ecuacion.evaluar(c) == 0)
            break;
        
        // Determinar en qué subintervalo se encuentra la raíz
        else if (ecuacion.evaluar(c)*ecuacion.evaluar(a) < 0)
            b = c;
        else
            a = c;
    }
    return c;
}

int main() {
    // Crear una ecuación polinómica
    EcuacionPolinomica ecuacion(1, -2, 3, -1); // ecuación: x^3 - 2x^2 + 3x - 1 = 0
    // Límites inferior y superior del intervalo donde se busca la raíz
    double a = 1.0;
    double b = 2.0;
    // Tolerancia
    double tol = 1e-6;

    double raiz = biseccion(ecuacion, a, b, tol);
    cout << "La raíz aproximada es: " << raiz << endl;

    return 0;
}

/*
En este caso, se ha creado una clase `EcuacionPolinomica` que representa una ecuación polinómica y tiene un método `evaluar` que permite evaluar la ecuación en un punto dado. La función `biseccion` ahora recibe como argumento un objeto de la clase `EcuacionPolinomica` en lugar de un array de coeficientes. Esto permite una implementación más sencilla y legible del código.
*/

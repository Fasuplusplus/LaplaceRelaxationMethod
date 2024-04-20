// Calcular el potencial electrostático alrededor de dos esferas conductoras de cargas conocidas usando método de relajación
// TODAS LAS UNIDADES EN MKS
// Voy a plantear el problema como uno bidimensional en coordenadas cilindricas
// Hola profe
//actualmente el programa crea la grilla y las esferas e imprime todo
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
// Dump "temporal" de variables
float r1 = 6; // radios de las esferas 1 y 2
float r2 = 4;
const int size = 51;       // cantidad de filas y columnas :: Conviene setear a un impar para que existan los centros como puntos discretos
float range = 100;         // valor máximo para r y z
float step = range / size; // tamaño en el continuo de cada paso discreto, mi constante de conversión entre pasos discretos y continuos
float Grid[size][size];    // Grid (r,z)
float q1 = 6;              // cargas de las esferas 1 y 2
float q2 = 5;
float v1 = 4; // potenciales de las esferas 1 y 2 :: posteriormente se van a calcular con las capacitancias
float v2 = 8;
float h = 20;       // altura del centro de la esfera 2
float Zp(float z) { // transformada de z a z'(el que interesa al usuario)
    return (z - range / 2);
}
float Z(float zp) { // transformada de z'(el que interesa al usuario) a z
    return (zp + range / 2);
}
void bigBang() {                          // crear esferas
    for (int i = 0; i < r1 / step; i++) { // Crear esferas (poner puntos dentro del radio a potencial fijo para un rectángulo de r*r centrado en cada esfera)
        for (int j = 0; j < (2 * r1) / step; j++) {
            if (i * step * i * step + (j * step - r1) * (j * step - r1) <= r1 * r1) {
                Grid[i][j + static_cast<int>(round(((range / 2) - r1) / step))] = v1;
            }
        }
    }
    for (int i = 0; i < r2 / step; i++) { // segunda esfera :: ROTO
        for (int j = 0; j < (2 * r2) / step; j++) {
            if (i * step * i * step + (j * step - r2) * (j * step - r2) <= r2 * r2) {
                Grid[i][j + static_cast<int>(round(((range / 2) + h - r2) / step))] = v2;
            }
        }
    }
}
int main() { // main para testear cosas
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            Grid[i][j] = 1;
        }
    }
    bigBang();
    cout << "hola\n";
    for (int j = size - 1; j >= 0; j--) { // esta es una version primitiva de la graficadora (en realidad es la graficadora completa pero tengo que reducirla para no imprimir 1 millon de casillas despues)
        cout << "\n";
        for (int i = 0; i < size; i++) {
            cout << Grid[i][j] << " ";
        }
    }
    return (0);
}
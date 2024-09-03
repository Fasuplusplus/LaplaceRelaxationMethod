// Calcular el potencial electrostático alrededor de dos esferas conductoras de cargas conocidas usando método de relajación
// TODAS LAS UNIDADES EN MKS
// Voy a plantear el problema como uno bidimensional en coordenadas cilindricas, con la esfera 1 en el centro y elcentro de la 2 a una altura h del centro de la primera
// Hola profe
// actualmente el programa crea la grilla y las esferas, hace una aproximación cruda del potencial e imprime todo
#include <cmath>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
// Variables globales
double r1 = 10;                  // radio de la esfera 1
double r2 = 8;                   // radio de la esfera 2
const int size = 500;            // cantidad de filas y columnas :: Conviene setear a un valor tq que existan los centros como puntos discretos
double range = 1000;             // valor máximo para r y z
double step = range / size;      // tamaño en el continuo de cada paso discreto, mi constante de conversión entre pasos discretos y continuos
double Grid[size][size];         // Grid [k][s] con contraparte continua (r,z)
double q1 = 0.0000000066759;     // carga de la esfera 1
double q2 = 0.0000000080111;     // carga de la esfera 2
double v1 = 6;                   // potencial de la esfera 1; se va a calcular mas adelante con una función de capacitancia
double v2 = 9;                   // potencial de la esfera 2; idem
double h = 20;   // altura en z' del centro de la esfera 2
const double K = 8987551787.368; // Constante de Coulomb(1/4Pie0)
// funciones frecuentes
double Zp(double z) { // transformada de z a z'(el que interesa al usuario)
    return (z - range / 2);
}
double Z(double zp) { // transformada de z'(el que interesa al usuario) a z
    return (zp + range / 2);
}
bool isBall1(int k, int s) { // ¿esta la casilla [k][s] dentro de la esfera 1?
    if (pow(k * step, 2) + pow(Zp(s * step), 2) <= pow(r1, 2)) {
        return (1);
    }
    else {
        return (0);
    }
}
bool isBall2(int k, int s) { // ¿esta la casilla [k][s] dentro de la esfera 2?
    if (pow(k * step, 2) + pow((Zp(s * step) - h), 2) <= pow(r2, 2)) {
        return (1);
    }
    else {
        return (0);
    }
}
// funciones principales
void CalcV() {                                                               // ejecutar todos los cálculos de capacitancia necesarios para obtener v1 y v2 :: todo sacado de  doi: 10.1098/rspa.2012.0133
    double U = acosh((pow(h, 2) - pow(r1, 2) - pow(r2, 2)) / (2 * r1 * r2)); // Parámetro adimensional que se usa en la capacitancia
    if (U == 0 || isnan(U)) {
        cout << "Error en calculo de U. Revisar radios de esferas y distancia entre ellas.\n";
        return;
    }
    double Caa = 0; // capacitancias creadas, las inicializamos ahora en el loop de suma
    double Cbb = 0;
    double Cab = 0;
    for (unsigned int n = 0; n < 4294967294; n++) { // calcular Caa :: por las dudas que el loop pare 1 numero antes de hacer overflow
        double term = (r1 * r2 * sinh(U)) / (r1 * sinh(n * U) + r2 * sinh((n + 1) * U));
        if (term <= 1e-18) {
            break;
        }
        else {
            Caa = Caa + term;
        }
    }
    for (unsigned int n = 0; n < 4294967294; n++) { // calcular Cbb :: por las dudas que el loop pare 1 numero antes de hacer overflow
        double term = (r1 * r2 * sinh(U)) / (r2 * sinh(n * U) + r1 * sinh((n + 1) * U));
        if (term <= 1e-18) {
            break;
        }
        else {
            Cbb = Cbb + term;
        }
    }
    for (unsigned int n = 1; n < 4294967294; n++) { // calcular Cab :: Notar que es una suma distinta en dónde comienza y en forma general
        double term = ((-(r1 * r2) / h) * sinh(U)) / (sinh(n * U));
        if (abs(term) <= 1e-18) {
            break;
        }
        else {
            Cab = Cab + term;
        }
    }
}
void bigBang() { // crear condiciones iniciales
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) { // dar a cada punto un valor de potencial calculado por una versión simplificada de la superposición de los potenciales de dos cargas puntuales en los centros de cada esfera
            Grid[i][j] = K * (q1 / (abs(step * i) + abs(Zp(step * j))) + q2 / (abs(step * i) + abs(Zp(step * j) - h)));
        }
    }
    for (int i = 0; i <= r1 / step + 1; i++) {                                              // Crear esferas (poner puntos dentro del radio a potencial fijo para un cuadrado de 2(r+step)*2(r+step) centrado en cada esfera) :: tener en cuenta que solo tomamos la  mitad derecha del problema en cuenta
        for (int j = size / 2 - r1 / step - 1; j <= size / 2 + r1 / step + 1 / step; j++) { // esfera 1, cuadrado centrado en (r,z')=(0,0)
            if (isBall1(i, j)) {
                Grid[i][j] = v1;
            }
        }
    }
    for (int i = 0; i <= r2 / step + 1; i++) {
        for (int j = size / 2 - (r2 - h) / step - 1; j <= size / 2 + (r2 + h) / step + 1 / step; j++) { // segunda esfera, cuadrado centrado en (r,z')=(0,h)
            if (isBall2(i, j)) {
                Grid[i][j] = v2;
            }
        }
    }
}
// main
int main() { // main para testear cosas
    CalcV();
    bigBang();
    cout << "hola\n";
    ofstream output;
    output.open("output.txt");
    for (int j = size - 1; j >= 0; j--) { // esta es una version primitiva de la graficadora (en realidad es la graficadora completa)
        output << "\n";
        for (int i = 0; i < size; i++) {
            output << (int)Grid[i][j] << " ";
        }
    }
    output.close();
    cout << "done";
    return (0);
}
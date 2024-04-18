// Calcular el potencial electrostático alrededor de dos esferas conductoras de cargas conocidas usando método de relajación
// Voy a plantear el problema como uno bidimensional en coordenadas cilindricas
// Hola profe
#include <cmath>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
// Dump "temporal" de variables
unsigned int rad1; // radios de las esferas 1 y 2
unsigned int rad2;
float q1; // cargas de las esferas 1 y 2
float q2;
float v1; // potenciales de las esferas 1 y 2 :: posteriormente se van a calcular con las capacitancias
float v2;
void bigBang(unsigned int size, unsigned int range) { // crear grid y esferas :: size: cantidad de filas y columnas. range: valor máximo para r y z
    float Grid[size][size]; //Crear grid (r,z) :: capaz despues lo pase a int si algun error de float me jode
     //divido esta parte que genera las esferas en una funcion aparte para mejor legibilidad?
}
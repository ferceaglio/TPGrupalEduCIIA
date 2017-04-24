#include "configuracion.h"

#define MILLIS_ENTRE_PISOS_DEFAULT          1000
#define MILLIS_APERTURA_PUERTAS_DEFAULT     1000
#define CANTIDAD_PISOS_DEFAULT              5
#define CANTIDAD_SUBSUELOS_DEFAULT          1
#define CANTIDAD_MAX_PISOS                  20
#define CANTIDAD_MIN_PISOS                  1
#define CANTIDAD_MAX_SUBSUELOS              5
#define CANTIDAD_MIN_SUBSUELOS              0

uint16_t velocidadEntrePisos = MILLIS_ENTRE_PISOS_DEFAULT;
uint16_t velocidadPuertas = MILLIS_APERTURA_PUERTAS_DEFAULT;
uint8_t cantidadPisos = CANTIDAD_PISOS_DEFAULT;
uint8_t cantidadSubsuelos = CANTIDAD_SUBSUELOS_DEFAULT;

uint16_t obtenerVelocidadEntrePisos() {

    return velocidadEntrePisos;
}

uint16_t obtenerVelocidadPuertas() {

    return velocidadPuertas;
}

uint8_t obtenerCantidadPisos() {

    return cantidadPisos;
}

uint8_t obtenerCantidadSubsuelos() {

    return cantidadSubsuelos;
}

void configurarVelocidadEntrePisos(uint16_t nuevaVelocidadEntrePisos) {

    velocidadEntrePisos = nuevaVelocidadEntrePisos;
}

void configurarVelocidadPuertas(uint16_t nuevaVelocidadPuertas) {

    velocidadPuertas = nuevaVelocidadPuertas;
}

bool_t configurarCantidadPisos(uint8_t nuevaCantidadPisos) {
    
    bool_t cantidadValida = nuevaCantidadPisos <= CANTIDAD_MAX_PISOS && nuevaCantidadPisos >= CANTIDAD_MIN_PISOS;

    if (cantidadValida) {
    
        cantidadPisos = nuevaCantidadPisos;
    }
    
    return cantidadValida;
}

bool_t configurarCantidadSubsuelos(uint8_t nuevaCantidadSubsuelos) {

    bool_t cantidadValida = nuevaCantidadSubsuelos <= CANTIDAD_MAX_SUBSUELOS && nuevaCantidadSubsuelos >= CANTIDAD_MIN_SUBSUELOS;

    if (cantidadValida) {
    
        cantidadSubsuelos = nuevaCantidadSubsuelos;
    }
    
    return cantidadValida;
}
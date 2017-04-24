#ifndef _CONFIGURACION_H_
#define _CONFIGURACION_H_

#include "sapi.h"

uint16_t obtenerVelocidadEntrePisos();
uint16_t obtenerVelocidadPuertas();
uint8_t obtenerCantidadPisos();
uint8_t obtenerCantidadSubsuelos();

void configurarVelocidadEntrePisos(uint16_t nuevaVelocidadEntrePisos);
void configurarVelocidadPuertas(uint16_t nuevaVelocidadPuertas);
void configurarCantidadPisos(uint8_t nuevaCantidadPisos);
void configurarCantidadSubsuelos(uint8_t nuevaCantidadSubsuelos);

#endif
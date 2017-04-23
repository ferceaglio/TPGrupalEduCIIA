#ifndef _MEF_ASCENSOR_H_
#define _MEF_ASCENSOR_H_

#include "sapi.h"

void ascensorInicializarMEF();
void ascensorActualizarMEF();

void enPlantaBaja();
void modoConfiguracion();
void bajando();
void subiendo();
void parado();
void yendoAPlantaBaja();

void reconfigurarDelayEntrePisos();
void reconfigurarDelayTimeOutParado();
bool_t chequearSolicitudDePiso();
void ledsEnMovimiento();
void ledsSinMovimiento();
void ledsConfigurando();

#endif
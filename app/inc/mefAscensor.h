#ifndef _MEF_ASCENSOR_H_
#define _MEF_ASCENSOR_H_

#include "sapi.h"

typedef enum {

    EN_PLANTA_BAJA,
    MODO_CONFIGURACION,
    BAJANDO,
    SUBIENDO,
    PARADO,
    YENDO_A_PLANTA_BAJA
    
    } estadoAscensor;

void ascensorInicializarMEF();
void ascensorActualizarMEF();

void enPlantaBaja();
void modoConfiguracion();
void bajando();
void subiendo();
void parado();
void yendoAPlantaBaja();

void actualizarPisoActual(int8_t cantPisos);
void actualizarEstadoActual(estadoAscensor nuevoEstado);
void reconfigurarDelayEntrePisos();
void reconfigurarDelayTimeOutParado();
bool_t chequearSolicitudDePiso();
bool_t recibirPiso();
void ledsEnMovimiento();
void ledsSinMovimiento();
void ledsConfigurando();

#endif
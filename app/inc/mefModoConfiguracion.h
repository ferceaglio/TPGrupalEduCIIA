#ifndef _MEF_MODO_CONFIGURACION_H_
#define _MEF_MODO_CONFIGURACION_H_

#include "sapi.h"

typedef enum {

    ESPERANDO_COMANDO,
    CONFIGURANDO_VELOCIDAD_ENTRE_PISOS,
    CONFIGURANDO_VELOCIDAD_PUERTAS,
    CONFIGURANDO_CANTIDAD_PISOS,
    CONFIGURANDO_CANTIDAD_SUBSUELOS,
    FUERA_DE_CONFIGURACION

    } estadoModoConfiguracion;

void configurar();
bool_t configurando();

void esperandoComando();
void configurandoVelocidadEntrePisos();
void configurandoVelocidadPuertas();
void configurandoCantidadPisos();
void configurandoCantidadSubsuelos();

void actualizarEstado(estadoModoConfiguracion nuevoEstado);

#endif
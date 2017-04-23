#include "mefAscensor.h"

typedef enum {

    EN_PLANTA_BAJA,
    MODO_CONFIGURACION,
    BAJANDO,
    SUBIENDO,
    PARADO,
    YENDO_A_PLANTA_BAJA
    
    } estadoAscensor;

estadoAscensor estadoActual = EN_PLANTA_BAJA;
int8_t pisoActual = 0;
int8_t pisoSolicitado = 0;
delay_t delayEntrePisos;
delay_t delayTimeOutParado;

void ascensorInicializarMEF() {

    reconfigurarDelayEntrePisos();
    reconfigurarDelayTimeOutParado();
}

void ascensorActualizarMEF(){
   
    switch(estadoActual) {
    
        case EN_PLANTA_BAJA:
        
            enPlantaBaja();
            break;
            
        case MODO_CONFIGURACION:
        
            modoConfiguracion();
            break;
            
        case BAJANDO:
        
            bajando();
            break;

        case SUBIENDO:
        
            subiendo();
            break;
            
        case PARADO:
        
            parado();
            break;
            
        case YENDO_A_PLANTA_BAJA:
        
            yendoAPlantaBaja();
            break;
        
        default:
        
            ascensorInicializarMEF();
            break;
    }
}

void enPlantaBaja() {

    ledsSinMovimiento();

    //TODO abrir puertas, lo ejecuto siempre.. total si estan abiertas las puertas, se van a mantener en ese estado

    if(false) { //TODO require configuracion?
        
        estadoActual = MODO_CONFIGURACION;
    
    } else {
    
        chequearSolicitudDePiso();
    }
}

void modoConfiguracion() {

    ledsConfigurando();

    //TODO recibe configuracion
    
    estadoActual = EN_PLANTA_BAJA;    
}

void bajando() {

    ledsEnMovimiento();

    gpioWrite( LEDG, OFF );

    if(pisoActual > pisoSolicitado) {
    
        if (delayRead(&delayEntrePisos)) {
        
            pisoActual--;
        }
        
    } else {
    
        estadoActual = PARADO;
    }
}

void subiendo() {

    ledsEnMovimiento();
    
    if(pisoActual < pisoSolicitado) {
    
        if (delayRead(&delayEntrePisos)) {
        
            pisoActual++;
        }
        
    } else {
    
        estadoActual = PARADO;
    }
}

void parado() {

    ledsSinMovimiento();

    //TODO abrir puertas, lo ejecuto siempre.. total si estan abiertas las puertas, se van a mantener en ese estado

    if(!chequearSolicitudDePiso()) {
    
        if (delayRead(&delayTimeOutParado)) {
        
            estadoActual = YENDO_A_PLANTA_BAJA;
        }
    
    } else {
    
        reconfigurarDelayTimeOutParado();
    }

}

void yendoAPlantaBaja() {
    
    ledsEnMovimiento();
    
}

void reconfigurarDelayEntrePisos() {

    delayConfig(&delayEntrePisos, 1000);
}

void reconfigurarDelayTimeOutParado() {

    delayConfig(&delayTimeOutParado, 60000);
}

bool_t chequearSolicitudDePiso() {
    
    pisoSolicitado = 0;//TODO pedir nuevo piso
    
    bool_t nuevaSolicitudDePiso = FALSE;
    
    if(pisoSolicitado != pisoActual) {
    
        if(pisoSolicitado > pisoActual) {
        
            estadoActual = SUBIENDO;            

        } else {
        
            estadoActual = BAJANDO;
        }
        
        //TODO cerrar puertas
        
        nuevaSolicitudDePiso = TRUE;
    }
    
    return nuevaSolicitudDePiso;
}

void ledsEnMovimiento() {

    gpioWrite(LEDB, ON);
    gpioWrite(LED3, OFF);
}

void ledsSinMovimiento() {

    gpioWrite(LEDB, OFF);
    gpioWrite(LED3, ON);
}

void ledsConfigurando() {

    gpioWrite(LEDB, ON);
    gpioWrite(LED3, ON);
}
#include "mefAscensor.h"

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
        
        actualizarEstadoActual(MODO_CONFIGURACION);
    
    } else {
    
        chequearSolicitudDePiso();
    }
}

void modoConfiguracion() {

    ledsConfigurando();

    //TODO recibe configuracion
    
    actualizarEstadoActual(EN_PLANTA_BAJA);    
}

void bajando() {

    ledsEnMovimiento();

    if(pisoActual > pisoSolicitado) {
    
        if (delayRead(&delayEntrePisos)) {
        
            actualizarPisoActual(-1);
        }
        
    } else {
    
        actualizarEstadoActual(PARADO);
    }
}

void subiendo() {

    ledsEnMovimiento();
    
    if(pisoActual < pisoSolicitado) {
    
        if (delayRead(&delayEntrePisos)) {
        
            actualizarPisoActual(1);
        }
        
    } else {
    
        actualizarEstadoActual(PARADO);
    }
}

void parado() {

    ledsSinMovimiento();

    //TODO abrir puertas, lo ejecuto siempre.. total si estan abiertas las puertas, se van a mantener en ese estado

    if (!chequearSolicitudDePiso()) {
    
        if (delayRead(&delayTimeOutParado)) {
        
            actualizarEstadoActual(YENDO_A_PLANTA_BAJA);
        }
    
    } else {
    
        reconfigurarDelayTimeOutParado();
    }

}

void yendoAPlantaBaja() {
    
    ledsEnMovimiento();
    
    if (!chequearSolicitudDePiso()) {
    
        if (pisoActual == 0) {
        
            actualizarEstadoActual(EN_PLANTA_BAJA);
        
        } else if (delayRead(&delayEntrePisos)) {
                
            actualizarPisoActual(pisoActual > 0 ? -1 : 1);      
        }

    
    } else {
    
        reconfigurarDelayEntrePisos();
    }
}

void actualizarPisoActual(int8_t cantPisos) {

    pisoActual += cantPisos;

    uartWriteString(UART_USB, "\nPiso " + pisoActual);
}

void actualizarEstadoActual(estadoAscensor nuevoEstado) {

    estadoActual = nuevoEstado;
    
    uartWriteString(UART_USB, "\nEstado " + estadoActual);
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
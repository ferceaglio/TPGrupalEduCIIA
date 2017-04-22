#include "mefAscensor.h"
#include "sapi.h"

typedef enum {

    EN_PLANTA_BAJA,
    MODO_CONFIGURACION,
    BAJANDO,
    SUBIENDO,
    PARADO,
    YENDO_A_PLANTA_BAJA
    
    } estadoAscensor;

estadoAscensor estadoActual;

void ascensorInicializarMEF(){
   estadoActual = EN_PLANTA_BAJA;
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

    //TODO abrir puertas, lo ejecuto siempre.. total si estan abiertas las puertas, se van a mantener en ese estado

    if(false) { //TODO require configuracion?
        
        estadoActual = MODO_CONFIGURACION;
    
    } else {
    
        if(false) { //TODO existe peticion pendiente de subir??

            estadoActual = SUBIENDO;
            
            //TODO cerrar puertas

        } else if(false) { //TODO existe peticion pendiente de bajar??
    
            estadoActual = BAJANDO;
            
            //TODO cerrar puertas            
        }
    }
}

void modoConfiguracion() {

    //TODO recibe configuracion
    
    estadoActual = EN_PLANTA_BAJA;    
}

void bajando() {

}

void subiendo() {

}

void parado() {

}

void yendoAPlantaBaja() {

}
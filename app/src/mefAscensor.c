#include "mefAscensor.h"
#include "configuracion.h"

#define PLANTA_BAJA                 0
#define PISO_ACTUAL_INICIAL         PLANTA_BAJA
#define PISO_SOLICITADO_INICIAL     PLANTA_BAJA
#define ESTADO_INICIAL              EN_PLANTA_BAJA
#define SUBIR_UN_PISO               1
#define BAJAR_UN_PISO               -1
#define SALTO_DE_LINEA              "\r\n"
#define CHAR_CERO                   '0'
#define MILLIS_TIME_OUT_PARADO      60000

#define TAMANIO_NOMBRE_ESTADO       25
#define NOMBRE_EN_PLANTA_BAJA       "EN_PLANTA_BAJA"
#define NOMBRE_MODO_CONFIGURACION   "MODO_CONFIGURACION"
#define NOMBRE_BAJANDO              "BAJANDO"
#define NOMBRE_SUBIENDO             "SUBIENDO"
#define NOMBRE_PARADO               "PARADO"
#define NOMBRE_YENDO_A_PLANTA_BAJA  "YENDO_A_PLANTA_BAJA"

#define TITULO_PISO                 "Piso: "
#define TITULO_ESTADO               "Estado: "

#define ENTRAR_A_CONFIGURACION      9

estadoAscensor estadoActual;
int8_t pisoActual = PISO_ACTUAL_INICIAL;
int8_t pisoSolicitado = PISO_SOLICITADO_INICIAL;
delay_t delayEntrePisos;
delay_t delayTimeOutParado;

void ascensorInicializarMEF() {

    actualizarEstadoActual(ESTADO_INICIAL);
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

    chequearSolicitudDePiso();
}

void modoConfiguracion() {

    ledsConfigurando();

    if(!configurando()) {
    
        reconfigurarDelayEntrePisos();
    
        actualizarEstadoActual(EN_PLANTA_BAJA);
    }    
}

void bajando() {

    ledsEnMovimiento();

    if(pisoActual > pisoSolicitado) {
    
        if (delayRead(&delayEntrePisos)) {
        
            actualizarPisoActual(BAJAR_UN_PISO);
        }
        
    } else {
    
        frenar();
    }
}

void subiendo() {

    ledsEnMovimiento();
    
    if(pisoActual < pisoSolicitado) {
    
        if (delayRead(&delayEntrePisos)) {
        
            actualizarPisoActual(SUBIR_UN_PISO);
        }
        
    } else {
    
        frenar();
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
    
        if (pisoActual == PLANTA_BAJA) {
        
            actualizarEstadoActual(EN_PLANTA_BAJA);
        
        } else if (delayRead(&delayEntrePisos)) {
                
            actualizarPisoActual(pisoActual > PLANTA_BAJA ? BAJAR_UN_PISO : SUBIR_UN_PISO);      
        }

    
    } else {
    
        reconfigurarDelayEntrePisos();
    }
}

void frenar() {
    
    if(pisoActual == PLANTA_BAJA) {
        
       actualizarEstadoActual(EN_PLANTA_BAJA);        

    } else {
        
            actualizarEstadoActual(PARADO);
    }
}

void actualizarPisoActual(int8_t cantPisos) {

    pisoActual += cantPisos;

    uartWriteString(UART_USB, SALTO_DE_LINEA);
    uartWriteString(UART_USB, TITULO_PISO);
    uartWriteByte(UART_USB, pisoActual + CHAR_CERO);
}

void actualizarEstadoActual(estadoAscensor nuevoEstado) {

    estadoActual = nuevoEstado;
    
    char nombreEstado[TAMANIO_NOMBRE_ESTADO];
    uartWriteString(UART_USB, SALTO_DE_LINEA);
    uartWriteString(UART_USB, TITULO_ESTADO);

    switch(estadoActual) {
    
        case EN_PLANTA_BAJA:
        
            uartWriteString(UART_USB, NOMBRE_EN_PLANTA_BAJA);
            break;
            
        case MODO_CONFIGURACION:
        
            uartWriteString(UART_USB, NOMBRE_MODO_CONFIGURACION);
            configurar();
            break;
            
        case BAJANDO:
        
            uartWriteString(UART_USB, NOMBRE_BAJANDO);
            break;

        case SUBIENDO:
        
            uartWriteString(UART_USB, NOMBRE_SUBIENDO);
            break;
            
        case PARADO:
        
            uartWriteString(UART_USB, NOMBRE_PARADO);
            break;
            
        case YENDO_A_PLANTA_BAJA:
        
            uartWriteString(UART_USB, NOMBRE_YENDO_A_PLANTA_BAJA);
            break;
    }
}

void reconfigurarDelayEntrePisos() {

    delayConfig(&delayEntrePisos, obtenerVelocidadEntrePisos());
}

void reconfigurarDelayTimeOutParado() {

    delayConfig(&delayTimeOutParado, MILLIS_TIME_OUT_PARADO);
}

bool_t chequearSolicitudDePiso() {

    bool_t pisoRecibido = recibirPiso();
    
    if(pisoRecibido) {
    
        if(pisoSolicitado == ENTRAR_A_CONFIGURACION && estadoActual == EN_PLANTA_BAJA) {
        
            actualizarEstadoActual(MODO_CONFIGURACION);

        } else if(pisoSolicitado > pisoActual) {
        
            actualizarEstadoActual(SUBIENDO);            

        } else {
        
            actualizarEstadoActual(BAJANDO);
        }
        
        //TODO cerrar puertas
    }
    
    return pisoRecibido;
}

bool_t recibirPiso() {
    
    //TODO TEMPORAL HASTA QUE TENGAMOS EL TECLADO MATRICIAL

    uint8_t pisoSolicitadoTemp;
    
    bool_t pisoIngresado = FALSE;
    
    if(uartReadByte(UART_USB, &pisoSolicitadoTemp)) {
    
        pisoIngresado = TRUE;
    
        pisoSolicitado = pisoSolicitadoTemp - CHAR_CERO;
    
        uartWriteByte(UART_USB, pisoSolicitado + CHAR_CERO);
    }
    
    //TEMPORAL HASTA QUE TENGAMOS EL TECLADO MATRICIAL
    
    return pisoIngresado && pisoSolicitado != pisoActual;
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
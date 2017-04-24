#include "mefModoConfiguracion.h"
#include "sapi.h"

#define SALTO_DE_LINEA   "\r\n"

#define MENU_LINEA_1     "-------------------- MENU DE CONFIGURACION --------------------"
#define MENU_LINEA_2     "1 - Configurar velocidad entre piso y piso."
#define MENU_LINEA_3     "2 - Configurar velocidad de apertura o cerrado de puerta."
#define MENU_LINEA_4     "3 - Configurar cantidad de pisos (1 a 20)."
#define MENU_LINEA_5     "4 - Configurar cantidad de subsuelos (0 a 5)."
#define MENU_LINEA_6     "5 - Salir del modo configuración."
#define MENU_LINEA_7     "----------------------------------------------------------------"

#define TITULO_ESPERANDO_COMANDO                     "Ingrese la opcion deseada: "
#define TITULO_VALOR_INGRESADO_INCORRECTO            "Valor ingresado incorrecto"
#define TITULO_CONFIGURANDO_VELOCIDAD_ENTRE_PISOS    "Ingrese cantidad de segundos entre piso y piso: "
#define TITULO_CONFIGURANDO_VELOCIDAD_PUERTAS        "Ingrese cantidad de segundos en abrir o cerrar puerta: "
#define TITULO_CONFIGURANDO_CANTIDAD_PISOS           "Ingrese cantidad de pisos (1 a 20): "
#define TITULO_CONFIGURANDO_CANTIDAD_SUBSUELOS       "Ingrese cantidad de subsuelos (0 a 5): "
#define TITULO_FUERA_DE_CONFIGURACION                "FIN DE CONFIGURACION"

#define CHAR_CERO               '0'
#define SIN_VALOR_INGRESADO     -1
#define CANTIDAD_ITEMS_MENU     5


estadoModoConfiguracion estadoActualMefModoConfiguracion;
uint8_t valorIngresado;

void configurar() {

    uartWriteString(UART_USB, SALTO_DE_LINEA);
    uartWriteString(UART_USB, MENU_LINEA_1);
    uartWriteString(UART_USB, SALTO_DE_LINEA);
    uartWriteString(UART_USB, MENU_LINEA_2);
    uartWriteString(UART_USB, SALTO_DE_LINEA);
    uartWriteString(UART_USB, MENU_LINEA_3);
    uartWriteString(UART_USB, SALTO_DE_LINEA);
    uartWriteString(UART_USB, MENU_LINEA_4);
    uartWriteString(UART_USB, SALTO_DE_LINEA);
    uartWriteString(UART_USB, MENU_LINEA_5);
    uartWriteString(UART_USB, SALTO_DE_LINEA);
    uartWriteString(UART_USB, MENU_LINEA_6);
    uartWriteString(UART_USB, SALTO_DE_LINEA);
    uartWriteString(UART_USB, MENU_LINEA_7);

    actualizarEstadoActualMefModoConfiguracion(ESPERANDO_COMANDO);
}

bool_t configurando() {

    bool_t configurando = TRUE;
   
    switch(estadoActualMefModoConfiguracion) {
    
        case ESPERANDO_COMANDO:
        
            esperandoComando();
            break;
            
        case CONFIGURANDO_VELOCIDAD_ENTRE_PISOS:
        
            configurandoVelocidadEntrePisos();
            break;
            
        case CONFIGURANDO_VELOCIDAD_PUERTAS:
        
            configurandoVelocidadPuertas();
            break;

        case CONFIGURANDO_CANTIDAD_PISOS:
        
            configurandoCantidadPisos();
            break;
            
        case CONFIGURANDO_CANTIDAD_SUBSUELOS:
        
            configurandoCantidadSubsuelos();
            break;
            
        case FUERA_DE_CONFIGURACION:
        
            configurando = FALSE;
            break;
    }
    
    return configurando;
}

bool_t recibirValorIngresado() {

    bool_t ingresoValor = FALSE;
        
    if(uartReadByte(UART_USB, &valorIngresado)) {
        
        valorIngresado -= CHAR_CERO;
    
        uartWriteByte(UART_USB, valorIngresado + CHAR_CERO);
        
        ingresoValor = TRUE;
    }
    
    return ingresoValor;
}

void esperandoComando() {

    if(recibirValorIngresado()) {
    
        if(valorIngresado <= CANTIDAD_ITEMS_MENU) {
        
            actualizarEstadoActualMefModoConfiguracion(valorIngresado);
        
        } else {
        
            uartWriteString(UART_USB, SALTO_DE_LINEA);
            uartWriteString(UART_USB, TITULO_VALOR_INGRESADO_INCORRECTO);
            uartWriteString(UART_USB, SALTO_DE_LINEA);
            uartWriteString(UART_USB, TITULO_ESPERANDO_COMANDO);  
        }
    }    
}

void configurandoVelocidadEntrePisos() {

    if(recibirValorIngresado()) {
    
        configurarVelocidadEntrePisos(valorIngresado * 1000);
        
        actualizarEstadoActualMefModoConfiguracion(FUERA_DE_CONFIGURACION);
    }
}

void configurandoVelocidadPuertas() {

    if(recibirValorIngresado()) {
    
        configurarVelocidadPuertas(valorIngresado * 1000);
        
        actualizarEstadoActualMefModoConfiguracion(FUERA_DE_CONFIGURACION);
    }
}

void configurandoCantidadPisos() {

    if(recibirValorIngresado()) {
    
        if(!configurarCantidadPisos(valorIngresado)) {
        
            uartWriteString(UART_USB, SALTO_DE_LINEA);
            uartWriteString(UART_USB, TITULO_VALOR_INGRESADO_INCORRECTO);
        }
        
        actualizarEstadoActualMefModoConfiguracion(FUERA_DE_CONFIGURACION);
    }
}

void configurandoCantidadSubsuelos() {

    if(recibirValorIngresado()) {
    
        if(!configurarCantidadSubsuelos(valorIngresado)) {
        
            uartWriteString(UART_USB, SALTO_DE_LINEA);
            uartWriteString(UART_USB, TITULO_VALOR_INGRESADO_INCORRECTO);
        }
        
        actualizarEstadoActualMefModoConfiguracion(FUERA_DE_CONFIGURACION);
    }
}

void actualizarEstadoActualMefModoConfiguracion(estadoModoConfiguracion nuevoEstado) {
    
    estadoActualMefModoConfiguracion = nuevoEstado;
    
    switch(estadoActualMefModoConfiguracion) {
    
        case ESPERANDO_COMANDO:
        
            uartWriteString(UART_USB, SALTO_DE_LINEA);
            uartWriteString(UART_USB, TITULO_ESPERANDO_COMANDO);
            break;
            
        case CONFIGURANDO_VELOCIDAD_ENTRE_PISOS:
        
            uartWriteString(UART_USB, SALTO_DE_LINEA);
            uartWriteString(UART_USB, TITULO_CONFIGURANDO_VELOCIDAD_ENTRE_PISOS);
            break;
            
        case CONFIGURANDO_VELOCIDAD_PUERTAS:
        
            uartWriteString(UART_USB, SALTO_DE_LINEA);
            uartWriteString(UART_USB, TITULO_CONFIGURANDO_VELOCIDAD_PUERTAS);
            break;

        case CONFIGURANDO_CANTIDAD_PISOS:
        
            uartWriteString(UART_USB, SALTO_DE_LINEA);
            uartWriteString(UART_USB, TITULO_CONFIGURANDO_CANTIDAD_PISOS);
            break;
            
        case CONFIGURANDO_CANTIDAD_SUBSUELOS:
        
            uartWriteString(UART_USB, SALTO_DE_LINEA);
            uartWriteString(UART_USB, TITULO_CONFIGURANDO_CANTIDAD_SUBSUELOS);
            break;
            
        case FUERA_DE_CONFIGURACION:
        
            uartWriteString(UART_USB, SALTO_DE_LINEA);
            uartWriteString(UART_USB, TITULO_FUERA_DE_CONFIGURACION);
            break;
    }
}
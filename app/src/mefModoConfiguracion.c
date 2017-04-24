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

#define TITULO_ESPERANDO_COMANDO                     "Seleccione la opcion deseada: "
#define TITULO_CONFIGURANDO_VELOCIDAD_ENTRE_PISOS    ""
#define TITULO_CONFIGURANDO_VELOCIDAD_PUERTAS        ""
#define TITULO_CONFIGURANDO_CANTIDAD_PISOS           ""
#define TITULO_CONFIGURANDO_CANTIDAD_SUBSUELOS       ""
#define TITULO_FUERA_DE_CONFIGURACION                "FIN DE CONFIGURACION"

estadoModoConfiguracion estadoActual;

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

    actualizarEstado(ESPERANDO_COMANDO);
}

bool_t configurando(){

    bool_t configurando = TRUE;
   
    switch(estadoActual) {
    
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
}

void esperandoComando() {

    
}

void configurandoVelocidadEntrePisos() {

    
}

void configurandoVelocidadPuertas() {

    
}

void configurandoCantidadPisos() {

    
}

void configurandoCantidadSubsuelos() {

    
}

void actualizarEstado(estadoModoConfiguracion nuevoEstado) {
    
    estadoActual = nuevoEstado;
    
    switch(estadoActual) {
    
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
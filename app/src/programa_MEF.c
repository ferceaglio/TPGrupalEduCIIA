/*============================================================================
 * Licencia: 
 * Autor: 
 * Fecha: 
 *===========================================================================*/

/*==================[inlcusiones]============================================*/

#include "programa.h"   // <= su propio archivo de cabecera
#include "mefIngresoPiso.h"
#include "mefAscensor.h"
#include "driverDisplays7Segmentos.h"
#include "driverTecladoMatricial.h"
#include "mefModoConfiguracion.h"
#include "mefPuertas.h" 
#include "sapi.h"       // <= Biblioteca sAPI

/*==================[definiciones y macros]==================================*/
typedef enum {EN_PLANTA_BAJA,MODO_CONFIGURACION,BAJANDO,SUBIENDO,PARADO,YENDO_A_PLANTA_BAJA,ABRIENDO_PUERTA,CERRANDO_PUERTAS} estadoMef;

/*==================[definiciones de datos internos]=========================*/

/*==================[definiciones de datos externos]=========================*/
estadoMef estadoActual;

uint8_t tiempoTranscurrido = 0;
/*==================[declaraciones de funciones internas]====================*/

/*==================[declaraciones de funciones externas]====================*/
void ascensorInicializarMEF(void){
  estadoActual = EN_PLANTA_BAJA;
}

void aperturaPuertas(void){
  estadoActual = ABRIENDO_PUERTA;
  ascensorActualizarMEF();
}
  
void cierrePuertas(void){
  estadoActual = CERRANDO_PUERTAS;
  ascensorActualizarMEF();
}

void ingresoDatos(){
  estadoActual = EN_ESPERA_DE_DIGITOS_1;
  ingresoPisosActualizaMEF();
}

void ascensorActualizarMEF(void){
	switch(estadoActual){
		case EN_PLANTA_BAJA:
			aperturaPuertas();
			cierrePuertas();
			ingresoDatos();
			
			
			}
		break;
		case MODO_CONFIGURACION:
			
			
			}
		break;
		case BAJANDO:
			
			
			}
		break;
		case SUBIENDO:
			
			
			}
		break;	
		case PARADO:
			
			
			}
		break;
		case YENDO_A_PLANTA_BAJA:
			
			
			}
		break;
		default:
                		ascensorInicializarMEF();
		break;
	}				
}
/*==================[funcion principal]======================================*/

// FUNCION PRINCIPAL, PUNTO DE ENTRADA AL PROGRAMA LUEGO DE ENCENDIDO O RESET.
int main( void ){

   // ---------- CONFIGURACIONES ------------------------------
   boardConfig();   // Inicializar y configurar la plataforma
   
   ascensorInicializarMEF();   // Inicializar la MEF de ascensor
   
   // ---------- REPETIR POR SIEMPRE --------------------------
   while( TRUE )
   {      
      ascensorActualizarMEF();   // Actualizar la MEF de ascensor
   } 

   // NO DEBE LLEGAR NUNCA AQUI, debido a que a este programa se ejecuta 
   // directamenteno sobre un microcontroladore y no es llamado/ por ningun
   // Sistema Operativo, como en el caso de un programa para PC.
   return 0;
}

/*==================[definiciones de funciones internas]=====================*/

/*==================[definiciones de funciones externas]=====================*/

/*==================[fin del archivo]========================================*/

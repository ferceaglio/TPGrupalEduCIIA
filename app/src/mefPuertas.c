#include "mefPuertas.h"
#include "sapi.h"
//int main( void )
//{
//boardConfig();
//uartConfig(UART_USB, 115200);
//   int estado_puertas=1;//se abren
//    int a=1;
//        gpioWrite(LED3,estado_puertas);
//    uartWriteString(UART_USB, "Puerta abierta\n");
//    while (a==1)
//    {
//        /* int estado_puertas=1;//se abren
//         gpioWrite(LED3,estado_puertas);
//    uartWriteString(UART_USB, "Puerta abierta\n");
//    */delay(2000);
//       if(gpioRead(TEC1))
//        {
//            uartWriteString(UART_USB, "Puerta obstruida\n");
//            delay(2000);
//            while(gpioRead(TEC1))
//            {
//                uartWriteString(UART_USB, "Puerta obstruida\n");
//                uartWriteString(UART_USB, "Alarma de puerta obstruida\n");
//                gpioWrite(LEDB, ON);
//                delay(1000);
//                gpioWrite(LEDB,OFF);
//                delay(1000);
//            }
//        }    
//                estado_puertas=0;  //cierro puerta
//                gpioWrite(LED3,estado_puertas);
//                uartWriteString(UART_USB, "Puerta cerrada\n");
//            
//            
//        a=1;    
//    }
//
//
//}

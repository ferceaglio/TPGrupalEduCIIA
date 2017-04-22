#include "program.h"
#include "sapi.h"

int main(void){

   boardConfig();   
   
   ascensorInicializarMEF();
   
   while(TRUE){
   
      ascensorActualizarMEF();
   } 

   // IT SHOULD NEVER COME HERE, because this program runs directly on a
   // microcontroller and is not called by any Operating System, as in
   // case of a PC program.
   return 0;
}
#include <lpc17xx.h>

/*PONEMOS TODOS LOS PINES A 0*/
void limpiarPuertos(){
  LPC_GPIO0->FIOCLR = 0xffffffff;
  LPC_GPIO1->FIOCLR = 0xffffffff;
  LPC_GPIO2->FIOCLR = 0xffffe7ff;
  LPC_GPIO3->FIOCLR = 0xffffffff;
  LPC_GPIO4->FIOCLR = 0xffffffff;
}

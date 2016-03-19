#include <lpc17xx.h>
#include "awesomeHeaderFile.h"


/*MUESTRA EL NÚMERO BCD A TRAVÉS DE LOS LEDS*/
void setNumeroBCD(int n){
  int estado = 0;
  //Convierto el número a BCD
  n = getBinToBCD(n);

  //Muestro n (ya en formato BCD en los LEDs)
  estado = ((n&0x010000000)>>28);
  LPC_GPIO1->FIOPIN |= (estado<<0);
  estado = ((n&0x020000000)>>29);
  LPC_GPIO1->FIOPIN |= (estado<<1);
  estado = ((n&0x040000000)>>30);
  LPC_GPIO1->FIOPIN |= (estado<<4);
  estado = ((n&0x080000000)>>31);
  LPC_GPIO1->FIOPIN |= (estado<<8);
  estado = ((n&0x01000000)>>24);
  LPC_GPIO1->FIOPIN |= (estado<<9);
  estado = ((n&0x02000000)>>25);
  LPC_GPIO1->FIOPIN |= (estado<<10);
  estado = ((n&0x04000000)>>26);
  LPC_GPIO1->FIOPIN |= (estado<<14);
  estado = ((n&0x08000000)>>27);
  LPC_GPIO0->FIOPIN |= (estado<<2);
  estado = ((n&0x0100000)>>20);
  LPC_GPIO1->FIOPIN |= (estado<<16);
  estado = ((n&0x0200000)>>21);
  LPC_GPIO1->FIOPIN |= (estado<<17);
  estado = ((n&0x0400000)>>22);
  LPC_GPIO4->FIOPIN |= (estado<<29);
  estado = ((n&0x0800000)>>23);
  LPC_GPIO4->FIOPIN |= (estado<<28);
  estado = ((n&0x010000)>>16);
  LPC_GPIO2->FIOPIN |= (estado<<6);
  estado = ((n&0x020000)>>17);
  LPC_GPIO2->FIOPIN |= (estado<<7);
  estado = ((n&0x040000)>>18);
  LPC_GPIO2->FIOPIN |= (estado<<8);
  estado = ((n&0x080000)>>19);
  LPC_GPIO0->FIOPIN |= (estado<<19);
  estado = ((n&0x01000)>>12);
  LPC_GPIO0->FIOPIN |= (estado<<20);
  estado = ((n&0x02000)>>13);
  LPC_GPIO0->FIOPIN |= (estado<<21);
  estado = ((n&0x04000)>>14);
  LPC_GPIO0->FIOPIN |= (estado<<22);
}

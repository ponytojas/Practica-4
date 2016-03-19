#include <lpc17xx.h>

/*MOSTRAR VALORES BINARIOS*/
void setNumeroBinario(int n){
  int estado;
  estado = n&0x01;
  LPC_GPIO1->FIOPIN |= (estado<<0);
  estado = ((n&0x02)>>1);
  LPC_GPIO1->FIOPIN |= (estado<<1);
  estado = ((n&0x04)>>2);
  LPC_GPIO1->FIOPIN |= (estado<<4);
  estado = ((n&0x08)>>3);
  LPC_GPIO1->FIOPIN |= (estado<<8);
  estado = ((n&0x010)>>4);
  LPC_GPIO1->FIOPIN |= (estado<<9);
  estado = ((n&0x020)>>5);
  LPC_GPIO1->FIOPIN |= (estado<<10);
  estado = ((n&0x040)>>6);
  LPC_GPIO1->FIOPIN |= (estado<<14);
  estado = ((n&0x080)>>7);
  LPC_GPIO0->FIOPIN |= (estado<<2);
  estado = ((n&0x0100)>>8);
  LPC_GPIO1->FIOPIN |= (estado<<16);
  estado = ((n&0x0200)>>9);
  LPC_GPIO1->FIOPIN |= (estado<<17);
  estado = ((n&0x0400)>>10);
  LPC_GPIO4->FIOPIN |= (estado<<29);
  estado = ((n&0x0800)>>11);
  LPC_GPIO4->FIOPIN |= (estado<<28);
  estado = ((n&0x01000)>>12);
  LPC_GPIO2->FIOPIN |= (estado<<6);
  estado = ((n&0x02000)>>13);
  LPC_GPIO2->FIOPIN |= (estado<<7);
  estado = ((n&0x04000)>>14);
  LPC_GPIO2->FIOPIN |= (estado<<8);
  estado = ((n&0x08000)>>15);
  LPC_GPIO0->FIOPIN |= (estado<<19);
}

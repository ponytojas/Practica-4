#include <lpc17xx.h>

void configurarPuertos(void){
  //Todos los puertos en modo GPIO
  LPC_PINCON->PINSEL0 = 0x00000000;
  LPC_PINCON->PINSEL1 = 0x00000000;
  LPC_PINCON->PINSEL2 = 0x00000000;
  LPC_PINCON->PINSEL3 = 0x00000000;
  LPC_PINCON->PINSEL4 = 0x00000000;

  //Pines de ENTRADA y SALIDA
  LPC_GPIO0->FIODIR |= 0xf87fffff;
  LPC_GPIO1->FIODIR |= 0x6007ffff;
  LPC_GPIO2->FIODIR |= 0xffffe7ff;
  LPC_GPIO3->FIODIR |= 0xfbffffff;
  LPC_GPIO4->FIODIR |= 0xffffffff;
	
	//Configuración de la interrupción externa EINT0 del botoncico
	NVIC_EnableIRQ(EINT3_IRQn);
	LPC_GPIOINT->IO2IntEnF |= (1 << 10);
	LPC_GPIOINT->IO2IntEnF |= (1 << 11);
	LPC_GPIOINT->IO2IntEnR |= (1 << 12);
	LPC_GPIOINT->IO2IntEnF |= (1 << 12);
}

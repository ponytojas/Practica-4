#include <lpc17xx.h>

/*OBTENCIÓN DEL VALOR INICIAL*/
int getValorInicial(){
  //TODO Leer puertos para conseguir los valores y meterlos en HEX
  int valorInicial = 0;
  //El primer pin corresponde con 1
  valorInicial = !(((LPC_GPIO1->FIOPIN>>31) & 0x01));
  //El segundo con 2 y así sucesivamente en potencias de 2, por lo que iremos multiplicando por 2 sucesivamente
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO0->FIOPIN>>26) & 0x01));
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO0->FIOPIN>>25) & 0x01));
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO0->FIOPIN>>24) & 0x01));
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO0->FIOPIN>>23) & 0x01));
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO1->FIOPIN>>28) & 0x01));
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO1->FIOPIN>>27) & 0x01));
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO1->FIOPIN>>26) & 0x01));
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO1->FIOPIN>>25) & 0x01));
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO1->FIOPIN>>24) & 0x01));
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO1->FIOPIN>>23) & 0x01));
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO1->FIOPIN>>22) & 0x01));
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO1->FIOPIN>>21) & 0x01));
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO1->FIOPIN>>20) & 0x01));
  valorInicial = (valorInicial<<1) + !(((LPC_GPIO1->FIOPIN>>19) & 0x01));
  valorInicial = (valorInicial<<1) + !((LPC_GPIO3->FIOPIN>>26) & 0x01);

	if(!valorInicial)
		valorInicial = 1;
  //Devolvemos el valor inicial introducido
  return valorInicial;
}

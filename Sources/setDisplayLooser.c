#include <lpc17xx.h>

/*DELAY ENTRE LOS NÚMEROS DEL DISPLAY*/
void delay(uint32_t n){															//Introducimos direcctamente el valor de los ms de retraso
  int32_t i;
  n*=20000;
  for(i=0;i<n;i++);
}

/*MOSTRAMOS EL NÚMERO EN EL DISPLAY */
void setDisplayLooser(int n){
//Pues aquí va el muestreo del display de 7-seg//Es necesario ver los segmentos que se encienden para cada numero//
//Pines: a(P0.18) b(p0.17) c(p0.15) d(p0.16) e(p0.9) f(p0.8) g(p0.7)//
  LPC_GPIO0->FIOSET = 0x00078380;
	delay(50);
  //pos++;  Falta la parte donde se va dividiendo los números en partes que hice
  switch (n){
    case 0:
    //El 0//a + b + c + d + e + f
    LPC_GPIO0->FIOCLR = 0x00078300;
    break;

    case 1:
    //El 1//b + c//
    LPC_GPIO0->FIOCLR = 0x00028000;
    break;

    case 2:
    //El 2//a + b + d + e +g//
    LPC_GPIO0->FIOCLR = 0x00070280;
    break;

    case 3:
    //El 3 //a + b + c + d + g/
    LPC_GPIO0->FIOCLR = 0x00078080;
    break;

    case 4:
    //El 4//b + c + f + g//
    LPC_GPIO0->FIOCLR = 0x00028180;
    break;

    case 5:
    //El 5//a + c + d + f + g//
    LPC_GPIO0->FIOCLR = 0x00058180;
    break;

    case 6:
    //El 6//a + c + d + e + f + g
    LPC_GPIO0->FIOCLR = 0x00058380;
    break;

    case 7:
    //El 7//a + b + c//
    LPC_GPIO0->FIOCLR = 0x00068000;
    break;

    case 8:
    //El 8//a + b + c + d + e + f + g//
    LPC_GPIO0->FIOCLR = 0x00078380;
    break;

    case 9:
    //El 9//a + b + c + d + f + g//
    LPC_GPIO0->FIOCLR = 0x00078180;
    break;
  }
}

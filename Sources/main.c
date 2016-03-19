    //************************************//
   /* Práctica 3---EntradaSalida	 */
  /*  Francisco Jesús Gimenez Hidalgo   */
 /*   Daniel Villalobos del Baño       */
//************************************//

#include <lpc17xx.h>
#include "awesomeHeaderFile.h"

/*DECLARACIÓN DE LAS VARIABLES*/
int valorBCD;																				//Valor del número codificado en BCD
int valorBIN;																				//Valor del número codificado en BINARIO
int esPrimerNoCero = 0;

/*DEFINICIÓN DE LAS CONSTANTES*/
#define NUM_MAX 65535


/***********/
/*FUNCIONES*/
/***********/

/*FUNCIÓN QUE CONTROLA EL DELAY*/
void delay(uint32_t n){															//Introducimos direcctamente el valor de los ms de retraso
  int32_t i;
  n*=20000;
  for(i=0;i<n;i++);
}



/*FUNCIÓN PRINCIPAL*/
int main(){
  int i = 0, valor = 0, ledTonto, ledEncendido, pos = 0, numeroDisplay = 0;
  int32_t tiempoTranscurrido;
				int test = 0;

  //Llamadas a funciones de inicialización
  configurarPuertos();
  limpiarPuertos();

  while(1){

    valor = getValorInicial();															//Leo valor inicial y lo guardo
    for(i=valor;i<=NUM_MAX;i++){														//Incrementamos el número desde el valor inicial al máximo

      while(!getEsPrimo(i) && i<=NUM_MAX)
      i++;

      if(i>NUM_MAX)
      break;

      if((LPC_GPIO2->FIOPIN>>10 & 0x01)){									//Si pulsamos SW2 Binario, si no BCD
        setNumeroBinario(i);
      }
      else{
        setNumeroBCD(i);
      }

      ledEncendido = 0;
      ledTonto = i;

      for(tiempoTranscurrido=0;tiempoTranscurrido<6000000;tiempoTranscurrido++){
        if(tiempoTranscurrido%375000 == 0){
					test++;
					
          if(ledEncendido == 0){
            LPC_GPIO1->FIOPIN |= (1<<18);  //Encendemos LED
            ledEncendido = 1;
          }
          else{
            LPC_GPIO1->FIOPIN &= ~(1<<18);  //Apagamos LED
            ledEncendido = 0;
          }

          if(ledTonto & 0x01)
            LPC_GPIO1->FIOPIN |= (1<<29);  //Encendemos LED
          else
            LPC_GPIO1->FIOPIN &= ~(1<<29);  //Encendemos LED

          ledTonto>>=1;
        }
        if(tiempoTranscurrido%1200000 == 0){
					numeroDisplay = getBinToBCD(i);
					setDisplayLooser((numeroDisplay>>(pos+12)) & 0x0F);
					pos+=4;
        }
      }
			LPC_GPIO0->FIOSET = 0x00078380;
			delay(500);
			pos = 0;
      limpiarPuertos();
    }
    limpiarPuertos();
  }
}

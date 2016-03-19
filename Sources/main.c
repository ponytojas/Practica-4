    //************************************//
   /* Pr�ctica 3---EntradaSalida	 */
  /*  Francisco Jes�s Gimenez Hidalgo   */
 /*   Daniel Villalobos del Ba�o       */
//************************************//

#include <lpc17xx.h>
#include "awesomeHeaderFile.h"

/*DECLARACI�N DE LAS VARIABLES*/
int valorBCD;																				//Valor del n�mero codificado en BCD
int valorBIN;																				//Valor del n�mero codificado en BINARIO
int esPrimerNoCero = 0;

/*DEFINICI�N DE LAS CONSTANTES*/
#define NUM_MAX 65535


/***********/
/*FUNCIONES*/
/***********/

/*FUNCI�N QUE CONTROLA EL DELAY*/
void delay(uint32_t n){															//Introducimos direcctamente el valor de los ms de retraso
  int32_t i;
  n*=20000;
  for(i=0;i<n;i++);
}



/*FUNCI�N PRINCIPAL*/
int main(){
  int i = 0, valor = 0, ledTonto, ledEncendido, pos = 0, numeroDisplay = 0;
  int32_t tiempoTranscurrido;
				int test = 0;

  //Llamadas a funciones de inicializaci�n
  configurarPuertos();
  limpiarPuertos();

  while(1){

    valor = getValorInicial();															//Leo valor inicial y lo guardo
    for(i=valor;i<=NUM_MAX;i++){														//Incrementamos el n�mero desde el valor inicial al m�ximo

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

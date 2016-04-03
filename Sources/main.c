    //************************************//
   /* Práctica 3---EntradaSalida	 */
  /*  Francisco Jesús Jimenez Hidalgo   */
 /*   Daniel Villalobos del Baño       */
//************************************//

#include <lpc17xx.h>
#include "awesomeHeaderFile.h"

/*DECLARACIÓN DE LAS VARIABLES*/
int valorBCD;																				//Valor del número codificado en BCD
int valorBIN;																				//Valor del número codificado en BINARIO
int esPrimerNoCero = 0;
uint32_t contador25 = 0; 

/*DECLARACIÓN DE VARIABLES ESTÁTICAS GLOBALES*/
static int ejecutarLedTonto = 0;
static int ejecutarDisplay = 0;
static int finNumero = 0;

/*DEFINICIÓN DE LAS CONSTANTES*/
#define NUM_MAX 65535
#define TRUE 1
#define FALSE 0


/***********/
/*FUNCIONES*/
/***********/

/*FUNCIÓN QUE SE EJECUTA CADA VEZ QUE PASAN 25ms*/
void SysTick_Handler(void)  {	
  contador25++;																			//Incrementamos el contador de los 25ms
	
	if ((contador25-1)%5 == 0) { ejecutarLedTonto = TRUE;}	//En el caso de que hayan pasado 125ms ejecutarLedTonto se convierte en TRUE
	
	if ((contador25-1)%16 == 0) { ejecutarDisplay = TRUE;}	//En el caso de que hayan pasado 400ms se ejecutarDisplay se convierte en TRUE

	if ((contador25)%80 == 0) { finNumero = TRUE;}					//Cuando hayan pasado 2000ms hemos terminado de mostrar el número
}



/*FUNCIÓN PRINCIPAL*/
int main(){
  int i = 0, valor = 0, ledTonto, ledEncendido, pos = 0, numeroDisplay = 0;

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
			SysTick_Config(SystemCoreClock / 40);      // Systick generará una interrupción cada 25ms
			contador25 = 0;											 			 //Contador a 0

			/*En este bucle while, mostramos los números en el 
			display y los leds hasta que pasen los 2000ms
			*/
			while(finNumero != 1) {
				
				//Cuando ejecutarLedTonto == TRUE (1) ejecutamos este bloque que se encarga de los leds que parpadean
				if (ejecutarLedTonto) {
						ejecutarLedTonto = FALSE;					//Limpiamos la "flag" de ejecutar este bloque
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
            LPC_GPIO1->FIOPIN &= ~(1<<29);  //Apagamos LED

          ledTonto>>=1;
				}

				//Cuando ejecutar display sea == TRUE
				if (ejecutarDisplay) {
					ejecutarDisplay = FALSE;					//Limpiamos la "flag" de ejecutar este bloque
					numeroDisplay = getBinToBCD(i);
					setDisplayLooser((numeroDisplay>>(pos+12)) & 0x0F);
					pos+=4;
				} 
			}
			
			finNumero = FALSE;					//Limpiamos la "flag" de que hemos llegado a mostrar el número entero
			pos = 0;
			limpiarPuertos();
			LPC_GPIO0->FIOSET = 0x00078380;
    }
    limpiarPuertos();
  }
}

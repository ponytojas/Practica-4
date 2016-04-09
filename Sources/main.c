    //************************************//
   /* Práctica 4---Interrupciones     	 */
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

/*DEFINICIÓN DE LAS CONSTANTES*/
#define NUM_MAX 65535
#define TRUE 1
#define FALSE 0

/*DECLARACIÓN DE VARIABLES ESTÁTICAS GLOBALES*/
static int ejecutarLedTonto = 0;
static int ejecutarDisplay = 0;
static int finNumero = 0;
static int i = 0;
static int numMax = NUM_MAX;
static int numMin = 0;
static int enBinario = FALSE;
static int incrementar = TRUE;

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

void EINT3_IRQHandler (void)
{
	if (LPC_GPIOINT->IO2IntStatF & (1 << 10)) {
  //raising edge interrupt on pin 2.10 was fired
  LPC_GPIOINT->IO2IntClr |= (1 << 10); // clear the status
		limpiarPuertos();
  
			if(enBinario == FALSE){									//Si pulsamos KEY1 Binario, si no BCD
				enBinario = TRUE;
				setNumeroBinario(i);
      }
      else{
				enBinario = FALSE;
				setNumeroBCD(i);
      }
  return;
  }
	
	if (LPC_GPIOINT->IO2IntStatF & (1 << 11)) {
  //raising edge interrupt on pin 2.11 was fired
  LPC_GPIOINT->IO2IntClr |= (1 << 11); // clear the status
  
			if(incrementar == FALSE){									//Si pulsamos KEY1 Binario, si no BCD
				incrementar = TRUE;
      }
      else{
				incrementar = FALSE;
      }
  return;
  }
	if (LPC_GPIOINT->IO2IntStatR & (1 << 12)) {
  //raising edge interrupt on pin 2.12 was rising
  LPC_GPIOINT->IO2IntClr |= (1 << 12); // clear the status
  
		numMax= getValorInicial();
		
  return;
  }
	if (LPC_GPIOINT->IO2IntStatF & (1 << 12)) {
  //raising edge interrupt on pin 2.12 was fired
  LPC_GPIOINT->IO2IntClr |= (1 << 12); // clear the status
  
			numMin = getValorInicial();
		
  return;
  }
}

/*FUNCIÓN PRINCIPAL*/
int main(){
	int ledTonto, ledEncendido, pos = 0, numeroDisplay = 0;

  //Llamadas a funciones de inicialización
  configurarPuertos();
  limpiarPuertos();
	
  while(1){

    
			if (incrementar){
				i=numMin-1;
			} else {i=numMax;}		//Leo valor inicial y lo guardo
    while(i>=numMin-1 && i <= numMax && i <= NUM_MAX){
			if ( i <= 0)
			{
				i= 0;
			}
			
			if (incrementar){
				i++;
			} else {i--;}

      while(!getEsPrimo(i) && i<=numMax){
      if (incrementar){
				i++;
			} else {i--;}
			}

      if(i>numMax || i<=0)
      break;

      ledEncendido = 0;
      ledTonto = i;
			SysTick_Config(SystemCoreClock / 40);      // Systick generará una interrupción cada 25ms
			contador25 = 0;											 			 //Contador a 0
			
				if (enBinario == TRUE) {
					setNumeroBinario(i);
				} else {
					setNumeroBCD(i);
				}

			/*En este bucle while, mostramos los números en el display y los leds hasta que pasen los 2000ms*/
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

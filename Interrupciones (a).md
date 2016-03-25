#**Interrupciones**

##SysTick

El SysTick es un contador de 24-bit del sistema.

Básicamente le asignaremos un valor desde el que empezar a contar (RELOAD) hasta otro valor (LOAD) este segundo valor se suele considerar 0 para funcionar por completo como contador.

###Nomeclatura

Por un lado tendremos que tener la llamada a las instrucciones cuando el contador llegue al valor deseado (*SysTick_Handler*) y por otro lado los valores de LOAD, RELOAD y prioridad

Empezando por estos segundos:

*SysTick->LOAD  = XXXXXXX;*

Donde XXXXXX es un entero cualquiera, nos permite asignarle un valor de **RELOAD** al SysTick, es decir, el valor desde el que empezará a contar hacia abajo

*NVIC_SetPriotiry (-1, X);*

Con esto asignaremos el valor de prioridad que le daremos al SisTick, donde X es un entero (por ejemplo el 8  {creo que es el primer valor que podemos asignarle al SysTick pero no estoy seguro})

*SysTick->VAL = X; *

Asignamos el valor del contador, normalmente 0 para blablabla

*SysTick->CTRL =  0x00000007;*

Esto habilita la interrupción (IRQ) del SysTick, su Timer y el origen del reloj que utilizará  {Siendo completamente sincero no tengo ni puñetera idea de porque es ese valor, lo sigo investigando, pero con el 7 todo funciona chachi}




La llamada del Handler:

Antes del main, como si definiéramos una función, añadimos el SysTick_Handler.

Entiendo que el sistema lo interpreta como una función y podría ir en un archivo.c aparte pero aún tengo que comprobarlo.

Ejemplo tonto

void SysTick_Handler()
{
    
    Hacemos cosas mazo de chachis que se ejecutarán cada lo que hayamos indicado en el LOAD
    
    Por ejemplo si hemos hecho LOAD = 50.000, se ejecutará cada 0,5 milisegundos
}

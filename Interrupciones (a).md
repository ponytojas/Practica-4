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




#Actualización

He comprobado lo de llamar al SysTick_Handler desde otro archivo.c 

Resulta que las variables que se declaren o se usen en esas ordenes se "destruyen" al final del proceso.

Si utilizamos una variable a para alternar un pin, imaginemos si a=0 hacemos esto y si a=1 hacemos lo otro, y cambiamos el valor a al final de las instrucciones, cuando vuelva a terminar el contador, la variable a no existe y tiene que "volver a crearse" aunque hagamos un return a; 

Esto me deja confuso, porque en el intento que estoy haciendo declaro a de forma universal en el main.c justo después de incluir las bibliotecas. Así que las interrupciones deben declararse en el main si usan alguna variable, o bien, hay alguna manera de hacerlo y no se me ha ocurrido.


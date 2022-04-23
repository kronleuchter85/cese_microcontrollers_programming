============================================================================================================
Universidad de Buenos Aires - Especializacion en Sistemas Embebidos Materia
============================================================================================================
Programacion de Microcontroladores 
============================================================================================================
Alumno: Gonzalo Carreño
============================================================================================================



Contenido del repositorio
- poc_1
_ poc_2
_ poc_3
_ poc_4 (partes 1 y 2)


------------------------------------------------------------------------------------------------------------
poc_1: Practica 1
------------------------------------------------------------------------------------------------------------
- ejercicio 1
- ejercicio 2

------------------------------------------------------------------------------------------------------------
Poc_2: Practica 2 - Non-Blocking Delays Implementation
------------------------------------------------------------------------------------------------------------
- ejercicio 1: implementacion de retardos no bloqueantes implementacion de tres funciones: -delayInit -delayRead -delayWrite
- ejercicio 2: implementacion de retardos no bloqueantes para hacer titilar tres LEDs Se implementa de dos formas: Independiente (por default): es necesario descomentar la invocacion en el main 'approach_independent_blinking' Dependiente: es necesario descomentar la invocacion en el main 'approach_dependent_blinking' y comentar 'approach_independent_blinking'

------------------------------------------------------------------------------------------------------------
Poc_3: Practica 3 - Non-Blocking Delays (Modular Implementation)
------------------------------------------------------------------------------------------------------------
- ejercicio 1: delay.c y delay.h
- ejercicio 2: en main.c. Implementar un programa que utilice retardos no bloqueantes y haga titilar en forma periódica e independiente los tres leds de la placa NUCLEO-F429ZI de acuerdo a una secuencia predeterminada como en la práctica 1.Cada led debe permanecer encendido 200 ms.  No debe encenderse más de un led simultáneamente en ningún momento.

------------------------------------------------------------------------------------------------------------
poc_4_1: Practica 4 - parte 1 - Debouncing Implementation
------------------------------------------------------------------------------------------------------------
Implementa la logica de debouncing en un modulo independiente utilizando ademas el modulo de delay desarrollado en la practica 3. El comportamiento esperado es que cuando se presiona el boton de usuario se prende el led verde de la placa nucleo y cuando se libera se prende el azul. La implementacion de la logica a realizar esta dada por las funciones buttonPressed y buttonReleased que son implementaciones a nivel de usuario, siendo el modulo el encargado de la gestion de debouncing totalmente abstraido de la implementacion de estas funciones.
	
------------------------------------------------------------------------------------------------------------
poc_4_2: Practica 4 - parte 2 - Debouncing Implementation (Modular Implementation)
------------------------------------------------------------------------------------------------------------
Implementa la logica de cambiar la velocidad de titilado entre FAST (100 ms) y SLOW (500ms) cada vez q se presiona el boton de usuario.	Esto se logra por medio de la gestion de un evento usando el modulo de debounce implementado con una maquina de estados finitos. La modularizacion en si ya la habia implementado en la parte 1 de esta misma practica pero en esta parte le cambio el nombre al modulo como especifica el enunciado y le agrego la variable global privada con su correspondiente funcion publica.

------------------------------------------------------------------------------------------------------------
poc_5: Practica 5 - UART Communication
------------------------------------------------------------------------------------------------------------
Implementa la logica para utilizar la comunicacion serie por medio de la UART. El programa de ejemplo recibe comandos y envia mensajes por el puerto serie COM3. Para ejecutarlo seguir las instrucciones detalladas en el archivo Readme.txt dentro del directorio.


------------------------------------------------------------------------------------------------------------
poc_final_project: Proyecto final de PdM
------------------------------------------------------------------------------------------------------------
El objetivo de la aplicación es permitir realizar la configuración de un sistema embebido desde la computadora usando el puerto serie. La configuración permite cargar secuencias y velocidades leds, y también activar la configuración que debe ejecutarse. Luego, desde el sistema embebido se podrá poner en funcionamiento o pausar la ejecución de forma local haciendo uso del botón de usuario.

microcontrollers_programming

Universidad de Buenos Aires - Especializacion en Sistemas Embebidos Materia: Programacion de Microcontroladores Alumno: Gonzalo Carreño

Contenido del repositorio:

poc_1: Practica 1
    ejercicio 1
    ejercicio 2

poc_2: Practica 2
    ejercicio 1: implementacion de retardos no bloqueantes implementacion de tres funciones: -delayInit -delayRead -delayWrite
    ejercicio 2: 
		implementacion de retardos no bloqueantes para hacer titilar tres LEDs Se implementa de dos formas: Independiente (por default): es necesario descomentar la invocacion en el main 'approach_independent_blinking' Dependiente: es necesario descomentar la invocacion en el main 'approach_dependent_blinking' y comentar 'approach_independent_blinking'

poc_3: Practica 3
	ejercicio 1: delay.c y delay.h
	ejercicio 2: en main.c
		Implementar un programa que utilice retardos no bloqueantes y haga titilar en forma periódica e independiente los tres leds de la placa NUCLEO-F429ZI de acuerdo a una secuencia predeterminada como en la práctica 1.Cada led debe permanecer encendido 200 ms.  No debe encenderse más de un led simultáneamente en ningún momento.

poc_4_1: Practica 4 parte 1
	Esta es la parte 1 de la practica 4. Implementa la logica de debouncing en un modulo independiente utilizando ademas el modulo de delay desarrollado en la practica 3.
	El comportamiento esperado es que cuando se presiona el boton de usuario se prende el led verde de la placa nucleo y cuando se libera se prende el azul. La implementacion
	de la logica a realizar esta dada por las funciones buttonPressed y buttonReleased que son implementaciones a nivel de usuario, siendo el modulo el encargado de la gestion
	de debouncing totalmente abstraido de la implementacion de estas funciones.
	
poc_4_2: Practica 4 parte 2
	...
	
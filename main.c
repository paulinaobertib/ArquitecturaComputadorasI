#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EasyPIO.h"
#include <ncurses.h>

//funcion para inicializar EASY PIO
void pinSetup(void);

//funciones pedidas
void retardo(int);
void mostrar(unsigned char);

//funcion para controlar un conjunto de LEDs 
void ledShow(unsigned char);

//funciones de las consignas
void autoFantastico(int);
void choque(int);

//funciones hechas extras
void efectoPulso(int);
void cargandoBateria(int);

int main() {
	const char led[] = {14, 15, 18, 23, 24, 25, 8, 7}; //puertos de los leds
	
	int i
		pioInit();
	
	for (i = 0; i <= 7; i++)
	{
		pinMode(led[i], OUTPUT);
	}
	
	//en c se pone la cantidad que queremos + 1 porque el ultimo es un espacio vacio
	int attempts = 3; //para contar los intentos
	int password_length = 6; //longitud maxima de la password
	char password[] = "vipau"; //para almacenar passwords ingresadas
	char inputPassword[password_length]; //password ingresada por el usuario
	int menuOption; //aca guardamos la opcion elegida por el usuario del menu
	int delayInicial = 500;
	
	initscr(); //inicializa el modo de pantalla y establece el entorno necesario para utilizar las funciones y características de ncurses
	noecho(); //evita que los caracteres ingresados por el usuario se muestren en la pantalla
	
	while (attempts > 0) { //ciclo for para los intentos de la password
		printw("Ingrese su password de 5 digitos: "); 
		
		//getch para leer el caracter sin mostrarlo en pantalla
		for (i = 0; i < password_length; i++)
		{
			int c = getch();
			
			if (c != ERR)
			{
				if (c == '\n')
				{
					inputPassword[i] = '\0';
					break;
				}
				else
				{
					inputPassword[i] = c;
					printw("*");
					refresh();
				} 
			}
		}
		
		attempts --;
		
		if (strcmp(inputPassword, password) == 0) { //compara dos cadenas de caracteres y devuelve un valor igual a cero si las cadenas son iguales
			printw("Bienvenido al sistema\n");
			refresh();
			break;
		} else {
			printw("Password invalida, le quedan %d intentos.\n", attempts);
			refresh();
		}
	}
	
	if (attempts == 0) { //si llegamos a la cantidad maxima de intentos,no hay mas
		printw("No tienes mas intentos\n");
		refresh();
		endwin();
		exit(-1);
	}
	
	do {
		//\n es un salto de linea
		printw("---- MENU ----\n");
		printw("1. Auto Fantastico\n");
		printw("2. Choque\n");
		printw("3. Efecto pulso\n");
		printw("4. Cargando bateria\n");
		printw("5. Salir\n");
		printw("Ingrese una opcion: ");
		refresh(); //actualiza y muestra los cambios en la pantalla después de realizar modificaciones en las ventanas utilizando las funciones de ncurses.
		echo(); //activa la retroalimentación automática de entrada en la pantalla.
		scanw("%d", &menuOption);
		//scanw: lee la entrada de datos del usuario desde la ventana actual
		//%d indica el formato de entrada esperado, en este caso un entero
		//&menuOption para obtener la direccion de memoria de la variable, asi scanf almacena en esa direccion
		
		switch (menuOption) {
		case 1:
			printw("Auto Fantastico\n");
			refresh();
			autoFantastico(delayInicial);
			break;
		case 2:
			printw("Choque\n");
			refresh();
			choque(delayInicial);
			break;
		case 3:
			printw("Efecto pulso\n");
			refresh();
			efectoPulso(delayInicial);
			break;
		case 4:
			printw("Cargando bateria\n");
			refresh();
			cargandoBateria(delayInicial);
			break;
		case 5:
			printw("Adios\n");
			refresh();
			break;
		default:
			printw("Has seleccionado una opcion no disponible en el menu, intentalo de nuevo.\n");
			refresh();
			break;
		}
		
		printf("\n");
	} while (menuOption != 5);
	
	return 0;
}


//FUNCIONES

void pinSetup(void) { //realiza la configuracion inicial de los pines utilizados para controlar los LEDs
	pioInit();
	int i;
	for (i = 0; i < 8; i++) { //lo tenemos que hacer hasta 8 porque tenemos 8 LEDs
		//pinMode es una funcion para establecer si un pin es de entrada (INPUT) o de salida (OUTPUT)
		pinMode(led[i], OUTPUT); //led[i] representa el numero del pin actual dentro del bucle
		//ponemos OUTPUT porque lo establecemos al modo de pin como de salida
	}
}

void retardo(int delay){ 
	delayMillis(delay);
}
	
	void mostrar(unsigned char data) {
		int t;
		for (t = 128; t > 0; t = t / 2) {
			if (data & t) 
			{
				printw("*");
				refresh(); 
			}
			else 
			{
				printw("_");
				refresh();
			}
		}
	}
	
	void ledShow(unsigned char data) {
		int i;
		for (i = 0; i < 8; i++) { //lo hacemos hasta 8 porque estamos controlando 8 leds en total
			digitalWrite(led[i], (data >> i) & 1); //la funcion digitalWrite se utiliza para establecer el estado de cada LED individual
		}
	}
	
	void autoFantastico(int delay) {
		noecho();
		keypad(stdscr,TRUE); //habilita el modo de teclado especial en la ventana estándar. Permite la captura de teclas especiales
		nodelay(stdscr, TRUE); //no bloquea el programa y devuelve inmediatamente si no hay entrada disponible en ese momento.
		int tecla = getch();
		unsigned char data = 0x80; //declaramos un entero sin signo. 0x80 en binario es 10000000
		//Cada digito binario representa un LED individual y el digito mas significativo (el de la izquierda) representa el primer LED.
		//es decir, solo el primer LED esta encendido
		while (1) { //while(1) es para que se haga indefinidamente hasta que se cumpla la condicion de salida
			int i;
			for (i = 0; i < 8; i++) {
				printw("Presione ESC para volver al menu principal\n");
				printw("Presione KEY UP para acelerar\n");
				printw("Presione KEY DOWN para desacelerar\n");
				refresh();
				ledShow(data);
				mostrar(data);
				data >>= 1; //se desplaza el bit de dato un valor a la derecha
				retardo(delay);
				
				if (delay > 50 && tecla == KEY_UP) { //se verifica si estamos tocando la tecla hacia arriba 
					delay -= 50;
				}
				
				if (delay < 3000 && tecla == KEY_DOWN) {//esta es la de la tecla para abajo
					delay += 50;
				}
				
				if (tecla == KEY_ESCAPE) { //si tocamos escape se termina el programa
					return;
				}
			}
			
			data = 0x02; //en binario es 00000010
			//el segundo LED (contando desde la derecha) esta encendido, mientras que los demas LEDs estan apagados.
			
			for (i = 0; i < 6; i++) { //se utiliza para inciar una secuencia de luces desde un estado especifico
				printw("Presione ESC para volver al menu principal\n");
				printw("Presione KEY UP para acelerar\n");
				printw("Presione KEY DOWN para desacelerar\n");
				refresh();
				ledShow(data);
				mostrar(data);
				data <<= 1; //el valor de data se desplaza hacia la izquierda (<<= 1), lo que hace que la secuencia de luces se desplace de un LED encendido al siguiente en cada iteracion
				retardo(delay);
				
				if (delay > 50 && tecla == KEY_UP) { //se verifica si estamos tocando la tecla hacia arriba 
					delay -= 50;
				}
				
				if (delay < 3000 && tecla == KEY_DOWN) {//esta es la de la tecla para abajo
					delay += 50;
				}
				
				if (tecla == KEY_ESCAPE) { //si tocamos escape se termina el programa
					return;
				}
			}
		}
	}
	
	void choque(int delay) {
		noecho();
		keypad(stdscr,TRUE);
		nodelay(stdscr, TRUE);
		int tecla = getch();
		unsigned char tabla[] = {
			0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42
		};
		// Se define un arreglo llamado "tabla" que contiene una secuencia de valores en formato hexadecimal. 
		//Estos valores representan los patrones de luces que se mostrarán durante el efecto de choque.
		//0x81 (binario: 10000001): Este valor enciende el LED mas a la izquierda y el septimo LED desde la izquierda.
		//0x42 (binario: 01000010): Este valor enciende el segundo y el sexto LED desde la izquierda.
		//0x24 (binario: 00100100): Este valor enciende el tercer y el quinto LED desde la izquierda.
		//0x18 (binario: 00011000): Este valor enciende el cuarto y el quinto LED desde la izquierda.
		
		while (1) { //Esto inicia un bucle infinito que controla la ejecución del efecto de choque. 
			//El bucle se repetirá continuamente hasta que se detenga manualmente o se cumpla alguna condición de salida.
			int i;
			for (i = 0; i < 7; i++) {
				//itera a través de los elementos del arreglo tabla. 
				//En cada iteración, se realiza una serie de acciones relacionadas con la visualización del patrón de luz correspondiente.
				
				printw("Presione ESC para volver al menu principal\n");
				printw("Presione KEY UP para acelerar\n");
				printw("Presione KEY DOWN para desacelerar\n");
				refresh();
				ledShow(tabla[i]);
				mostrar(tabla[i]); //Llama a una funcion mostrar.
				retardo(delay); //Llama a una función retardo. 
				
				if (delay > 50 && tecla == KEY_UP) { //se verifica si estamos tocando la tecla hacia arriba
					delay -= 50;
				}
				
				if (delay < 3000 && tecla == KEY_DOWN) {//esta es la de la tecla para abajo
					delay += 50;
				}
				
				if (tecla == KEY_ESCAPE) { //si tocamos escape se termina el programa
					return;
				}
			}
		}
	}
	
	void efectoPulso(int delay) {
		noecho();
		keypad(stdscr,TRUE);
		nodelay(stdscr, TRUE);
		int tecla = getch();
		unsigned int index = 0;
		unsigned char tabla[] = { 0xFF, 0x00 }; // Tabla de control de los LEDs
		unsigned int size = sizeof(tabla) / sizeof(tabla[0]);
		
		while (1) {
			unsigned char data = tabla[index];
			
			printw("Presione ESC para volver al menu principal\n");
			printw("Presione KEY UP para acelerar\n");
			printw("Presione KEY DOWN para desacelerar\n");
			refresh();
			ledShow(data);
			mostrar(data); // Mostrar el estado de los LEDs
			retardo(delay);
			
			if (delay > 50 && tecla == KEY_UP) { //se verifica si estamos tocando la tecla hacia arriba
				delay -= 50;
			}
			
			if (delay < 3000 && tecla == KEY_DOWN) {//esta es la de la tecla para abajo
				delay += 50;
			}
			
			if (tecla == KEY_ESCAPE) { //si tocamos escape se termina el programa
				return;
			}
			
			index = (index + 1) % size;
		}
	}
	
	void cargandoBateria(int delay) {
		noecho();
		keypad(stdscr,TRUE);
		nodelay(stdscr, TRUE);
		int tecla = getch();
		unsigned char tabla[] = {
			0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF
		};
		
		while (1) {
			int i;
			for (i = 0; i < 9; i++) {
				printw("Presione ESC para volver al menu principal\n");
				printw("Presione KEY UP para acelerar\n");
				printw("Presione KEY DOWN para desacelerar\n");
				refresh();
				ledShow(tabla[i]);
				mostrar(tabla[i]);
				retardo(delay);
				
				if (delay > 50 && tecla == KEY_UP) { //se verifica si estamos tocando la tecla hacia arriba
					delay -= 50;
				}
				
				if (delay < 3000 && tecla == KEY_DOWN) {//esta es la de la tecla para abajo
					delay += 50;
				}
				
				if (tecla == KEY_ESCAPE) { //si tocamos escape se termina el programa
					return;
				}
			}
		}
	}
	

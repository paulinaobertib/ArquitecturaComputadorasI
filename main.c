#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "EasyPIO.h"
#include <ncurses.h>
#include <sys/ioctl.h>
#include <termios.h>

const char led[] = {14, 15, 18, 23, 24, 25, 8, 7}; //puertos de los leds
int delay = 10;
int salir;

//funciones pedidas
int retardo(int);
int teclas(int); 
void mostrar(unsigned char); //muestra tanto por consola y en el led
//funciones de las consignas
void autoFantastico();
void choque();
void carrera();
//funciones hechas extras
void efectoPulso();
void cargandoBateria();


int main() {
	pioInit(); //inicia easypio
	initscr(); //inicia la libreria ncurses
	
	int i;
	for (i = 0; i < 8; i++) { //lo tenemos que hacer hasta 8 porque tenemos 8 LEDs
		//pinMode es una funcion para establecer si un pin es de entrada (INPUT) o de salida (OUTPUT)
		pinMode(led[i], OUTPUT); //led[i] representa el numero del pin actual dentro del bucle
		//ponemos OUTPUT porque lo establecemos al modo de pin como de salida
	}
	
	//en c se pone la cantidad que queremos + 1 porque el ultimo es un espacio vacio
	int attempts = 3; //para contar los intentos
	int password_length = 6; //longitud maxima de la password
	char password[] = "vipau"; //para almacenar passwords ingresadas
	char inputPassword[password_length]; //password ingresada por el usuario
	int menuOption; //aca guardamos la opcion elegida por el usuario del menu
	
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
		printw("3. Carrera\n");
		printw("4. Efecto pulso\n");
		printw("5. Cargando bateria\n");
		printw("6. Salir\n");
		printw("Ingrese una opcion: ");
		refresh(); //actualiza y muestra los cambios en la pantalla despu�s de realizar modificaciones en las ventanas utilizando las funciones de ncurses.
		echo(); //activa la retroalimentaci�n autom�tica de entrada en la pantalla.
		scanw("%d", &menuOption);
		//scanw: lee la entrada de datos del usuario desde la ventana actual
		//%d indica el formato de entrada esperado, en este caso un entero
		//&menuOption para obtener la direccion de memoria de la variable, asi scanf almacena en esa direccion
		
		switch (menuOption) {
		case 1:
			printw("Auto Fantastico\n");
			refresh();
			autoFantastico();
			break;
		case 2:
			printw("Choque\n");
			refresh();
			choque();
			break;
		case 3:
			printw("Carrera\n");
			refresh();
			carrera();
			break;
		case 4:
			printw("Efecto pulso\n");
			refresh();
			efectoPulso();
			break;
		case 5:
			printw("Cargando bateria\n");
			refresh();
			cargandoBateria();
			break;
		case 6:
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

int retardo(int n) {
	if (delay < 50) {
		if (n == 0) {
			delay = delay + 5; //incrementa el retardo en 5
			return delay; //me da el nuevo valor del retardo
		}
	}
	if (delay > 5)
		if (n == 1) {
			delay = delay - 5; //decrementa el retardo en 5
			return delay; //me da el nuevo valor del retardo
	}
		return delay; //valor actual del retardo
}

int teclas(int a) {
	initscr();  // Inicializa la biblioteca ncurses
	noecho();  // Desactiva el eco de teclas ingresadas
	cbreak();  // Desactiva el buffering de linea
	int teclaPresionada;  //almacenar la tecla presionada
	keypad(stdscr, TRUE);  // Habilita la captura de teclas especiales
	nodelay(stdscr, TRUE);  // Configura getch() para que no bloquee el programa
	
	teclaPresionada = getch(); //lee la tecla presionada
	nocbreak(); //restaura el buffering de la linea
	
	if (teclaPresionada == KEY_UP) {
		a = retardo(1);
	}
	if (teclaPresionada == KEY_DOWN) {
		a = retardo(0);
	}
	if (teclaPresionada == 115) {  // para salir apretar s que es en codigo ascii
		echo();
		endwin();
		salir = 0;
		clear();
	}
	for (int j = 0; j < a; j++) {
		unsigned int i = 0x4fffff;  // raspberry 0x3fffff 
		while (i) i--;
	}
	echo();
	endwin();
	return a;
}

//mostrar es por consola y por led
void mostrar(unsigned char data) {
	initscr();
	
	int t;
	int i;
	for (t = 7; t >= 0; --t) {
		char simboloConsola;
		int prendidoApagadoLed;
		
		if (data & (1 << i)) {
			simboloConsola= '*';
			prendidoApagadoLed = 1;
			
		} else {
			simboloConsola = '_';
			prendidoApagadoLed = 0;
		}
		printw("%c", simboloConsola); //lo muestra por consola
		digitalWrite(led[i], prendidoApagadoLed);  //muestra por led
	}
	printw("\r");
	fflush(stdout);
	endwin();

}

//funciones pedidas

void autoFantastico() {
	//tabla del auto 
	unsigned char tablaAutoFantastico[] = {
		0x80, 0x40, 0x20, 0x10, 0x08, 0x04, 0x02, 0x01,
	};
	
	for (int i = 0; i < 8; i++) {
		mostrar(tablaAutoFantastico[i]);
		delay = teclas(delay);
	}
	for (int i = 7; i != 0; i--) {
		mostrar(tablaAutoFantastico[i]);
		delay = teclas(delay);
	}
}
	
void choque() {
	int i;
	unsigned char tablaChoque[] = {
		0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42, 0x81,
	};
		// Se define un arreglo llamado "tabla" que contiene una secuencia de valores en formato hexadecimal. 
		//Estos valores representan los patrones de luces que se mostrar�n durante el efecto de choque.
		//0x81 (binario: 10000001): Este valor enciende el LED mas a la izquierda y el septimo LED desde la izquierda.
		//0x42 (binario: 01000010): Este valor enciende el segundo y el sexto LED desde la izquierda.
		//0x24 (binario: 00100100): Este valor enciende el tercer y el quinto LED desde la izquierda.
		//0x18 (binario: 00011000): Este valor enciende el cuarto y el quinto LED desde la izquierda.
	for (i = 0; i < 8; i++) {
		mostrar(tablaChoque[i]);
		delay = teclas(delay);
	}

}

void carrera (){
	unsigned char tablaCarrera[] = {
		0x80, 0x80, 0x40, 0x40, 0x20, 0x20,
			0x10, 0x10, 0x88, 0x48, 0x24, 0x14,
			0xA, 0x6, 0x3,0x1
	};
	
	for (i = 0; i < 16; i++) {
		mostrar(tablaCarrera[i]);
		delay = teclas(delay);
	}
}

//funciones inventadas
void efectoPulso() {
	unsigned int index = 0;
	unsigned char tablaEfectoPulso[] = { 0xFF, 0x00 }; // Tabla de control de los LEDs
	unsigned int size = sizeof(tablaEfectoPulso) / sizeof(tablaEfectoPulso[0]);
	
	while (1) {
		unsigned char data = tablaEfectoPulso[index];
		mostrar(tablaEfectoPulso);
		delay = teclas(delay);
		
		index = (index + 1) % size;
	}
}
	
void cargandoBateria() {
	
	int i;
	unsigned char tablaCargandoBateria[] = {
		0x00, 0x80, 0xC0, 0xE0, 0xF0, 0xF8, 0xFC, 0xFE, 0xFF
	};
	for (i = 0; i < 9; i++) {
		mostrar(tablaCargandoBateria[i]);
		delay = teclas(delay);
	}
}


	

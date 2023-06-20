#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <stdint.h> //libreria para usar el uint8_t 
#include <windows.h> //libreria para usar las teclas de flechas


//funcion para inicializar EASY PIO
void pinSetup(void);
//funciones pedidas
void retardo(unsigned long int);
void mostrar(unsigned char);
//funciones de las consignas
void autoFantastico(unsigned long int);
void carrera(unsigned long int);
void choque(unsigned long int);
//funciones hechas extras
void efectoPulso(unsigned long int);
void cargandoBateria(unsigned long int);

int main() {
	//en c se pone la cantidad que queremos + 1 porque el ultimo es un espacio vacio
	const int MAX_ATTEMPTS = 3; //numero maximo de intentos
	const int PASSWORD_LENGTH = 5; //longitud maxima de la password
	char passwords[MAX_ATTEMPTS][PASSWORD_LENGTH + 1]; //para almacenar passwords ingresadas
	char inputPassword[PASSWORD_LENGTH + 1]; //password ingresada por el usuario
	int attempt; //para contar los intentos
	int menuOption; //aca guardamos la opcion elegida por el usuario del menu
	unsigned long int speedini = 151000000; //esta variable representa la velocidad inicial de la secuencia de encendido de los LEDs
	unsigned long int speed = speedini; // 1000000 //Esto se hace para tener una variable speed que se pueda modificar durante la ejecucion del programa sin alterar el valor original de speedini. Inicialmente, speed tendr� el mismo valor que speedini.
	retardo(380000000); //es el tiempo de retardo especificado en algun tipo de unidad de tiempo.
	
	for (attempt = 0; attempt < MAX_ATTEMPTS; attempt++) { //ciclo for para los intentos de la password
		printf("Ingrese su password de 5 digitos: "); //printf para mostrar por consola
		
		int j = 0; //para rastrear la posicion en la cadena input password
		char c; //para almacenar lo ingresado por el usuario
		
		//while para leer los caracteres ingresados por el usuario
		//getch para leer el caracter sin mostrarlo en pantalla
		while ((c = getch()) != 13) { //13 es el enter en ASCII
			if (c != 8) { //8 es la tecla de borrar en ASCII
				inputPassword[j] = c;
				j++;
				printf("*");
			} else {
				if (j > 0) {
					printf("\b \b"); //Al imprimir "\b \b", se muestra un car�cter de retroceso (\b) para mover el cursor hacia la izquierda, luego se imprime un espacio en blanco para sobrescribir el �ltimo car�cter visible y finalmente se emite otro car�cter de retroceso para colocar el cursor nuevamente en la posici�n original.
					j--;
				}
			}
		}
		
		inputPassword[j] = '\0';
		printf("\n");
		
		strncpy(passwords[attempt], inputPassword, PASSWORD_LENGTH); //copiar la password ingresada (inputPassword) a la matriz passwords en la posicion attempt.
		passwords[attempt][PASSWORD_LENGTH] = '\0'; //se le asigna el caracter nulo al final para establecer que es el fin de la cadena
		
		if (strcmp(passwords[attempt], "vipau") == 0) { //compara dos cadenas de caracteres y devuelve un valor igual a cero si las cadenas son iguales
			printf("Bienvenido al sistema\n");
			break;
		} else {
			printf("Password invalida, le quedan %d intentos.\n", MAX_ATTEMPTS - attempt - 1);
		}
	}
	
	if (attempt == MAX_ATTEMPTS) { //si llegamos a la cantidad maxima de intentos,no hay mas
		printf("No tienes mas intentos\n");
	}
	
	do {
		//\n es un salto de linea
		printf("---- MENU ----\n");
		printf("1. Auto Fantastico\n");
		printf("2. Carrera\n");
		printf("3. Choque\n");
		printf("4. Efecto pulso\n");
		printf("5. Cargando bateria\n");
		printf("6. Salir\n");
		printf("Ingrese una opcion: ");
		//scanf es para leer la entrada de usuario desde la consola
		//%d indica el formato de entrada esperado, en este caso un entero
		//&menuOption para obtener la direccion de memoria de la variable, asi scanf almacena en esa direccion
		scanf("%d", &menuOption);
		
		switch (menuOption) {
		case 1:
			printf("Auto Fantastico\n");
			system("cls");
			autoFantastico(speed);
			menuOption = 0;
			speed = speedini;
			break;
		case 2:
			printf("Carrera\n");
			system("cls");
			carrera(speed);
			menuOption = 0;
			speed = speedini;
			break;
		case 3:
			printf("Choque\n");
			system("cls");
			choque(speed);
			menuOption = 0;
			speed = speedini;
			break;
		case 4:
			printf("Efecto pulso\n");
			system("cls");
			efectoPulso(speed);
			menuOption = 0;
			speed = speedini;
			break;
		case 5:
			printf("Cargando bateria\n");
			system("cls");
			cargandoBateria(speed);
			menuOption = 0;
			speed = speedini;
			break;
		case 6:
			system("cls");
			printf("Adios\n");
			break;
		default:
			system("cls");
			printf("Has seleccionado una opcion no disponible en el menu, intentalo de nuevo.\n");
			menuOption = 0;
			break;
		}
		
		printf("\n");
	} while (menuOption != 6);
	
	return 0;
}


//FUNCIONES

void retardo(unsigned long int a){ 
	//"unsigned long int" (representa un número entero sin signo y generalmente ocupa 4 bytes en la memoria). La función no devuelve ningún valor (void).
	//Bucle de a que se ejecuta siempre que a sea distinto de cero
	//En cada iteración del bucle, se decrementa el valor de "a" en 1
	while (a) a--;
}
	
	void mostrar(unsigned char data) {
		//mask representa una mascara de bits que se utiliza para verificar el estado de cada bit en el valor de dato
		for (unsigned char mask = 128; mask > 0; mask >>= 1) { //128=10000000 en binario
			//En cada iteracion, mask se desplaza un bit hacia la derecha mediante el operador de desplazamiento a la derecha (>>=).
			if (data & mask) { //En cada iteracion del bucle, se verifica si el bit correspondiente en dato esta activo (1) utilizando la operacion de bitwise AND (&) con mask. Si el resultado es verdadero, se imprime *, de lo contrario se imprime _.
				printf("*");
			} else {
				printf("_");
			}
		}
	}
	
	void autoFantastico(unsigned long int speed) {
		unsigned char data = 0x80; //declaramos un entero sin signo. 0x80 en binario es 10000000
		//Cada digito binario representa un LED individual y el digito mas significativo (el de la izquierda) representa el primer LED.
		//es decir, solo el primer LED esta encendido
		while (1) { //while(1) es para que se haga indefinidamente hasta que se cumpla la condicion de salida
			for (int i = 0; i < 8; ++i) {
				printf("Presione ESC para volver al menu principal\n");
				printf("Presione KEY UP para acelerar\n");
				printf("Presione KEY DOWN para desacelerar\n");
				printf("Delay: %lu\n", speed);
				mostrar(data);
				data >>= 1; //se desplaza el bit de dato un valor a la derecha
				retardo(speed);
				system("cls"); //limpia la consola
				
				if ((speed - 5000000) > 1000000) {
					if (GetAsyncKeyState(VK_UP) & 0x0001) { //se verifica si estamos tocando la tecla hacia arriba (VK_UP)
						//bit 0x0001 indica si la tecla esta siendo presionada
						speed -= 5000000;
					}
				}
				
				if (GetAsyncKeyState(VK_DOWN) & 0x0001) {//esta es la de la tecla para abajo
					speed += 5000000;
				}
				
				if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) { //si tocamos escape se termina el programa
					return;
				}
			}
			
			data = 0x02; //en binario es 00000010
			//el segundo LED (contando desde la derecha) esta encendido, mientras que los demas LEDs estan apagados.
			
			for (int i = 0; i < 6; ++i) { //se utiliza para inciar una secuencia de luces desde un estado especifico
				printf("Presione ESC para volver al menu principal\n");
				
				printf("Delay: %lu\n", speed); //se usa %lu para unsigned long
				mostrar(data);
				data <<= 1; //el valor de data se desplaza hacia la izquierda (<<= 1), lo que hace que la secuencia de luces se desplace de un LED encendido al siguiente en cada iteracion
				retardo(speed);
				system("cls");
				
				if ((speed - 5000000) > 1000000) {
					if (GetAsyncKeyState(VK_UP) & 0x0001) {
						speed -= 5000000;
					}
				}
				
				if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
					speed += 5000000;
				}
				
				if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
					return;
				}
			}
		}
	}
	
	void carrera(unsigned long int speed) {
		//uint8_t es un array de enteros sin signo con 8 bits
		//el array se inicializa con los valores entre {}
		uint8_t tabla[] = {
			0x80, 0x80, 0x40, 0x40, 0x20, 0x20,
				0x10, 0x10, 0x88, 0x48, 0x24, 0x14,
				0x0A, 0x06, 0x03, 0x01
		};
		//0x80 (binario: 10000000): Enciende el LED mas a la izquierda.
		//0x40 (binario: 01000000): Enciende el segundo LED desde la izquierda.
		//0x20 (binario: 00100000): Enciende el tercer LED desde la izquierda.
		//0x10 (binario: 00010000): Enciende el cuarto LED desde la izquierda.
		//0x88 (binario: 10001000): Enciende el primer y el quinto LED desde la izquierda.
		//0x48 (binario: 01001000): Enciende el segundo y el quinto LED desde la izquierda.
		//0x24 (binario: 00100100): Enciende el tercer y el quinto LED desde la izquierda.
		//0x14 (binario: 00010100): Enciende el cuarto y el quinto LED desde la izquierda.
		//0x0A (binario: 00001010): Enciende el tercer y el sexto LED desde la izquierda.
		//0x06 (binario: 00000110): Enciende el cuarto y el quinto LED desde la izquierda.
		//0x03 (binario: 00000011): Enciende el quinto y el sexto LED desde la izquierda.
		//0x01 (binario: 00000001): Enciende el sexto LED desde la izquierda.
		
		while (1) {
			for (int i = 0; i < 16; ++i) {
				printf("Presione ESC para volver al menu principal\n");
				printf("Presione KEY UP para acelerar\n");
				printf("Presione KEY DOWN para desacelerar\n");
				printf("Delay: %lu\n", speed);
				//%lu es un especificador de formato que se utiliza para imprimir un valor de tipo unsigned long.
				//la l indica que el argumento es de tipo unsigned long, y u indica que el valor se debe imprimir como un numero sin signo.
				//\n representa un salto de linea, para que la siguiente salida aparezca en una nueva linea.
				mostrar(tabla[i]);
				retardo(speed);
				system("cls"); //limpia la consola
				
				if ((speed - 5000000) > 1000000) {
					if (GetAsyncKeyState(VK_UP) & 0x0001) {
						speed -= 5000000;
					}
				}
				
				if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
					speed += 5000000;
				}
				
				if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
					return;
				}
			}
		}
	}
	
	void choque(unsigned long int speed) {//Esto define la función choque que toma un parámetro "speed" de tipo "unsigned long int".
		// Se define un arreglo llamado "tabla" que contiene una secuencia de valores en formato hexadecimal. 
		//Estos valores representan los patrones de luces que se mostrarán durante el efecto de choque.
		
		uint8_t tabla[] = {
			0x81, 0x42, 0x24, 0x18, 0x18, 0x24, 0x42
		};
		//0x81 (binario: 10000001): Este valor enciende el LED mas a la izquierda y el septimo LED desde la izquierda.
		//0x42 (binario: 01000010): Este valor enciende el segundo y el sexto LED desde la izquierda.
		//0x24 (binario: 00100100): Este valor enciende el tercer y el quinto LED desde la izquierda.
		//0x18 (binario: 00011000): Este valor enciende el cuarto y el quinto LED desde la izquierda.
		
		while (1) { //Esto inicia un bucle infinito que controla la ejecución del efecto de choque. 
			//El bucle se repetirá continuamente hasta que se detenga manualmente o se cumpla alguna condición de salida.
			
			for (int i = 0; i < 7; ++i) {
				//itera a través de los elementos del arreglo tabla. 
				//En cada iteración, se realiza una serie de acciones relacionadas con la visualización del patrón de luz correspondiente.
				
				printf("Presione ESC para volver al menu principal\n");
				printf("Presione KEY UP para acelerar\n");
				printf("Presione KEY DOWN para desacelerar\n");
				printf("Delay: %lu\n", speed); //Imprime el valor actual de speed en la consola, mostrando la velocidad actual del efecto de choque.

				mostrar(tabla[i]); //Llama a una funcion mostrar.
				retardo(speed); //Llama a una función retardo. 
				system("cls"); //Limpia la consola para borrar los patrones de luces anteriores y prepararse para mostrar el siguiente patrón.
				
				if ((speed - 5000000) > 1000000) {
					if (GetAsyncKeyState(VK_UP) & 0x0001) { //flecha hacia arriba
						speed -= 5000000; 
					}
				}
				
				if (GetAsyncKeyState(VK_DOWN) & 0x0001) { //flecha hacia abajo
					speed += 5000000;
				}
				
				if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) { //tecla escape
					return;
				}
			}
		}
	}
	
	void efectoPulso(unsigned long int speed) {
		unsigned int index = 0;
		unsigned char tabla[] = { 0xFF, 0x00 }; // Tabla de control de los LEDs
		unsigned int size = sizeof(tabla) / sizeof(tabla[0]);
		
		while (1) {
			unsigned char data = tabla[index];
			
			printf("Presione ESC para volver al menu principal\n");
			printf("Presione ESC para volver al menu principal\n");
			printf("Presione KEY UP para acelerar\n");
			printf("Presione KEY DOWN para desacelerar\n");
			printf("Delay: %lu\n", speed);
			mostrar(data); // Mostrar el estado de los LEDs
			retardo(speed);
			system("cls"); // Limpiar la pantalla
			
			if ((speed - 5000000) > 1000000) {
				if (GetAsyncKeyState(VK_UP) & 0x0001) {
					speed -= 5000000;
				}
			}
			
			if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
				speed += 5000000;
			}
			
			if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
				return;
			}
			
			index = (index + 1) % size;
		}
	}
	
	void cargandoBateria(unsigned long int speed) {
		unsigned char data = 0x00; // todos los LEDs apagados excepto el primero
		//0xFF inicializa todos prendidos
		
		while (1) {
			for (int i = 0; i < 8; ++i) {
				printf("Presione ESC para volver al menu principal\n");
				printf("Presione KEY UP para acelerar\n");
				printf("Presione KEY DOWN para desacelerar\n");
				printf("Delay: %lu\n", speed);
				//0xFF representa el valor binario 11111111. Este valor tiene todos los bits activados, lo que significa que todos los LEDs estar�an encendidos.
				//>> es el operador de desplazamiento a la derecha. Cuando se aplica a 0xFF, desplaza todos los bits hacia la derecha en funci�n del valor de i. En cada iteraci�n, i aumenta, lo que resulta en un desplazamiento mayor y, por lo tanto, en la activacion gradual de los LEDs.
				//data | (0xFF >> i) realiza una operacion de OR bit a bit entre data y el resultado del desplazamiento. Esto enciende los LEDs anteriores y el siguiente LED en cada iteracion.
				mostrar(data | (0xFF >> i)); // Encender LEDs anteriores y el siguiente LED
				retardo(speed);
				system("cls"); // Limpiar la pantalla
				
				if ((speed - 5000000) > 1000000) {
					if (GetAsyncKeyState(VK_UP) & 0x0001) {
						speed -= 5000000;
					}
				}
				
				if (GetAsyncKeyState(VK_DOWN) & 0x0001) {
					speed += 5000000;
				}
				
				if (GetAsyncKeyState(VK_ESCAPE) & 0x0001) {
					return;
				}
			}
			
			data = 0x00; // Apagar todos los LEDs
		}
	}


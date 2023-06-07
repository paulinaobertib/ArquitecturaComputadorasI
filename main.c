#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

int main() {
	//en c se pone la cantidad que queremos + 1 porque el ultimo es un espacio vacio
	const int MAX_ATTEMPTS = 3; //numero maximo de intentos
	const int PASSWORD_LENGTH = 5; //longitud maxima de la password
	char passwords[MAX_ATTEMPTS][PASSWORD_LENGTH + 1]; //para almacenar passwords ingresadas
	char inputPassword[PASSWORD_LENGTH + 1]; //password ingresada por el usuario
	int attempt; //para contar los intentos
	
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
					printf("\b \b"); //Al imprimir "\b \b", se muestra un carácter de retroceso (\b) para mover el cursor hacia la izquierda, luego se imprime un espacio en blanco para sobrescribir el último carácter visible y finalmente se emite otro carácter de retroceso para colocar el cursor nuevamente en la posición original.
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
	
	return 0;
}



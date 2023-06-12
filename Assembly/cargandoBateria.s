				MOV		r0, #2		; Mueve el valor 2 al registro r0. Aqu� se est� pasando el valor 2 como argumento para la velocidad.
				MOV		SP, #pilaptr	; Mueve el valor de la etiqueta pilaptr al registro SP. Esto establece el puntero de pila en la direcci�n de memoria indicada por pilaptr.
				BL		CargandoBateria	; Llama a la funci�n CargandoBateria utilizando la instrucci�n de salto y enlace (BL). Esto saltar� a la etiqueta CargandoBateria y guardar� la direcci�n de retorno en el registro LR.
				end		; Fin del programa.
				
CargandoBateria
				STMFD	SP!, {r4, r5, r6, r7, LR}	; Guarda los registros r4, r5, r6, r7 y LR en la pila
				
				MOV		r6, r0		; Guarda el valor del registro r0 en r6. Este valor fue pasado como par�metro.
				MOV		r4, #0x00		; Mueve el valor 0x00 al registro r4. Esto representa el n�mero binario 11111111.
				MOV		r5, #8		; Mueve el valor 8 al registro r5. Este ser� nuestro contador.
				
ForCargandoBateria
				MOV		r0, r4		; Prepara r0 para pasarlo como par�metro a la funci�n Display
				BL		Display
				
				MOV		r0, r6		; Prepara r0 para pasarlo como par�metro a la funci�n Retardo
				BL		Retardo
				
				BL		SystemCLS
				
				MOV		r4, r4, LSL #1	; Multiplica r4 por 2 mediante un desplazamiento l�gico a la izquierda
				SUBS		r5, r5, #1	; Resta 1 a r5 y actualiza las banderas
				BNE		ForCargandoBateria	; Salta al inicio del bucle si r5 no es igual a cero
				BEQ		Termino		; Salta a la etiqueta "Termino" si r5 es igual a cero
				
Display
				MOV		PC, LR  ; Volver al punto de retorno
				
forDisplay
				MOV		PC, LR
				;		Salta de vuelta a la ubicaci�n desde donde se llam� a la funci�n Display
				
Retardo
				MOV		PC, LR
				;		Salta de vuelta a la ubicaci�n desde donde se llam� a la funci�n Retardo
				
SystemCLS
				;		Simula la limpieza de pantalla (no se proporciona c�digo)
				MOV		PC, LR
				;		Salta de vuelta a la ubicaci�n desde donde se llam� a la funci�n SystemCLS
				
Termino
				LDMFD	SP!, {r4, r5, r6, r7, LR}
				;		Recupera los valores almacenados en la pila en los registros r4, r5, r6, r7 y LR
				MOV		PC, LR
				;		Salta de vuelta a la ubicaci�n desde donde se llam� a la funci�n Termino
				
pila				FILL		40
				;		Reserva un bloque de memoria de 40 bytes para la pila del programa
				;Al		reservar 40 bytes, se garantiza que hay suficiente espacio disponible para almacenar los registros y variables necesarios en el contexto del programa en cuesti�n.
				
pilaptr			DCB		1
				;		Declara una variable pilaptr de un solo byte y le asigna el valor 1
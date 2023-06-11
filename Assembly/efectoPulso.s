			MOV		r0, #2			; carga el valor 2 en el registro r0.
			LDR		SP, =pila		; carga la dirección de la etiqueta "pila" en el registro SP (puntero de pila).
			BL		efectoPulso		; llamada a la subrutina "efectoPulso"
			END
			
efectoPulso
			STMFD	SP!, {r4, r5, r6, r7, r8, r9, r10, LR}	; guarda múltiples registros en la pila
			MOV		r10, #tabla		; carga el valor inmediato de la etiqueta "tabla" en el registro r10
			MOV		r6, #0			; carga el valor inmediato 0 en el registro r6
			MOV		r9, r0			; copia el valor de r0 en el registro r9.
ForEfectoPulso
			LDRB		r4, [r10, r6]	; carga un byte de memoria en el registro r4. La dirección se calcula sumando el valor de r10 y r6.
			MOV		r0, r4			; copia el valor de r4 en el registro r0.
			BL		mostrar			; llama a la subrutina "mostrar"
			MOV		r0, r9			; copia el valor de r9 en el registro r0.
			BL		retardo			; llama a la subrutina "retardo"
			BL		SystemCLS		; llama a la subrutina "SystemCLS"
			ADD		r6, r6, #1		; incrementa el valor de r6 en 1.
			CMP		r6, #16			; compara el valor de r6 con el valor inmediato 16.
			BNE		ForEfectoPulso	; salta a la etiqueta "ForEfectoPulso" si no se cumple la condición
			BL		Termino			; llama a la subrutina "Termino"
			
mostrar
			;		R0 contiene el valor a mostrar en los LEDs
			MOV		PC, LR			; salta a la siguiente instrucción utilizando el valor almacenado en el registro LR (Link Register).
			
retardo
			;		R0 contiene el valor de retardo
			MOV		PC, LR			; salta a la siguiente instrucción utilizando el valor almacenado en el registro LR (Link Register).
			
SystemCLS
			;		Implementa la limpieza de pantalla
			MOV		PC, LR			; salta a la siguiente instrucción utilizando el valor almacenado en el registro LR (Link Register).
			
Termino
			LDMFD	SP!, {r4, r5, r6, r7, r8, r9, r10, LR}	; carga múltiples registros desde la pila.
			MOV		PC, LR
			
			;		se define la etiqueta "tabla" y se inicializa con una serie de valores.
tabla		DCB		0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00
pila			EQU		0x20000000

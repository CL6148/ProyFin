*******************************************
* Proyecto Final - Diseño de Compiladores *
*					  *
*		   CL+			  *
*					  *
* Carlos Andrés Luna Leyva		  *
* A00826148				  *
*******************************************

La finalidad de este proyecto es crear un lenguaje orientado a objetos con las funcionalidades básicas de cualquier lenguaje de programación tal como estatutos, expresiones matemáticas, modulos locales y globales, y estructuras de datos sencillas. Para el aspecto de objectos se busca desarrollar mecanismos tal como clases, atributos, métodos, y herencia (1 solo nível).

El proyecto está diseñado para ser ejecutado por medio de Flex y Bison a base del lenguaje C.

*****************************************************************************

Instrucciones de Ejecución:
  Dentro del proyecto se encuentra el archivo 'compile.bat' para la compilación de los archivos del lexer y parser, pero de igual manera se pueden ejecutar los siguientes comandos de manera individual para la compilación.
	./compile.bat

		o

	bison -d parser.y
	flex scanner.l
	gcc -o main parser.tab.c lex.yy.c

  Una vez compilado, se ejecuta el archivo main.exe con el archivo de texto con el código a ejecutar.
	./main {Archivo_de_Prueba.extension}

*****************************************************************************

v0.3: Finalización de Parser [2022-11-15]
	+ parser.y	:	Actualización de Gramática, funciones leídas completamente
	
	- symtab.c / .h	:	Rediseño de sistema de tabla de símbolos, actualmente incompleto

	Problemas Identificados:
	- Tabla de Símbolos lee ID's incorrectamente y en casos les agrega un caracter no reconocido y conflicta con la validación de duplicados.

	Pendiente:
	- Semántica general
	- Tabla de Símbolos
	- Compilación y creación de Cuádruplos
	- Creación de Código de Máquina

v0.2: Tabla de Símbolos y Optimización Lexer/Parser [2022-11-04]
	+ scanner.l	:	Actualización de Tokens, tentativo formato base final
	+ parser.y	:	Actualización de Gramática, tentativo formato base final
	+ symtab.h	:	Definición de structs utilizados por Table de Símbolos
	+ symtab.c	:	Mecanismos principales de la Tabla de Símbolos y sus funcionalidades

	Resuelto:
	° La Gramática y ejecución de Bison ya no regresa errores Shift/Reduce ni Reduce/Reduce con las Gramáticas implementadas
	° Gramática de 'variables' funciona correctamente y permite declarar multiples variables de multiples tipos de dato

	Pendiente:
	- Semántica general para todas las reglas generales (Validación de Tipos / Validación de Operaciones)
	- Tabla de Símbolos regresa caractéres no reconocidos en debug, revisar funcionamiento
	- Tabla de Símbolos no verifica duplicados de manera consistente, posible arreglo con semántica
	- Compilar y evaluar código de manera funcional, preparar para generación de cuádruplos
	- Implementar Gramática propia para funciones y scopes anidados

v0.1: Incremento a Lexer y Parser 'OOP Basic' [2022-10-10]
	+ scanner.l	:	Actualización de Tokens a utilizar
	+ parser.y	:	Nuevas gramáticas actualizadas para el proyecto

	Pendiente:
	- Resolver problemas de Bison Shift/Reduce y Reduce/Reduce
	- Gramática de 'variables' tiene conflicto en vars2, posible arreglo con semántica
	- Semántica general para todas las reglas gramaticales

v0.0: Esqueleto de Lexer y Parser 'Little Duck' [2022-10-03]
	+ scanner.l	:	Archivo Lexer
	+ parser.y	: 	Archivo Parser
	+ compile.bat	:	Ejecución y compilación de archivos en consola
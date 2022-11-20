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

v0.5: Máquina Virtual Desarrollada y Generador de Código Maduro [2022-11-19]
	+ parser.y	:	Madurez de Semántica para estatutos y expresiones comunes, integración de archivo parser.y como hub principal de ejecución
	+ symtab.h	:	Merge enter symtab.h y codeGenerator.h para la generación de código e inserción de variables a table de símbolos en un solo archivo
				Rediseño de funciones de inserción y búsqueda de variables en la lista anidada y cambio de nombre para simplificar significado (insert->putsym | lookup->getsym)
				Eliminación de archivo symtab.c para ejecutar funciones directamente desde archivo parser.y
	+ virtualMachine.h:	Introducción de pila de variables separada a la pila de ejecución para aislar la asignación y manipulación de valores
				Limpieza y redefinición de algunos estatutos de ejecución de código para tener resultados consistentes
				Impresión a consola al llamar cada estatuto de ejecución para fines de debug [TEMP]
	- varTypes.c|.h	:	Eliminación de archivos reduntantes / sin utilizar

	Resulelto:
	° Semántica básica sobre gramática fundamental para la ejecución del compilador y código generado
	° Rediseño de Tabla de Símbolos y sus funciones
	° Implementación de reglas fundamentales de Máquina Virtual
	° Creación y ejecución de código generado fundamental

	Notas:
	¬ Para facilitar la implementación y comprobar el funcionamiento de los elementos agregados, el parser/lexer fue reducido a solo la ejecución del bloque MAIN y sus estatutos utilizando solo variables de tipo INT.
	¬ Esto fue para reducir el ruido y complejidad de las pruebas de integración, ahora con la implementación completa de Máquina Virtual y Generación de Código con el compilador reducido se deben introducir estos elementos eliminados.

	Pendiente:
	- Implementación y verificación de diferentes tipos de datos
	- Completar expresiones relacionales y booleanas (>= , <= , AND , OR , NOT) con reglas de Máquina Virtual y Generación de Código
	- Implementación de Funciones Parametrizables y ejecución correcta de variables en alcances (scopes) diferentes
	- Implementación de Clases y Objetos en el código

v0.4: Máquina Virtual Sencilla y Generador de Código Base [2022-11-19]
	+ parser.y	:	Inicios de Semántica, definición de 'labels' con funcionalidad de saltos pendientes (IF/ELSE DO/WHILE)
	+ scanner.l	: 	Inicios de Semántica, definición de tipos de regreso para variables
	+ symtab.c|.h	:	Integración de 'offset' para máquina virtual
	+ varTypes.c|.h	:	Archivo con lógica de revisión semántica de tipos de retorno
	+ virtualMachine.h:	Archivo con pila de ejecución de código
	+ codeGenerator	:	Archivo con asignación de offset a elementos y resolución de saltos pendientes

	Resuleto:
	° La tabla de símbolos ya no regresa caracteres no reconocidos, completamente funcional
	
	Pendiente:
	- Completar semántica e implementar sobre reglas de gramática
	- Posible rediseño de Tabla de Símbolos según implementación semántica
	- Definir todas las reglas de la Máquina Virtual para todos los elementos del compilador
	- Crear código real en Generador de Código para ejecución final del compilador

v0.3: Finalización de Parser [2022-11-15]
	+ parser.y	:	Actualización de Gramática, funciones leídas completamente
	
	- symtab.c|.h	:	Rediseño de sistema de tabla de símbolos, actualmente incompleto

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
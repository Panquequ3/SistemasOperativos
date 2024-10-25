# MultiTarea

## Tabla de contenidos
- [Descripcion](#descripcion)

- [Requisitos](#requisitos)

- [Instalacion / Compilacion](#instalacion--compilacion)

- [Ejecucion](#ejecucion)

- [Funciones](#funciones)

- [Variables de Entorno](#variables-de-entorno)

- [Atribucion](#atribucion)

## Descripcion
Se propuso crear un programa que desplegara un menú con diferentes opciones 
con las que el usuario pueda probar diferentes valores, desde identificar una
palabra palíndromo, hasta evaluar un número en una función específica, esta solución contempla el manejo correcto de los datos ingresados para evitar un resultado incorrecto.

## Requisitos
- 
  Para ejecutar este programa, necesitas tener un compilador de C++ instalado en tu sistema con al menos la versión 6.3.0. y estar en la carpeta principal "programaMenu".  
  El programa es compatible con sistemas Linux y también puede ejecutarse en Windows, siempre y cuando tengas instalado un subsistema Linux.  
  Tambien se requiere tener instalado Python3 y la libreria matplotlib de este mismo compilador dentro de Linux.  
  Para la lectura de archivos .env se descargó la librería dotenv-cpp, el cual debe ser añadido a la carpeta junto con el programa.

## Instalacion / Compilacion
* Para la instalación del programa es necesario con clonar el repositorio, y tambien clonar la [libreria dotenv-cpp](https://github.com/laserpants/dotenv-cpp.git) y añadirla a la carpeta __"external"__ junto con el resto, de lo contrario el .env con las variables de entorno no podran ser leidas correctamente. Asegurate de mantener todos los archivos en las carpetas correctas, en caso de no ejecutarse correctamente, verificar que la ubicación de cada archivo. 
  > Importante mencionar que se deben compilar 7 programas previamente, el programa principal (con make) y los programas que ejecutan la opción (6), (7), (8), (9) y (10) (con **"make -f MakefileC", "make -f MakefileP" y "make -f MakefileI"** respectivamente)
* Instalar la libreria __matplotlib__ de python se realiza con pip, utilizando el comando en consola __pip3 install matplotlib__.  
  > Importante mencionar que es principalmente requerido la instalacion de Python3 dentro del subsistema, cualquier uso de otra version se debe modificar dentro del codigo para ejecutar el codigo.

## Ejecucion

Posterior a la compilación, utilizaremos el comando
```bash
./multiTarea -u nombre_usuario -p contraseña -t "frase" -v "n1;n2;..;nk" -n numero  
```
para acceder al programa.

> Mencionar que el vector debe seguir la forma de: __numero__ o __numeroA;numeroB;...__ en caso de añadir más números.


| Argumento | Descripcion                  |
| -------  | ----------------------------- |
| u | Especifica el usuario                |
| p | Especifica la contraseña del usuario |
| t | Especifica el texto/frase a elección |
| v | Especifica el vector de numeros      |
| n | Especifica un número real            |

> Importante mencionar que para la modificación de los valores entregados desde menu.cpp en las opciones (7) y (8), se deben modificar las [variables de entorno](#variables-de-entorno) necesarias.  
(no confundir opción (6) con (7), ya que la opción (6) no hace uso de estas).

## Funciones
En esta sección se detallan las funciones que posee el programa y ejemplos de ejecución de estas.    
Este programa cuenta con las siguientes funcionalidades:
  
  * **Detección de Palíndromos:** Identifica si una palabra o frase es un palíndromo.
  
  * **Contar Vocales:** Calcula el número de vocales en un texto dado.
  
  * **Contar Letras:** Determina la cantidad de letras en una frase.
  
  * **Promedio y Sumatoria:** Calcula el promedio y la sumatoria de un vector de números.
  
  * **Evaluación de Función:** Calcula el valor de una función matemática dada.

  * **Verificación de Usuario:** Comprueba la validez del usuario y la contraseña.

  * **Programa contador de palabras:** llama a un programa externo que permite el conteo de palabras sobre archivos de una carpeta.  
  Cuenta las palabras en los archivos de entrada, generando archivos de salida con los resultados.
  
  * **Conteo paralelo con threads:** llama a un programa externo que permite las mismas funcionalidades que en el contador de palabras, con la diferencia de que este proceso se llevará a cabo con una cantidad determinada de hilos.

  * **Creacion de indice:** llama a un programa externo que crea un indice de las palabras que se repiten en los archivos de procesar, siempre y cuando el proceso anterior __Conteo paralelo con threads__ fue llamado antes

  * **Analisis de performance:** llama a un programa externo que ejecuta tantas veces como especifique la variable de entorno __"REPEATS"__ el programa de conteo paralelo con una cierta cantidad de threads especificadas como una lista en otra variable de entorno (__"ARRAY_THREADS"__)

  * **Planificador:** llama a un programa externo que lee y asigna tareas a ejecutar dentro de un "core" y retornando el resultado de las operaciones dadas en un archivo de texto con el formato **"id;operacion;num1,num2"**

  * **Añadir un usuario :** A los usuarios de tipo Admin, le permite añadir usuarios, con la condicion de que estos no estean repetidos.  
  Para añadir un usuario general, sin acceso a funciones del Administrador, se debe ingresar en la parte de __"Rol: "__ el valor __Usuario__, en caso de querer agregar un Administrador nuevo dentro de la base de datos, se coloca __"Admin"__
  
  * **Lista de usuarios:** A los usuarios de tipo Admin, muestra a todos los usuarios que estan almacenados con el formato __"Usuario";"Contraseña";"Rol"__.
  
  * **Eliminar un usuario:** A los usuarios de tipo Admin, le permite eliminar a los usuarios que se especifiquen.

## Variables de entorno

* **RESULT_PATH** = Contiene la ubicacion donde los resultados se van a guardar. 

* **PROCESS_PATH** = Contiene la ubicacion de los archivos que se van a procesar.

* **CANT_THREADS** = Asigna la cantidad de hilos que se va a utilizar en la opcion (7).

* **MAP_PATH** = Contiene la ubicacion del archivo __map.txt__ que tiene organizados los elementos de __PROCESS_PATH__ con una id especifica.
  > __map.txt__ se crea durante la ejecucion de la opcion (7)

* **INDEX_PATH** = Contiene la ubicacion del archivo __inverted_index.INDEX__ que contiene todas las palabras, donde aparecen estas segun la id de __map.txt__ y cuantas estas tienen aparicion.

* **EXT_ARCHIVE** = Nos da la extencion del cual se va a guardar los archivos de la opcion (7).

* **STOP_PATH** = Ubicacion del archivo con las __stop words__ utilizadas.

* **TEMP_PATH** = Ubicacion en el cual se ubica los elementos temporales generados por la opcion (7) debido a la eliminacion de las stop words y no modificar el archivo original.

* **ARRAY_THREADS** = Arreglo con la cantidad de hilos que se van a ocupar en la opcion (9).
* **REPEATS** = Cantidad de veces que se va a repetir el conteo paralelo en la opcion (9).
* **STORE_DATA_PATH** = Ubicacion del archivo de texto con el formato **"cantidad_threads;tiempo_de_ejecucion"** con los tiempos de cada ejecucion.
* **GRAPHIC_PATH** = Ubicacion del grafico generado por la opcion (9) mostrando el tiempo de ejecucion de una cantidad de hilos contra otras.
* **PROCESS_CORE_PATH** = Ubicacion con las instrucciones a procesar de la opcion (10) para los cores.
* **CANT_CORES** = Cantidad de "cores" que se van a utilizar en la opcion (10).
* **RESULT_CORE_PATH** = Ubicacion con los resultados de las operaciones, mostrando el "core" que lo realizo.

## Atribucion
Durante la creación del proyecto se utilizó el archivo __stop_word.txt__ del repositorio [stop-words (Alir3z4)](https://github.com/Alir3z4/stop-words) que esta bajo la [licencia CC BY 4.0](https://creativecommons.org/licenses/by/4.0/).
Además de el repositorio [7506Condor1C2014 (nahuel36)](https://github.com/busiris2014/7506Condor1C2014) del cual se extrajeron los archivos para la ejecución de la opción (7).

# MultiTarea

## Descripcion
Se propuso crear un programa que desplegara un menú con diferentes opciones 
con las que el usuario pueda probar diferentes valores, desde identificar una
palabra palíndromo, hasta evaluar un número en una función específica, esta solución contempla el manejo correcto de los datos ingresados para evitar un resultado incorrecto.

## Requisitos
- 
  Para ejecutar este programa, necesitas tener un compilador de C++ instalado en tu sistema con al menos la versión 6.3.0. y estar en la carpeta principal "programaMenu".  
  El programa es compatible con sistemas Linux y también puede ejecutarse en Windows, siempre y cuando tengas instalado un subsistema Linux. 

  Para la lectura de archivos .env se descargó la librería dotenv-cpp, el cual debe ser añadido a la carpeta junto con el programa.

## Instalacion / Compilacion
* Para la instalación del programa basta con clonar el repositorio, y tambien clonar la [libreria dotenv-cpp](https://github.com/laserpants/dotenv-cpp.git) y añadirla a la carpeta __"external"__ junto con el resto, de lo contrario el .env con las variables de entorno no podran ser leidas correctamente. Asegurate de mantener todos los archivos en las carpetas correctas, en caso de no ejecutarse correctamente, verificar que la ubicación de cada archivo. 

* > Importante mencionar que se deben compilar 3 programas previamente, el programa principal (con make) y los programas que ejecutan la opción (6) , (7) y (8) (con "make -f MakefileC" , "make -f MakefileP" y "make -f MakefileI")

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

Importante mencionar que para la modificación de los valores entregados desde menu.cpp en las opciones (7) y (8), se deben modificar las variables de entorno necesarias.
(no confundir opción (6) con (7), ya que la opción (6) no hace uso de estas).

## Funciones
En esta sección se detallan las funciones que posee el programa y ejemplos de ejecución de estas.    
Este programa cuenta con las siguientes funcionalidades:
  
  * Detección de Palíndromos: Identifica si una palabra o frase es un palíndromo.
  
  * Contar Vocales: Calcula el número de vocales en un texto dado.
  
  * Contar Letras: Determina la cantidad de letras en una frase.
  
  * Promedio y Sumatoria: Calcula el promedio y la sumatoria de un vector de números.
  
  * Evaluación de Función: Calcula el valor de una función matemática dada.

  * Verificación de Usuario: Comprueba la validez del usuario y la contraseña.

  * Programa contador de palabras : llama a un programa externo que permite el conteo de palabras sobre archivos de una carpeta.  
  Cuenta las palabras en los archivos de entrada, generando archivos de salida con los resultados.
  
  * Conteo paralelo con threads : llama a un programa externo que permite las mismas funcionalidades que en el contador de palabras, con la diferencia de que este proceso se llevará a cabo con una cantidad determinada de hilos.

  * Creacion de indice: llama a un programa externo que crea un indice de las palabras que se repiten en los archivos de procesar, siempre y cuando el proceso anterior __Conteo paralelo con threads__ fue llamado antes

  * Añadir un usuario : A los usuarios de tipo Admin, le permite añadir usuarios, con la condicion de que estos no estean repetidos.  
  Para añadir un usuario general, sin acceso a funciones del Administrador, se debe ingresar en la parte de ___"Rol: "___ el valor ___Usuario___, en caso de querer agregar un Administrador nuevo dentro de la base de datos, se coloca ___"Admin"___
  
  * Lista de usuarios : A los usuarios de tipo Admin, muestra a todos los usuarios que estan almacenados con el formato ___"Usuario";"Contraseña";"Rol"___.
  
  * Eliminar un usuario : A los usuarios de tipo Admin, le permite eliminar a los usuarios que se especifiquen.

## Atribucion
Durante la creación del proyecto se utilizó el archivo __stop_word.txt__ del repositorio [stop-words (Alir3z4)](https://github.com/Alir3z4/stop-words) que esta bajo la [licencia CC BY 4.0](https://creativecommons.org/licenses/by/4.0/).
Además de el repositorio [7506Condor1C2014 (nahuel36)](https://github.com/busiris2014/7506Condor1C2014) del cual se extrajeron los archivos para la ejecución de la opción (7).
## Variables de entorno

RESULT_PATH= (explicar)
PROCESS_PATH= (explicar)
CANT_THREADS= (explicar)
MAP_PATH = 
INDEX_PATH= 
EXT_ARCHIVE =
STOP_PATH=
TEMP_PATH = 

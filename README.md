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

* > Importante mencionar que se deben compilar 2 programas previamente, el programa principal (con make) y el programa que ejecuta la opción (6) (con "make -f MakefileC")

## Ejecucion
En esta sección se detalla como ejecutar el programa junto con una descripción de los argumentos de lanzamiento.  

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

  * Añadir un usuario : A los usuarios de tipo Admin, le permite añadir usuarios, con la condicion de que estos no estean repetidos.  
  Para añadir un usuario general, sin acceso a funciones del Administrador, se debe ingresar en la parte de ___"Rol: "___ el valor ___Usuario___, en caso de querer agregar un Administrador nuevo dentro de la base de datos, se coloca ___"Admin"___
  
  * Lista de usuarios : A los usuarios de tipo Admin, muestra a todos los usuarios que estan almacenados con el formato ___"Usuario";"Contraseña";"Rol"___.
  
  * Eliminar un usuario : A los usuarios de tipo Admin, le permite eliminar a los usuarios que se especifiquen.
# RDPROC
###### Trabajo Práctico 1 de Sistemas Operativos I - FCEFyN - UNC.

# Integrantes:
  - Perez, Bruno Santiago
  - Ourthe, Nahuel Gastón

It's a UNIX software to see your computer's info.

# Para correr el programa

## Compilar desde código fuente

### Requisitos:
* gcc
* make
### Compilación
Para compilar se debe acceder a la carpeta donde se descargó el proyecto y ejecutar el comando `make`

### Ejecución
Se ejecuta corriendo:  `./rdproc`

### Opciones
Step A --> `./rdproc`  
Step B --> `./rdproc -s`
Step C --> `./rdproc -l [interval] [duration]`
Step D --> `./rdproc -p [pid]` o `./rdproc -f [pid]` o `./rdproc -t [pid]`

# Desarrollo

## Una breve introducción
El objetivo de este trabajo práctico fue entender la estructura del kernel de Linux.
Para esto se investigó la estructura del directorio _/proc_ y a partir de este directorio se construyó un programa en C que imprimiera información útil del sistema y de procesos en particular.

## El sistema de archivos _/proc_
El sistema de archivos _/proc_ contiene un sistema de archivos imaginario o virtual. 
Este no existe físicamente en disco, sino que el núcleo lo crea en memoria. 
Se utiliza para ofrecer información relacionada con el sistema (originalmente acerca de procesos, de aquí su nombre).

## Desarrollo del práctico
Convenientemente la consigna estaba separada en 4 pasos, lo cual fue fácil dividir las tareas entre nosotros.
Como paso inicial creamos un repositorio en GitHub ([link](https://github.com/nourthe/os1-rdproc)).
Luego se procedió a crear una template en el archivo main que pudiera interpretar los argumentos pedidos en las consignas y llamar a funciones que no hacían nada. Para esto fue muy útil la función getopt_long.

Luego se investigó cómo hacer un archivo _Makefile_ para no tener todo el código en un sólo archivo y poder trabajar paralelamente de a dos sin tener conflictos de arhivos.

La parte más importante de la separación de archivos fue hacer un archivo que tuviera todas las funciones de lectura de otros archivos (_rdfile.h_ y _rdfile.c_).

Se priorizó utilizar siempre buffers externos y utilizar funciones seguras (es decir chequear que el archivo a leer "entre" en el buffer utilizado) y no hacer llamadas _malloc_ para no tener leaks de memoria ni lidiar con la responsabilidad de liberar memoria.

Finalemente se procedió a completar los pasos.


## Respuestas
- Cuáles son los tipos de file descriptors que podemos encontrar en /proc/<id>/fd?

    
- Qué diferencia hay entre hard y soft limits?
El hard limit es el límite que un usuario nunca puede superar. 

El limite soft es un límite cuyo objetivo es actuar como una advertencia. Le dice al usuario y el administrador de sistema que se está acercando a un límite
pelogroso. Los usuarios pueden superar este límite.

Ambos límites son configurables.

- Suponiendo que un usuario está ejecutando el proceso pid 1212, es válida la ejecución del siguiente comando desde una terminal nueva? % echo “Hello, world.” >> /proc/1212/fd/1
Sí, totalmente. Lo que hará eso es poner en el fd stdout del proceso 1212 "Hello, world." y se mostrará en pantalla ese texto.
A modo de ejemplo se corrió el programa _rdproc -l 15 1500_ y mediante el comando `ps aux | grep rdproc` se determinó el pid del proceso.
Luego se ejecutó en otra terminal `echo "\n ----- Probando los File Descriptors ---- \n " >> /proc/23828/fd/1`
y se verificó que en la terminal donde se corrió el programa inicial se visualizó el texto _----- Probando los File Descriptors ----_
![Prueba fd](readmeAssets/ejemplo_fd.png?raw=true "Probando del fd stdout")


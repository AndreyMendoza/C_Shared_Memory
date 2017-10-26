**************************************
# C_Shared_Memory - Tema Principal
Simulación de paginación y segmentación haciendo uso de memoria compartida y semáforos.

**************************************

Instituto Tecnológico de Costa Rica
Sede Central de Cartago
Escuela de Ingeniería en Computación
Sistemas Operativos
“Proyecto2 - Memoria Compartida”
Estudiantes:
	Andrey Mendoza Fernández - 2015082908
	Armando López Cordero - 2015125414
               	
Prof: Ing. Erika Marín Schumann
Periodo: 2017 - II Semestre
Fecha de Entrega: 25 de octubre del 2017

**************************************

# --> COMPILACIÓN <--

Respecto a la compilación del proyecto se debe tener en cuenta que es necesario tener instalado Cmake & Make en el ordenador, esto con la finalidad de poder generar el makefile y otros archivos necesarios para la ejecución del programa. A continuación se presenta una sugerencia de instalación con los respectivos pasos que se deben llevar a cabo para instalar dichos complementos.

sudo apt-get install build-essential
wget http://www.cmake.org/files/v3.2/cmake-3.2.2.tar.gz
tar xf cmake-3.2.2.tar.gz 
cd cmake-3.2.2
./configure 
make
sudo apt-get install checkinstall
sudo checkinstall

Una vez completados estos pasos ya se contará con los complementos necesarios para ejecutar el proyecto desde la terminal, no obstante, primero se debe contar con una carpeta la cual almacenará los ejecutables de la aplicación, para ello hay que dirigirse a la ubicación del proyecto e ingresar el siguiente comando para crear dicha carpeta <mkdir Bin>. Luego hay que ubicarse dentro de la carpeta recién creada (Bin) y posteriormente realizar <cmake ..> dentro de la misma.
Llegando a este punto bastará con ingresar el comando <make> con el cual el programa estará compilado y por ende permitirá la ejecución de la aplicación.


**************************************
#--> EJECUCIÓN <--
La ejecución del proyecto se debe llevar a cabo una vez que el mismo se encuentra compilado correctamente, sólo bastará con ubicarse dentro de la carpeta Bin creada con el <mkdir Bin>, note que si ya existe dicha carpeta sólo bastará con dirigirse dentro. 
Una vez hecho esto se deberán ingresar los parámetros que se van a enviar desde consola y por supuesto el nombre de la aplicación que se está intentando ejecutar. En este caso se cuenta con el proyecto llamado SharedMemory dentro del cual se deberá ejecutar el archivo main.c que contiene el menú de opciones que se ajusta a los parámetros pasados desde consola.
A continuación se muestran algunos ejemplos de ejecución y su respectiva explicación.

********************
# Inicializador
Tal como la sección lo indica, el inicializador es el encargado de la creación de todos los recursos necesarios para la ejecución de los otros módulos del sistema. Específicamente este inicializa las memorias compartidas con las que trabaja el productor y espía. Además, crea los semáforos para restringir el acceso a la región crítica.
Para la ejecución de este subprograma se debe ingresar además del nombre de módulo, el tamaño con que se debe crear la memoria compartida, es decir, la cantidad de celdas/bloques que contendrá la memoria. Entonces, un ejemplo claro de la ejecución sería:
	./inic 50

********************
# Productor
Tal como la sección lo indica, el productor es el encargado de la creación de todos los hilos que realizan el proceso de asignación en memoria y de registrar los diferentes estados que tienen a lo largo de su ejecución. Específicamente este inicializa la memoria compartida con las estructuras que se desean trabajar (paginación / segmentación), además asigna valores a dichas estructuras para que posteriormente los hilos hagan uso de los datos para realizar recorridos en memoria, ya sea para asignarse un espacio o para liberarlo.
Otro parte importante de este módulo, es que después de inicializar la memoria con las estructuras base, el productor pasa a un ciclo infinito que se encarga de estar generando hilos cada 30-60 segundos y asigna al hilo creado la función de buscar espacio en memoria con sus propias configuraciones.
Para la ejecución de este subprograma se debe ingresar además del nombre de módulo, el modo con que se debe trabajar sobre la memoria compartida, es decir, la segmentación o paginación. Entonces, un ejemplo claro de la ejecución sería:
	./prod -s (modo segmentación)
	./prod -p (modo paginación)

********************
# Espía
Tal como la sección lo indica, el espía es el encargado de brindar información al usuario, que en este caso sería el estado de los procesos y el estado en que se encuentra la memoria compartida en un determinado momento.
Para la ejecución de este subprograma se debe ingresar además del nombre de módulo, el modo de espiar con que se desea correr, es decir, mem (para espiar la memoria) o proc (para espiar los procesos). Entonces, un ejemplo claro de la ejecución sería:
	./espia mem (espia la memoria)
	./espia proc (espia los procesos)

********************
#Finalizador
Este módulo se encarga de finalizar y liberar todos los recursos que el inicializador y productor crearon, en este caso serían las dos memorias compartidas, los hilos creados y los semáforos para el control de acceso a las regiones críticas. Entonces, un ejemplo claro de la ejecución sería:
	./fin



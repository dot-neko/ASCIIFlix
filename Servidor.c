/*
* Javier Abellan, 20 Jun 2000
*
* Programa Servidor de socket INET, como ejemplo de utilizacion de las
* funciones de sockets.
*/
#include <Socket_Servidor.h>
#include <Socket.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>

main ()
{
	/*
	* Descriptores de socket servidor y de socket con el cliente
	*/
	int Socket_Servidor;
	int Socket_Cliente;
	char Cadena[100];

	/*
	* Se abre el socket servidor, con el servicio "cpp_java" dado de
	* alta en /etc/services.
	*/
	Socket_Servidor = Abre_Socket_Inet ("cpp_java");
	if (Socket_Servidor == -1)
	{
		printf ("No se puede abrir socket servidor\n");
		exit (-1);
	}
	printf ("Socket servidor abierto.\n");
	/*
	* Se espera un cliente que quiera conectarse
	*/
	Socket_Cliente = Acepta_Conexion_Cliente (Socket_Servidor);
	if (Socket_Servidor == -1)
	{
		printf ("No se puede abrir socket de cliente\n");
		exit (-1);
	}
	printf ("Socket Cliente abierto.\n");
	/*
	* Se lee la informacion del cliente, suponiendo que va a enviar 
	* 5 caracteres.
	*/
	Lee_Socket (Socket_Cliente, Cadena, 68);

	/*
	* Se escribe en pantalla la informacion que se ha recibido del
	* cliente
	*/
	printf ("Soy Servior, he recibido : %s\n", Cadena);

	/*
	* Se prepara una cadena de texto para enviar al cliente. La longitud
	* de la cadena es 5 letras + \0 al final de la cadena = 6 caracteres
	*/
	strcpy (Cadena, "Adios");
	FILE* file = fopen("/server/catalog/sw6_trailer.txt", "r");
    char line[68]; 		//Ancho máximo del frame
    int frameHeight = 13; 	//Altura del frame
    int frameDuration = 0;	//Duracion en segundos del frame
    while(1){
    	fgets(line, sizeof(line), file);
    	frameDuration= atoi(line);
    	for (int i = 0; i < frameHeight ; ++i)
		{
			fgets(line, sizeof(line), file);
			printf("%s\n", line );
			Escribe_Socket (Socket_Cliente, line, 68);
		}
		sleep(frameDuration);
		system("clear");
    }
	
	Escribe_Socket (Socket_Cliente, Cadena, 68);

	/*Preparar estructura para leer por cada fila del documento
	* Son 13 filas por frame, y luego tiene que interpretar de la
	* primera linea los segundos que tiene que dejar estático el 
	* frame completo*/

	/*
	* Se cierran los sockets
	*/
	close (Socket_Cliente);
	close (Socket_Servidor);
}

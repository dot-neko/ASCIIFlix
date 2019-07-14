/*
* Javier Abellan, 20 Jun 2000
*
* Programa Cliente de un socket INET, como ejemplo de utilizacion
* de las funciones de sockets
*/
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include <Socket_Cliente.h>
#include <Socket.h>
#define CHARS 100
#define FRAMEHEIGHT 13
int main (int argc, char *argv[])
{
	if(argc!=2) 
	{
		printf("Ha olvidado ingresar una película.\n"); 
		exit(1);
	}
	/*
	* Descriptor del socket y buffer para datos
	*/
	int Socket_Con_Servidor;
	char cadena_multiuso[100];
	int frameHeight = FRAMEHEIGHT;
	float frameDuration = 0.0f;
	int moviePlay = 1;
	/*
	* Se abre la conexion con el servidor, pasando el nombre del ordenador
	* y el servicio solicitado.
	* "localhost" corresponde al nombre del mismo ordenador en el que
	* estamos corriendo. Esta dado de alta en /etc/hosts
	* "cpp_java" es un servicio dado de alta en /etc/services
	*/
	Socket_Con_Servidor = Abre_Conexion_Inet ("pc1", "cpp_java");
	if (Socket_Con_Servidor == 1)
	{
		printf ("No puedo establecer conexion con el servidor\n");
		exit (-1);
	}
	/*Envio peticion al servidor*/
	strcpy (cadena_multiuso, argv[1]);
	Escribe_Socket (Socket_Con_Servidor, cadena_multiuso, CHARS);

	do{
		system("clear");
		Lee_Socket (Socket_Con_Servidor, cadena_multiuso, CHARS);
		frameDuration= atoi(cadena_multiuso);
		for (int i = 0; i < frameHeight; ++i)
		{
			Lee_Socket (Socket_Con_Servidor, cadena_multiuso, CHARS);
			printf ("%s\n", cadena_multiuso);
		}
		sleep((frameDuration+10)/10);
		if (frameDuration==0)
		{
			moviePlay=0;
		}
	} while(moviePlay);

	printf ("SE TERMINO LA PELICULA\n");
	/*
	* Se cierra el socket con el servidor
	*/
	close (Socket_Con_Servidor);

}

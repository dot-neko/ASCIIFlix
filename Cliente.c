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

main ()
{
	/*
	* Descriptor del socket y buffer para datos
	*/
	int Socket_Con_Servidor;
	char Cadena[100];

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

	/*
	* Se prepara una cadena con 5 caracteres y se envia, 4 letras mas
	* el \0 que indica fin de cadena en C
	*/
	strcpy (Cadena, "PLAY");
	Escribe_Socket (Socket_Con_Servidor, Cadena, 68);

	/*
	* Se lee la informacion enviada por el servidor, que se supone es
	* una cadena de 6 caracteres.
	*/
	
	int frameHeight = 13;
	int frameDuration = 0;
	do{
		Lee_Socket (Socket_Con_Servidor, Cadena, 70);
		frameDuration= atoi(Cadena);
		for (int i = 0; i < frameHeight; ++i)
		{
			Lee_Socket (Socket_Con_Servidor, Cadena, 70);
			printf ("%s\n", Cadena);
		}
		usleep((frameDuration+1)*1000);
		system("clear");
	} while(Cadena!=NULL);

	/*
	* Se escribe en pantalla la informacion recibida del servidor
	*/

	/*
	* Se cierra el socket con el servidor
	*/
	close (Socket_Con_Servidor);
}

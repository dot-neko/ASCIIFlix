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
#define CHARS 100
main ()
{
	/*
	* Descriptores de socket servidor y de socket con el cliente
	*/
	int Socket_Servidor;
	int Socket_Cliente;
	char Cadena_lectura[100];

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
	printf ("Socket Cliente aceptado.\n");
	/*
	* Se lee la informacion del cliente, suponiendo que va a enviar 
	* 5 caracteres.
	*/
	Lee_Socket (Socket_Cliente, Cadena_lectura, 68);

	/*
	* Se escribe en pantalla la informacion que se ha recibido del
	* cliente
	*/
	printf ("Soy Servior, he recibido : %s\n", Cadena_lectura);

	/*Preparar estructura para leer por cada fila del documento
	* Son 13 filas por frame, y luego tiene que interpretar de la
	* primera linea los segundos que tiene que dejar estático el 
	* frame completo*/

	strcpy (Cadena_lectura, "Adios");
	FILE *filep;
	if ((filep = fopen("server/catalog/sw6_trailer.txt", "r")) == NULL)
	{
		printf("No se pudo abrir el archivo");
		exit(1);
	}
    	char line[CHARS]; 		//Ancho máximo del frame
    	char line_transf[CHARS]; 	//Frame trasmitido
    	int frameHeight = 13; 	//Altura del frame
    	int frameDuration = 0;	//Duracion en segundos del frame

	while(!feof(filep)){
		if (fgets(line, CHARS, filep)!=NULL)
		{
			frameDuration= atoi(line);
			printf("Se envian %d\n",frameDuration);
			Escribe_Socket (Socket_Cliente, line, CHARS);	//Envia dato de segundos del frame
		}
		else
		{
			printf("Error en frame\n");
			sprintf(line,"");
			Escribe_Socket (Socket_Cliente, line, CHARS);
			exit(1);
		}
		sleep(1);
		printf("TRANSMITIENDO...\n");
		/*Lee_Socket (Socket_Cliente, Cadena_lectura, 68);*/
		for (int i = 0; i < frameHeight ; ++i)
		{

			if (fgets(line, CHARS, filep)!=NULL)
			{
				Escribe_Socket (Socket_Cliente, line, CHARS);
			}
			else
			{
				sprintf(line,"");
				printf("Lei un null");
				Escribe_Socket (Socket_Cliente, line, CHARS);
				exit(1);
			}
		}
		sleep((frameDuration+1)/10);
    }



	/*
	* Se cierran los sockets
	*/
	close (Socket_Cliente);
	close (Socket_Servidor);
}

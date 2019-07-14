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
#define FRAMEHEIGHT 13
#define TIME_MULTIPLIER 1.3
main ()
{
	/*
	* Descriptores de socket servidor y de socket con el cliente
	*/
	int Socket_Servidor;
	int Socket_Cliente;
	char cadena_recibida[100];
	char movie_path[100];
	char line[CHARS]; 				//Ancho máximo del frame
	char line_transf[CHARS]; 		//Frame trasmitido
	int frameHeight = FRAMEHEIGHT; 	//Altura del frame
	float frameDuration = 0.0f;		//Duracion en segundos del frame
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
	Lee_Socket (Socket_Cliente, cadena_recibida, 68);

	/*
	* Se escribe en pantalla la informacion que se ha recibido del
	* cliente
	*/
	printf ("Soy Servior, he recibido : %s\n", cadena_recibida);

	

	sprintf(movie_path,"server/catalog/%s.txt",cadena_recibida);
	FILE *filep;
	if ((filep = fopen(movie_path, "r")) == NULL)
	{
		printf("No se pudo encontrar la película solicitada.\n");
		sprintf(line,"");
		Escribe_Socket (Socket_Cliente, line, CHARS);
		exit(1);
	}
	/*Preparar estructura para leer por cada fila del documento
	* Son 13 filas por frame, y luego tiene que interpretar de la
	* primera linea los segundos que tiene que dejar estático el 
	* frame completo*/


	while(!feof(filep)){
		if (fgets(line, CHARS, filep)!=NULL)
		{
			frameDuration= atoi(line)* TIME_MULTIPLIER;
			printf("Se envian %4.2f\n",frameDuration);
			Escribe_Socket (Socket_Cliente, line, CHARS);	//Envia dato de segundos del frame
		}
		else
		{
			printf("Error en frame\n");
			sprintf(line,"");
			Escribe_Socket (Socket_Cliente, line, CHARS);
			exit(1);
		}
		printf("TRANSMITIENDO...\n");
		for (int i = 0; i < frameHeight ; ++i)
		{

			if (fgets(line, CHARS, filep)!=NULL)
			{
				Escribe_Socket (Socket_Cliente, line, CHARS);
			}
			else
			{
				sprintf(line,"");
				printf("Lei un null. Fin de transmision.\n");
				Escribe_Socket (Socket_Cliente, line, CHARS);
				exit(1);
			}
		}
		sleep((frameDuration+2)/10);
    }

	/*
	* Se cierran los sockets
	*/
	close (Socket_Cliente);
	close (Socket_Servidor);
}

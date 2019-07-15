#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>

#include <Socket_Cliente.h>
#include <Socket.h>
#define CHARS 100
#define FRAMEHEIGHT 13

void handler(int signum);

int main (int argc, char *argv[])
{
	if(argc!=2) 
	{
		printf("Ha olvidado ingresar una película.\n"); 
		exit(1);
	}

	int Socket_Con_Servidor;
	char cadena_multiuso[CHARS];
	char ch_arr[FRAMEHEIGHT][CHARS]={"","","","","","","","","","","","",""};
	
	int frameHeight = FRAMEHEIGHT;
	float frameDuration = 0.0f;
	int moviePlay = 1;
	signal(SIGINT,handler);
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
	/*Envio peticion al servidor según parámetros*/
	strcpy (cadena_multiuso, argv[1]);
	Escribe_Socket (Socket_Con_Servidor, cadena_multiuso, CHARS);

	do{

		//Lee la primera línea del frame. Toma info de duración en pantalla
		Lee_Socket (Socket_Con_Servidor, cadena_multiuso, CHARS);
		frameDuration= atoi(cadena_multiuso);

		//Carga los datos del socket en un buffer intermedio
		for (int i = 0; i < frameHeight; ++i)
		{
			Lee_Socket (Socket_Con_Servidor, cadena_multiuso, CHARS);
			strcpy(ch_arr[i], cadena_multiuso);
		}
		system("clear");

		//Imprime el buffer en pantalla. Esto optimiza la visualización final.
		for (int i = 0; i < frameHeight; ++i)
		{
			printf ("%s\n", ch_arr+i);
		}
		
		//Mantiene en pantalla el tiempo necesario la impresión
		sleep((frameDuration+6)/10);
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

void handler (int signum){
	printf("\nRecibi la señal sigint\n");
	close(Socket_Con_Servidor);
}


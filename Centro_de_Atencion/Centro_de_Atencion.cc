/* Modelo MM1 - Un Servidor, Una Cola  */

#include <stdio.h>
#include <stdlib.h> 
#include "simlib.c"
// Definición eventos
#define Inicio_dia        1  /*  Evento 1: Inicio día           */
#define Fin_día           2  /*  Evento 2: Fin día          */
#define Arribo_llamadas   3 /*   Evento 3: arribo llamadas*/
#define Falla_General     4 /*Evento 4 :Falla General*/
#define Fin_llamada       5 /*Evento 5: fin llamada*/

// Definición servidores y colas
#define Servidor          1/* Lista 1: Servidor*/
#define Servidor_Operador_1 2
#define Servidor_Operador_2 3
#define Servidor_Operador_3 4
#define Servidor_Operador_4 5
#define Cola_llamadas     6  /* Lista 2: Cola */
#define Cola_Operador_1   7
#define Cola_Operador_2   8
#define Cola_Operador_3   9
#define Cola_Operador_4   10
// Definición sampst para demoras
#define Demora_cola_llamadas       1  /* Sampst 1: Demora en Cola            */
#define Demora_Consulta            2 /*Sampst 2 : Demora de toda consulta*/

/* Declaraci¢n de variables */

float media_interllamadas,tiempo_activo, tiempo_inactivo,min_consulta_breve, max_consulta_breve, media_otros, desv_estandar_otros, probabilidad_falla, probabilidad_llamada, probabilidad_operador_ocupado,probabilidad_operador_libre,cant_fallas,cant_días, OperadorAtendio;

// Definición posiciones transfer
#define Tiempo_Evento   1
#define Tipo_Evento 2
#define Tipo_Llamada  3
#define Operador      4

/* Rutinas */
int main();
void inicializa(void);
void Rutina_inicio_día(tiempo_inactivo);
void Rutina_fin_día(void);
void Rutina_arribo_llamada(void);
void Rutina_Falla_General();
void Rutina_Fin_llamada();
void estadísticos(void);


int main()  /* Main function. */
{
	/* Apertura de Archivos que sean necesarios */

	media_interllamadas = 3.7;
	tiempo_activo = 720;
	tiempo_inactivo = 720;
	min_consulta_breve = 2;
	max_consulta_breve = 5;
	media_otros = 15;
	desv_estandar_otros = 3;
	probabilidad_falla = 0.2;
	cant_días = 5;
	

	/* Initializar Simlib */
	init_simlib();



	/* Initializar el Sistema */
	inicializa();

	/* Ejecutar la simulaci¢n. */



	while (sim_time < 5400)
	{

		/* Determinar pr¢ximo Evento */
		timing();

		/* Invocar el evento correcto. */

		switch( next_event_type )
		{
			case Inicio_día:
				Rutina_inicio_día()
				break;
			case Fin_día:
				Rutina_fin_día();
				break;
			case Arribo_llamadas:
				Rutina_arribo_llamada();
				break;
			case Falla_General:
				Rutina_Falla_General();
				break;
			case Fin_llamada:
				Rutina_Fin_llamada();
				break;
				default;
        }
	}

	/* Llamada al Reporte para mostrar los resultados */
	reporte();
	//getchar();
	system("pause");
}


void inicializa(void)  /* Inicializar el Sistema */
{
	/* Se carga el primer inicio día */
	transfer[Tiempo_Evento] = sim_time+tiempo_inactivo;
	transfer[Tipo_Evento] = Inicio_dia;
	
	list_file(INCREASING,LIST_EVENT);
	// Se Carga la primera falla general
	transfer[Tiempo_Evento] = sim_time + uniform(6, 7, Falla_General)
	transfer[Tipo_Evento] = Falla_General;
	list_file(INCREASING, LIST_EVENT);
}
Rutina_inicio_día(tiempo_inactivo)
	{
		transfer[Tiempo_Evento] = tiempo_inactivo;
		transfer[Tipo_Evento] = Inicio_dia;
		// Se pronostica el primer arribo de llamadas
		transfer[Tiempo_Evento] = sim_time + expon(media_interllamadas, Arribo_llamadas);
		transfer[Tiempo_Evento] = Arribo_llamadas;
		list_file(INCREASING, LIST_EVENT);
		list_file[INCREASING, LIST_EVENT]


	}
void Rutina_arribo_llamada(void)  /* Evento Arribo */
{
	/* Determinar pr¢ximo arribo de llamada y cargar en Lista de Eventos */

	transfer[Tiempo_Evento] = sim_time + expon(media_interllamadas,Arribo_llamadas);
	transfer[Tiempo_Evento] = Arribo_llamadas;
	list_file(INCREASING,LIST_EVENT);

	/* Chequear si el Servidor est  desocupado */

	if (list_size[Servidor_Operador_1] == 0)
	{


	   /* Si está desocupado ocuparlo y generar la partida */

	   list_file(FIRST, Servidor_Operador_1);
	}
	else if (list_size[Servidor_Operador_2]==0)
		{
			list_file(FIRST, Servidor_Operador_2);
		}
	else if (list_size[Servidor_Operador_3]==0)
		{
			list_file(FIRST, Servidor_Operador_3)
		}
	else
	{
		list_file(FIRST, Servidor_Operador_4)
	}
	   sampst(0.0, Demora_cola_llamadas);
	   probabilidad_llamada = lcgrand(Arribo_llamadas);
	   if (probabilidad_llamada <= 0.35)
	   {
		   transfer[Tiempo_Evento] = sim_time + (min_consulta_breve, Max_Consulta_breve, Arribo_llamadas);
		   transfer[Tipo_Llamada]=1
	   }
	   else
	   {
		   transfer[Tiempo_Evento] = sim_time + (media_otros, Arribo_llamadas);
		   transfer[Tipo_Llamada] = 2;
	   }
	   if (list_size[Servidor_Operador_1] > 0 && list_size[Servidor_Operador_2] > 0 && list_size[Servidor_Operador_3] > 0 && list_size[_Operador_4] > 0)
			 {
				  probabilidad_operador_ocupado = lcgrand(11);
				  // Acá se debería determinar lo que hace cada cliente si todo operador está ocupado
				  if (probabilidad_operador_ocupado >=0,6)
					{
					  list_file(Cola_llamadas)
					}
			 }
	   else
	   {
		   if (list_size[Cola_Operador_1] = 0 && list_size[Cola_Operador_2] == 0 && list_size[Cola_Operador_3] == 0 && list_size[Cola_Operador_4] == 0)
			   probabilidad_operador_libre = lcgrand(Arribo_llamadas);
		   if (probabilidad_operador_libre <= 0,25)
			 {
			   transfer[Operador]=1
			 }
		   else if (probabilidad_operador_libre <=0.5)
		   {
			   transfer[Operador]=2
		   }
		   else if (probabilidad_operador_libre <= 0,75)
		   {
			   transfer[Operador]=3
		   }
		   else
		   {
			   transfer[Operador]=4
		   }
	   }
	   transfer[Tipo_Evento] = Fin_llamada;
	   list_file(INCREASING,LIST_EVENT);

	

	else
	{

	   /* Va a cola */

	   transfer[1] = sim_time;
	   list_file(LAST, Cola_llamadas);
	}
}


void Rutina_Fin_llamada(void)  /* Evento Partida */
{
	int TipoLlamada = transfer[Tipo_Llamada];
	int OperadorAtendio=transfer[Operador]
	/* Desocupar el Servidor */

	list_remove(FIRST, OperadorAtendio);

	/* Ver si hay trabajos en cola */

	if (list_size[Cola_llamadas] > 0)
	{

	   /* Sacar el primero de la cola y actualizar Demoras */

	   list_remove(FIRST, Cola);
	   sampst(sim_time - transfer[1], Demora_Consulta);

	   /* Cargar en el Servidor y generar la partida */
	   list_file(FIRST, O);
	   if (TipoLlamada==1)
		{
			transfer[Tiempo_Evento] = sim_time + uniform(min_consulta_breve, max_consulta_breve, Fin_llamada);
			transfer[Tipo_Llamada]=1
	   }
	   else
	   {
		   transfer[Tiempo_Evento] = sim_time + expon(media_otros, Fin_llamada);
		   transfer[Tipo_Llamada]=2
	   }
	   transfer[Tipo_Evento] = Fin_llamada;
	   transfer[Operador] = OperadorAtendio;
	   list_file(INCREASING,LIST_EVENT);
	}
}
void Rutina_Falla_General()
	{
		cant_fallas++
		if (list_size[Servidor_Operador_1] > 0)
			{
				// Desocupar servidor
				list_remove(FIRST, Servidor_Operador_1)
			}
		else if (list_size[Servidor_Operador_2] > 0)
			{
				list_remove(FIRST, Servidor_Operador_2)
			}
		else if (list_size[Servidor_Operador_3] > 0)
			{
				list_remove(FIRST, Servidor_Operador_3)
			}
		else
			{
				list_remove(FIRST, Servidor_Operador_4)
			}
			// Cancelar Evento
			event_cancel(Fin_llamada)

			// Llevarlo a la cola
			transfer[1] = sim_time;
			list_file(Cola_llamadas)
	}
void Rutina_fin_día()
	{
		//Generar un nuevo inicio de día
		transfer[Tiempo_Evento] = sim_time + tiempo_inactivo;
		list_file(INCREASING, LIST_EVENT)
	}
void estadisticos(void)  /* Generar Reporte de la Simulaci¢n */
{

	/* Mostrar Par metros de Entrada */

	/* -------- Por pantalla -------- */

	printf("Comienza reporte \n\n");

	///*Demora media  en Cola de llamadas.
	sampst(0.0, -Demora_cola_llamadas);
	printf("\nDemora en cola: %f \n ", transfer[1]);

	// Numero medio en la cola de llamadas
	filest(Cola_llamadas);
	printf("\nNúmero Promedio en Cola de llamadas: %f \n ", transfer[1]);

	// Demora promedio de las consultas
	sampst(0, 0 - Demora_Consulta);
	printf("\nDemora consulta: %f \n ", transfer[1]);

	// Cantidad Fallas
	printf("\nCantidad fallas: %f \n ", transfer[1]);

	//Utilización operador 1
	filest(Cola_Operador_1);
	printf("\nUtilizaci¢n Operador  1: %f \n ", transfer[1]);
	// Utilización operador 2
	filest(Cola_Operador_2);
	printf("\nUtilizaci¢n Operador 2: %f \n ", transfer[1]);
	filest(Cola_Operador_3);
	printf("\nUtilizaci¢n Operador 3 : %f \n ", transfer[1]);
	filest(Cola_Operador_4);
	printf("\nUtilizaci¢n Operador 4 : %f \n ", transfer[1]);
}






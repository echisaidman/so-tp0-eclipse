#include "client.h"
#include <stdbool.h>
#include "utils.h"
#include <commons/collections/list.h>
#include <commons/string.h>
#include <readline/readline.h>
// #include "shared_utils.h"

int main(void)
{
	//probando si funciona
	int conexion;

	/* ---------------- LOGGING ---------------- */

	t_log *logger = log_create("cfg/log.log", "Cliente", true, LOG_LEVEL_DEBUG);
	log_info(logger, "Cliente comenzando...");

	/* ---------------- ARCHIVOS DE CONFIGURACION ---------------- */

	t_config *config = config_create("cfg/cliente.config");
	char *ip = config_get_string_value(config, "IP");
	char *puerto = config_get_string_value(config, "PUERTO");
	char *clave = config_get_string_value(config, "CLAVE");

	log_info(logger, "{ IP: %s, Puerto: %s, Clave: %s }", ip, puerto, clave);

	/* ---------------- LEER DE CONSOLA ---------------- */

	t_list *listaLeidos = leer_consola(logger);

	/*---------------------------------------------------PARTE 3-------------------------------------------------------------*/

	// ADVERTENCIA: Antes de continuar, tenemos que asegurarnos que el servidor esté corriendo para poder conectarnos a él
	// ????

	// Creamos una conexión hacia el servidor
	conexion = crear_conexion(ip, puerto);

	// Enviamos al servidor el valor de CLAVE como mensaje
	enviar_mensaje(clave, conexion);

	// Armamos y enviamos el paquete
	crear_enviar_paquete(conexion, listaLeidos);
	// simpleListDestroyer(listaLeidos); // TODO

	log_info(logger, "Cliente finalizando...");
	terminar_programa(conexion, logger, config);
}

t_list *leer_consola(t_log *logger)
{
	t_list *lista = list_create();

	char *leido = readline("> ");
	while (!string_equals_ignore_case(leido, ""))
	{
		log_debug(logger, "'%s' ingresado por consola", leido);
		list_add(lista, leido);
		leido = readline("> ");
	}
	free(leido); // El ultimo valor es el vacio "", y hay que freearlo

	return lista;
}

void crear_enviar_paquete(int conexion, t_list *listaLeidos)
{
	t_paquete *paquete = crear_paquete();

	t_list_iterator *iterator = list_iterator_create(listaLeidos);
	while (list_iterator_has_next(iterator))
	{
		char *leido = (char *)list_iterator_next(iterator);
		agregar_a_paquete(paquete, leido, strlen(leido) + 1);
	}
	list_iterator_destroy(iterator);

	enviar_paquete(paquete, conexion);

	eliminar_paquete(paquete);
}

void terminar_programa(int conexion, t_log *logger, t_config *config)
{
	liberar_conexion(conexion);
	log_destroy(logger);
	config_destroy(config);
}

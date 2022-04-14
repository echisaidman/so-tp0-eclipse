#ifndef CLIENT_H_
#define CLIENT_H_

#include <commons/log.h>
#include <commons/config.h>
#include <commons/collections/list.h>

t_list *leer_consola(t_log *);
void crear_enviar_paquete(int, t_list *);
void terminar_programa(int, t_log *, t_config *);

#endif

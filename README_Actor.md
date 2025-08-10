# ActorSupervisorErlang

Este proyecto implementa un supervisor básico en Erlang que gestiona dos actores trabajadores (`worker_actor`). El supervisor monitorea la vida de sus trabajadores y los reinicia automáticamente en caso de fallo. Permite enviar tareas a los trabajadores y recibir resultados.

## Descripción

El sistema consta de tres módulos principales:

- **actor_supervisor**: supervisa y reinicia los actores trabajadores, captura terminaciones de proceso con `trap_exit`.
- **worker_actor**: actor que procesa mensajes para realizar operaciones (como suma) o simular fallos.
- **main**: módulo de ejemplo que inicia el supervisor, envía tareas, simula fallos y muestra resultados.

Este proyecto ejemplifica el modelo de actores en Erlang y el patrón supervisor para tolerancia a fallos.

## Requisitos

- Erlang/OTP 23 o superior.
- Entorno con shell de Erlang para compilar y ejecutar.

## Instalación

Compila el proyecto ejecutando en la terminal dentro de la carpeta del proyecto:

```bash
erl -make

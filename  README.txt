==============================
TAREA 2 - ESTRUCTURA DE DATOS
==============================

NOMBRE DEL JUEGO: Apocalipsis USM

INTEGRANTES:
-------------
- Renato Osorio
- Domingo [Apellido de Domingo]

ROLES:
-------
Ambos trabajamos en conjunto en las diferentes partes del proyecto, dividiendo las tareas de forma equilibrada.

- Renato: Codificación principal, diseño del árbol del mapa, narrativa del juego, sistema de combate, estructura de enemigos y eventos.
- Domingo: Lógica para cargar y procesar el archivo .map, implementación del árbol ternario, funciones del jugador, mejoras y validaciones del mapa.

INSTRUCCIONES PARA COMPILAR Y EJECUTAR:
----------------------------------------
1. Abre la terminal en la carpeta del proyecto.
2. Compila con:
   g++ tarea2.cpp -o tarea2 -Wall
3. Ejecuta el juego con:
   ./tarea2

Asegúrate de que el archivo `data.map` esté en la misma carpeta que el ejecutable.

¿QUÉ TIENE EL ARCHIVO `data.map`?
-----------------------------------
Es nuestro propio mundo del juego Apocalipsis USM. Contiene:

- Las habitaciones por las que el jugador pasa (como Biblioteca, NOAC, Cafetería…).
- Las conexiones que forman un árbol ternario válido.
- 5 enemigos personalizados con nombre, stats y probabilidad.
- 3 eventos originales donde el jugador puede ganar vida, armas o cometer errores.
- Un sistema de mejoras después de cada combate.

¿POR QUÉ MERECE LOS 10 PUNTOS EXTRA?
-------------------------------------
El archivo tiene:

- Una historia pensada de principio a fin: despiertas en la biblioteca, vas encontrando enemigos y aliados, hasta llegar al laboratorio donde está tu amigo infectado.
- Eventos únicos con humor y lógica (como comprar RedBull y balas, o que el director te dé el título).
- Un arma especial que se obtiene en una sala (NOAC) y tiene efecto en el juego.
- Un enemigo final con historia (Walter White).
- El árbol tiene altura 6 y cumple con la estructura ternaria pedida.

Intentamos hacer algo entretenido y con sentido dentro del contexto universitario y lo mezclamos con mecánicas simples pero funcionales.

==============================
FIN DEL README


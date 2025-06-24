#include <stdio.h>
#include <string.h>
#include "funcion.h"

// Registrar resultados de un partido
void registrarPartido(struct Partido *partido, struct Equipo equipos[4]) {
    printf("Ingrese el nombre del equipo local: ");
    leerCadena(partido->equipoLocal, 30);
    printf("Ingrese los goles del equipo local: ");
    scanf("%d", &partido->golesLocal);

    printf("Ingrese el nombre del equipo visitante: ");
    leerCadena(partido->equipoVisitante, 30);
    printf("Ingrese los goles del equipo visitante: ");
    scanf("%d", &partido->golesVisitante);

    actualizarEstadisticas(partido, equipos);
}

// Actualizar estadísticas de los equipos
void actualizarEstadisticas(struct Partido *partido, struct Equipo equipos[4]) {
    struct Equipo *local = buscarEquipo(equipos, 4, partido->equipoLocal);
    struct Equipo *visitante = buscarEquipo(equipos, 4, partido->equipoVisitante);

    if (local == NULL || visitante == NULL) {
        printf("Error: Uno o ambos equipos no existen.\n");
        return;
    }

    local->golesAFavor += partido->golesLocal;
    local->golesEnContra += partido->golesVisitante;
    visitante->golesAFavor += partido->golesVisitante;
    visitante->golesEnContra += partido->golesLocal;

    local->partidosJugados++;
    visitante->partidosJugados++;

    if (partido->golesLocal > partido->golesVisitante) {
        local->partidosGanados++;
        visitante->partidosPerdidos++;
        local->puntos += 3;
    } else if (partido->golesLocal < partido->golesVisitante) {
        visitante->partidosGanados++;
        local->partidosPerdidos++;
        visitante->puntos += 3;
    } else {
        local->partidosEmpatados++;
        visitante->partidosEmpatados++;
        local->puntos++;
        visitante->puntos++;
    }
}

// Buscar un equipo por nombre
struct Equipo *buscarEquipo(struct Equipo equipos[4], int numEquipos, char *nombre) {
    for (int i = 0; i < numEquipos; i++) {
        if (strcmp(equipos[i].nombre, nombre) == 0) {
            return &equipos[i];
        }
    }
    return NULL;
}

// Mostrar la tabla de posiciones
void mostrarTabla(struct Equipo equipos[4]) {
    printf("Tabla de posiciones:\n");
    printf("Equipo\tPJ\tG\tE\tP\tGF\tGC\tPuntos\n");
    for (int i = 0; i < 4; i++) {
        printf("%s\t%d\t%d\t%d\t%d\t%d\t%d\t%d\n",
               equipos[i].nombre,
               equipos[i].partidosJugados,
               equipos[i].partidosGanados,
               equipos[i].partidosEmpatados,
               equipos[i].partidosPerdidos,
               equipos[i].golesAFavor,
               equipos[i].golesEnContra,
               equipos[i].puntos);
    }
}

// Mostrar estadísticas de un equipo
void mostrarEstadisticasEquipo(struct Equipo equipos[4]) {
    char nombre[30];
    printf("Ingrese el nombre del equipo: ");
    leerCadena(nombre, 30);

    struct Equipo *equipo = buscarEquipo(equipos, 4, nombre);
    if (equipo == NULL) {
        printf("Equipo no encontrado.\n");
        return;
    }

    printf("Estadísticas del equipo %s:\n", equipo->nombre);
    printf("Partidos jugados: %d\n", equipo->partidosJugados);
    printf("Ganados: %d\n", equipo->partidosGanados);
    printf("Empatados: %d\n", equipo->partidosEmpatados);
    printf("Perdidos: %d\n", equipo->partidosPerdidos);
    printf("Goles a favor: %d\n", equipo->golesAFavor);
    printf("Goles en contra: %d\n", equipo->golesEnContra);
    printf("Puntos: %d\n", equipo->puntos);
}

// Guardar equipos en un archivo
void guardarEquipos(struct Equipo equipos[4]) {
    FILE *archivo = fopen("equipos.dat", "wb");
    if (archivo == NULL) {
        printf("Error al abrir el archivo para guardar los equipos.\n");
        return;
    }
    fwrite(equipos, sizeof(struct Equipo), 4, archivo);
    fclose(archivo);
    printf("Equipos guardados correctamente.\n");
}

// Cargar equipos desde un archivo
void cargarEquipos(struct Equipo equipos[4]) {
    FILE *archivo = fopen("equipos.dat", "rb");
    if (archivo == NULL) {
        printf("No se encontró un archivo de equipos. Se inicializarán los equipos en blanco.\n");
        for (int i = 0; i < 4; i++) {
            strcpy(equipos[i].nombre, "");
            equipos[i].partidosJugados = 0;
            equipos[i].partidosGanados = 0;
            equipos[i].partidosEmpatados = 0;
            equipos[i].partidosPerdidos = 0;
            equipos[i].golesAFavor = 0;
            equipos[i].golesEnContra = 0;
            equipos[i].puntos = 0;
        }
        return;
    }
    fread(equipos, sizeof(struct Equipo), 4, archivo);
    fclose(archivo);
    printf("Equipos cargados correctamente.\n");
}
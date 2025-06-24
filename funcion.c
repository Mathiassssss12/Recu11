#include <stdio.h>
#include <string.h>
#include "funcion.h"

void inicializarEquipos(Equipo equipos[NUM_EQUIPOS]) {
    // Lista fija de los 16 equipos de LigaPro Serie A 2025
    const char *nombres[NUM_EQUIPOS] = {
        "Aucas", "Barcelona SC", "Delfin", "Deportivo Cuenca",
        "El Nacional", "Emelec", "Independiente del Valle", "Libertad",
        "Liga de Quito", "Macara", "Manta FC", "Mushuc Runa",
        "Orense", "Tecnico Universitario", "Universidad Catolica", "Vinotinto Ecuador"
    };

    for (int i = 0; i < NUM_EQUIPOS; i++) {
        strcpy(equipos[i].nombre, nombres[i]);
        equipos[i].partidosJugados = 0;
        equipos[i].ganados = 0;
        equipos[i].empatados = 0;
        equipos[i].perdidos = 0;
        equipos[i].golesFavor = 0;
        equipos[i].golesContra = 0;
        equipos[i].puntos = 0;
    }
}

int buscarEquipo(const Equipo equipos[], const char *nombre) {
    for (int i = 0; i < NUM_EQUIPOS; i++) {
        if (strcmp(equipos[i].nombre, nombre) == 0) {
            return i;
        }
    }
    return -1;
}

void registrarPartido(Equipo equipos[NUM_EQUIPOS], Partido partidos[], int *numPartidos) {
    char local[32], visitante[32];
    int golesLocal, golesVisitante, idxLocal, idxVisitante;

    printf("Ingrese nombre del equipo local: ");
    getchar(); // Limpieza de buffer
    fgets(local, sizeof(local), stdin);
    local[strcspn(local, "\n")] = 0; // Quitar el salto de línea

    printf("Ingrese nombre del equipo visitante: ");
    fgets(visitante, sizeof(visitante), stdin);
    visitante[strcspn(visitante, "\n")] = 0;

    idxLocal = buscarEquipo(equipos, local);
    idxVisitante = buscarEquipo(equipos, visitante);

    if (idxLocal == -1 || idxVisitante == -1) {
        printf("Alguno de los equipos no existe en la LigaPro.\n");
        return;
    }

    printf("Goles para %s: ", local);
    scanf("%d", &golesLocal);
    printf("Goles para %s: ", visitante);
    scanf("%d", &golesVisitante);

    // Guardar partido en historial
    Partido p;
    strcpy(p.local, local);
    strcpy(p.visitante, visitante);
    p.golesLocal = golesLocal;
    p.golesVisitante = golesVisitante;
    partidos[*numPartidos] = p;
    (*numPartidos)++;

    // Actualizar estadísticas
    equipos[idxLocal].partidosJugados++;
    equipos[idxVisitante].partidosJugados++;
    equipos[idxLocal].golesFavor += golesLocal;
    equipos[idxLocal].golesContra += golesVisitante;
    equipos[idxVisitante].golesFavor += golesVisitante;
    equipos[idxVisitante].golesContra += golesLocal;

    if (golesLocal > golesVisitante) {
        equipos[idxLocal].ganados++;
        equipos[idxVisitante].perdidos++;
        equipos[idxLocal].puntos += 3;
        printf("Ganador: %s\n", equipos[idxLocal].nombre);
    } else if (golesLocal < golesVisitante) {
        equipos[idxVisitante].ganados++;
        equipos[idxLocal].perdidos++;
        equipos[idxVisitante].puntos += 3;
        printf("Ganador: %s\n", equipos[idxVisitante].nombre);
    } else {
        equipos[idxLocal].empatados++;
        equipos[idxVisitante].empatados++;
        equipos[idxLocal].puntos += 1;
        equipos[idxVisitante].puntos += 1;
        printf("Empate entre %s y %s\n", equipos[idxLocal].nombre, equipos[idxVisitante].nombre);
    }
}

void mostrarTablaPosiciones(Equipo equipos[NUM_EQUIPOS]) {
    // Ordenar por puntos y luego diferencia de goles
    Equipo ordenados[NUM_EQUIPOS];
    memcpy(ordenados, equipos, sizeof(ordenados));
    for (int i = 0; i < NUM_EQUIPOS - 1; i++) {
        for (int j = i + 1; j < NUM_EQUIPOS; j++) {
            int diffI = ordenados[i].golesFavor - ordenados[i].golesContra;
            int diffJ = ordenados[j].golesFavor - ordenados[j].golesContra;
            if (
                ordenados[j].puntos > ordenados[i].puntos ||
                (ordenados[j].puntos == ordenados[i].puntos && diffJ > diffI)
            ) {
                Equipo tmp = ordenados[i];
                ordenados[i] = ordenados[j];
                ordenados[j] = tmp;
            }
        }
    }
    printf("\n%-24s PJ  PG  PE  PP  GF  GC  PTS\n", "Equipo");
    for (int i = 0; i < NUM_EQUIPOS; i++) {
        printf("%-24s %2d  %2d  %2d  %2d  %2d  %2d  %3d\n",
            ordenados[i].nombre,
            ordenados[i].partidosJugados,
            ordenados[i].ganados,
            ordenados[i].empatados,
            ordenados[i].perdidos,
            ordenados[i].golesFavor,
            ordenados[i].golesContra,
            ordenados[i].puntos
        );
    }
}

void mostrarHistorialPartidos(const Partido partidos[], int numPartidos) {
    printf("\nHISTORIAL DE PARTIDOS JUGADOS:\n");
    if (numPartidos == 0) {
        printf("No hay partidos registrados.\n");
        return;
    }
    for (int i = 0; i < numPartidos; i++) {
        printf("%2d. %s %d - %d %s\n", i + 1,
            partidos[i].local, partidos[i].golesLocal,
            partidos[i].golesVisitante, partidos[i].visitante);
    }
}
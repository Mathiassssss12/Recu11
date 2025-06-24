#include <stdio.h>
#include <string.h>
#include "funcion.h"

void inicializarEquipos(Equipo equipos[NUM_EQUIPOS]) {
    const char *nombres[NUM_EQUIPOS] = {
        "Aucas", "Barcelona SC", "Delfin", "Deportivo Cuenca",
        "El Nacional", "Emelec", "Independiente del Valle", "Libertad",
        "Liga de Quito", "Macara", "Manta FC", "Mushuc Runa",
        "Orense", "Tecnico Universitario", "Universidad Catolica", "Vinotinto Ecuador"
    };

    const char *jugadores[NUM_EQUIPOS][NUM_JUGADORES] = {
        {"Hamilton Piedra", "Brian Montenegro", "Stalin Segura", "Michael Carcelén", "Jonnathan Mina", "Edson Reséndez", "Ulises Ciccioli", "John Ontaneda"},
        {"Damián Díaz", "Fidel Martínez", "Mario Pineida", "Gabriel Marques", "Christian Cruz", "Felipe Caicedo", "Byron Castillo", "Jesús Trindade"},
        {"Jairo Padilla", "Ayrton Preciado", "José Cevallos", "Luis Luna", "Romario Caicedo", "Anderson Julio", "Moisés Corozo", ""},
        {"Ignacio Bailone", "Agustín Gómez", "Brian Bustos", "Luis Estupiñán", "Marcos López", "Cristian Tobar Luna", "Alejandro Tobar", ""},
        {"Damián Lanza", "Walter Chalá", "William Palacios", "Miguel Parrales", "Jefferson Intriago", "Carlos Arboleda", "", ""},
        {"Bryan Cabezas", "Luis León", "Facundo Barceló", "Aníbal Leguizamón", "Sebastián Rodríguez", "José Angulo", "", ""},
        {"Michael Hoyos", "Jhegson Méndez", "Piero Hincapié", "Moisés Caicedo", "Matías Zunino", "David Córdova", "", ""},
        {"Eber Caicedo", "Carlos Arboleda", "Luis Amarilla", "Diego Armas", "Esteban Paz", "", "", ""},
        {"Adrián Gabbarini", "Luis Amarilla", "Hernán Pellerano", "Aníbal Chalá", "Damián Díaz", "Rodrigo Aguirre", "", ""},
        {"Ricardo Prieto", "Jimmy Montanero", "Wilson Paredes", "José Cevallos", "", "", "", ""},
        {"Daniel Valencia", "Christian Alemán", "Carlos Garcés", "José Luis Quiñónez", "", "", "", ""},
        {"Ricardo Adalberto", "Washington Corozo", "Jonathan Bauman", "José Madrid", "", "", "", ""},
        {"Miguel Parrales", "Ángel Mena", "Alexander Domínguez", "José Cevallos", "", "", "", ""},
        {"Jhonny Quiñónez", "Gabriel Cortez", "Jhon Espinoza", "Anderson Ordóñez", "", "", "", ""},
        {"Byron Palacios", "Ismael Díaz", "Juan Carlos Paredes", "Gabriel Marques", "", "", "", ""},
        {"Rafael Monti", "Danny Luna", "Josué Estrada", "Andrés López", "", "", "", ""}
    };

    for (int i = 0; i < NUM_EQUIPOS; i++) {
        strcpy(equipos[i].nombre, nombres[i]);
        equipos[i].partidosJugados = equipos[i].ganados = equipos[i].empatados = equipos[i].perdidos = 0;
        equipos[i].golesFavor = equipos[i].golesContra = equipos[i].puntos = 0;
        for (int j = 0; j < NUM_JUGADORES; j++) {
            strcpy(equipos[i].jugadores[j].nombre, jugadores[i][j]);
            equipos[i].jugadores[j].goles = 0;
        }
    }
}

void mostrarListadoEquipos(const Equipo equipos[NUM_EQUIPOS]) {
    printf("Lista de equipos:\n");
    for (int i = 0; i < NUM_EQUIPOS; i++) {
        printf("%2d. %s\n", i + 1, equipos[i].nombre);
    }
}

void mostrarJugadores(const Equipo* equipo) {
    printf("Jugadores de %s:\n", equipo->nombre);
    for (int i = 0; i < NUM_JUGADORES; i++) {
        if (strlen(equipo->jugadores[i].nombre) > 0)
            printf("%2d. %s\n", i + 1, equipo->jugadores[i].nombre);
    }
}

void registrarPartido(Equipo equipos[NUM_EQUIPOS], Partido partidos[], int *numPartidos) {
    int idxLocal, idxVisitante, golesLocal, golesVisitante;
    printf("\nSeleccione el equipo LOCAL:\n");
    mostrarListadoEquipos(equipos);
    printf("Ingrese el número del equipo local: ");
    scanf("%d", &idxLocal); idxLocal--;

    if (idxLocal < 0 || idxLocal >= NUM_EQUIPOS) {
        printf("Equipo local inválido.\n"); return;
    }

    printf("\nSeleccione el equipo VISITANTE:\n");
    mostrarListadoEquipos(equipos);
    printf("Ingrese el número del equipo visitante: ");
    scanf("%d", &idxVisitante); idxVisitante--;

    if (idxVisitante < 0 || idxVisitante >= NUM_EQUIPOS || idxVisitante == idxLocal) {
        printf("Equipo visitante inválido o igual al local.\n"); return;
    }

    printf("Goles para %s: ", equipos[idxLocal].nombre); scanf("%d", &golesLocal);
    printf("Goles para %s: ", equipos[idxVisitante].nombre); scanf("%d", &golesVisitante);

    Partido p;
    p.idxLocal = idxLocal;
    p.idxVisitante = idxVisitante;
    p.golesLocal = golesLocal;
    p.golesVisitante = golesVisitante;

    // Goleadores Local
    for (int i = 0; i < golesLocal; i++) {
        printf("Gol %d de %s: seleccione jugador:\n", i + 1, equipos[idxLocal].nombre);
        mostrarJugadores(&equipos[idxLocal]);
        int jug;
        do {
            printf("Ingrese el número del jugador: ");
            scanf("%d", &jug);
            jug--;
            if (jug < 0 || jug >= NUM_JUGADORES || strlen(equipos[idxLocal].jugadores[jug].nombre) == 0)
                printf("Jugador inválido. ");
        } while (jug < 0 || jug >= NUM_JUGADORES || strlen(equipos[idxLocal].jugadores[jug].nombre) == 0);
        p.golesJugadoresLocal[i] = jug;
        equipos[idxLocal].jugadores[jug].goles++;
    }

    // Goleadores Visitante
    for (int i = 0; i < golesVisitante; i++) {
        printf("Gol %d de %s: seleccione jugador:\n", i + 1, equipos[idxVisitante].nombre);
        mostrarJugadores(&equipos[idxVisitante]);
        int jug;
        do {
            printf("Ingrese el número del jugador: ");
            scanf("%d", &jug);
            jug--;
            if (jug < 0 || jug >= NUM_JUGADORES || strlen(equipos[idxVisitante].jugadores[jug].nombre) == 0)
                printf("Jugador inválido. ");
        } while (jug < 0 || jug >= NUM_JUGADORES || strlen(equipos[idxVisitante].jugadores[jug].nombre) == 0);
        p.golesJugadoresVisitante[i] = jug;
        equipos[idxVisitante].jugadores[jug].goles++;
    }

    partidos[*numPartidos] = p;
    (*numPartidos)++;

    // Actualizar estadísticas equipos
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
    Equipo ordenados[NUM_EQUIPOS];
    memcpy(ordenados, equipos, sizeof(ordenados));
    for (int i = 0; i < NUM_EQUIPOS - 1; i++) {
        for (int j = i + 1; j < NUM_EQUIPOS; j++) {
            int diffI = ordenados[i].golesFavor - ordenados[i].golesContra;
            int diffJ = ordenados[j].golesFavor - ordenados[j].golesContra;
            if (ordenados[j].puntos > ordenados[i].puntos ||
                (ordenados[j].puntos == ordenados[i].puntos && diffJ > diffI)) {
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

void mostrarHistorialPartidos(const Partido partidos[], int numPartidos, const Equipo equipos[]) {
    printf("\nHISTORIAL DE PARTIDOS JUGADOS:\n");
    if (numPartidos == 0) {
        printf("No hay partidos registrados.\n");
        return;
    }
    for (int i = 0; i < numPartidos; i++) {
        printf("%2d. %s %d - %d %s\n", i + 1,
            equipos[partidos[i].idxLocal].nombre, partidos[i].golesLocal,
            partidos[i].golesVisitante, equipos[partidos[i].idxVisitante].nombre);
    }
}

void imprimirGoleadoresTorneo(Equipo equipos[NUM_EQUIPOS]) {
    int maxGoles = 0;
    for (int i = 0; i < NUM_EQUIPOS; i++)
        for (int j = 0; j < NUM_JUGADORES; j++)
            if (equipos[i].jugadores[j].goles > maxGoles)
                maxGoles = equipos[i].jugadores[j].goles;
    printf("\nGoleador(es) del torneo:\n");
    for (int i = 0; i < NUM_EQUIPOS; i++)
        for (int j = 0; j < NUM_JUGADORES; j++)
            if (equipos[i].jugadores[j].goles == maxGoles && maxGoles > 0)
                printf("%s (%s): %d goles\n", equipos[i].jugadores[j].nombre, equipos[i].nombre, equipos[i].jugadores[j].goles);
    if (maxGoles == 0)
        printf("No hay goles en el torneo.\n");
}

void imprimirGoleadoresPorEquipo(Equipo equipos[NUM_EQUIPOS]) {
    printf("\nGoleador de cada equipo:\n");
    for (int i = 0; i < NUM_EQUIPOS; i++) {
        int maxGoles = 0, idxGoleador = -1;
        for (int j = 0; j < NUM_JUGADORES; j++) {
            if (equipos[i].jugadores[j].goles > maxGoles) {
                maxGoles = equipos[i].jugadores[j].goles;
                idxGoleador = j;
            }
        }
        printf("%s: ", equipos[i].nombre);
        if (idxGoleador >= 0 && maxGoles > 0)
            printf("%s con %d goles\n", equipos[i].jugadores[idxGoleador].nombre, maxGoles);
        else
            printf("Sin goles\n");
    }
}
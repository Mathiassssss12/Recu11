#ifndef FUNCION_H
#define FUNCION_H

#define NUM_EQUIPOS 16
#define NUM_JUGADORES 8
#define MAX_PARTIDOS 240
#define MAX_GOLES_PARTIDO 16

typedef struct {
    char nombre[32];
    int goles;
} Jugador;

typedef struct {
    char nombre[32];
    Jugador jugadores[NUM_JUGADORES];
    int partidosJugados;
    int ganados, empatados, perdidos;
    int golesFavor, golesContra;
    int puntos;
} Equipo;

typedef struct {
    int idxLocal, idxVisitante;
    int golesLocal, golesVisitante;
    int golesJugadoresLocal[MAX_GOLES_PARTIDO];    // índices de jugadores del local
    int golesJugadoresVisitante[MAX_GOLES_PARTIDO]; // índices de jugadores del visitante
} Partido;

void inicializarEquipos(Equipo equipos[NUM_EQUIPOS]);
void mostrarListadoEquipos(const Equipo equipos[NUM_EQUIPOS]);
void mostrarJugadores(const Equipo* equipo);
void registrarPartido(Equipo equipos[NUM_EQUIPOS], Partido partidos[], int *numPartidos);
void mostrarTablaPosiciones(Equipo equipos[NUM_EQUIPOS]);
void mostrarHistorialPartidos(const Partido partidos[], int numPartidos, const Equipo equipos[]);
void imprimirGoleadoresTorneo(Equipo equipos[NUM_EQUIPOS]);
void imprimirGoleadoresPorEquipo(Equipo equipos[NUM_EQUIPOS]);

#endif
#ifndef FUNCION_H
#define FUNCION_H

#define NUM_EQUIPOS 16
#define MAX_PARTIDOS 240

typedef struct {
    char nombre[32];
    int partidosJugados;
    int ganados, empatados, perdidos;
    int golesFavor, golesContra;
    int puntos;
} Equipo;

typedef struct {
    char local[32], visitante[32];
    int golesLocal, golesVisitante;
} Partido;

// Prototipos de funciones
void inicializarEquipos(Equipo equipos[NUM_EQUIPOS]);
int buscarEquipo(const Equipo equipos[], const char *nombre);
void registrarPartido(Equipo equipos[NUM_EQUIPOS], Partido partidos[], int *numPartidos);
void mostrarTablaPosiciones(Equipo equipos[NUM_EQUIPOS]);
void mostrarHistorialPartidos(const Partido partidos[], int numPartidos);

#endif
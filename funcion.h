#ifndef FUNCION_H
#define FUNCION_H

// Estructura para representar un equipo
struct Equipo {
    char nombre[30];
    int partidosJugados;
    int partidosGanados;
    int partidosEmpatados;
    int partidosPerdidos;
    int golesAFavor;
    int golesEnContra;
    int puntos;
};

// Estructura para representar un partido
struct Partido {
    char equipoLocal[30];
    char equipoVisitante[30];
    int golesLocal;
    int golesVisitante;
};

// Declaraciones de funciones
void leerCadena(char *cadena, int num);
void registrarPartido(struct Partido *partido, struct Equipo equipos[4]);
void actualizarEstadisticas(struct Partido *partido, struct Equipo equipos[4]);
struct Equipo *buscarEquipo(struct Equipo equipos[4], int numEquipos, char *nombre);
void mostrarTabla(struct Equipo equipos[4]);
void mostrarEstadisticasEquipo(struct Equipo equipos[4]);

// Funciones para manejo de archivos
void guardarEquipos(struct Equipo equipos[4]);
void cargarEquipos(struct Equipo equipos[4]);

#endif // FUNCION_H
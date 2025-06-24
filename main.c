#include <stdio.h>
#include "funcion.h"

int main (int argc, char *argv[]) {
    struct Equipo equipos[4];
    struct Partido partido;
    int opcion;

    // Cargar equipos desde archivo
    cargarEquipos(equipos);

    do {
        printf("\n-----------------------------------\n");
        printf("SISTEMA DE GESTION DE LIGAPRO\n");
        printf("1. Registrar resultado de un partido\n");
        printf("2. Mostrar tabla de posiciones\n");
        printf("3. Mostrar estadísticas de un equipo\n");
        printf("4. Guardar equipos y salir\n");
        printf("Seleccione una opción: ");
        scanf("%d", &opcion);
        getchar(); // Limpiar el buffer de entrada

        switch (opcion) {
            case 1:
                registrarPartido(&partido, equipos);
                break;
            case 2:
                mostrarTabla(equipos);
                break;
            case 3:
                mostrarEstadisticasEquipo(equipos);
                break;
            case 4:
                guardarEquipos(equipos);
                printf("Datos guardados. Saliendo del programa...\n");
                break;
            default:
                printf("Opción no válida. Intente de nuevo.\n");
        }
    } while (opcion != 4);

    return 0;
}



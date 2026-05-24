#ifndef PROCESO_H
#define PROCESO_H

// Datos basicos de un proceso del sistema.
struct Proceso
{
    int id;
    char nombre[50];
    int prioridad; // 1=Alta, 2=Media, 3=Baja
    char estado[20]; // "Listo", "En ejecucion", "Terminado"
    int memoria; // memoria asignada
    Proceso* siguiente; // Puntero al siguiente proceso
};

#endif

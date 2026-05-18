#ifndef PACIENTE_H
#define PACIENTE_H

// Datos basicos del paciente para el sistema.
struct Paciente
{
    int id;
    char nombre[50];
    int edad;
    char sintomas[100];
    int prioridad; // 1=Alta, 2=Media, 3=Baja
    char estado[20]; // "Esperando", "En atencion", "Alta"
    Paciente* siguiente; // Puntero al siguiente paciente en la lista
};

#endif

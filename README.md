# Sistema de Gestion de Procesos

Proyecto en C++ que simula la administracion de procesos de un sistema operativo usando una lista enlazada, una cola de prioridad y una pila de memoria.

## Integrantes

- Ordoñez Molinero Hans Anderson
- George Bill Valdivieso Tomas
- Casavilca Paucar Joel Walter
- De la cruz Santana Jhon Kenyo

## Distribucion del trabajo

- George Bill Valdivieso Tomas: Capitulo 1, analisis del problema.
- De la cruz Santana Jhon Kenyo: Capitulo 2, diseno de la solucion.
- Casavilca Paucar Joel Walter: Manual de usuario.
- Ordoñez Molinero Hans Anderson: Codigo, integracion final y README.

Todo el equipo apoyo en revision, pruebas y validacion del sistema.

## Estructura del proyecto

```text
├── src/
│   ├── main.cpp
│   ├── ListaProcesos.cpp
│   ├── ColaProcesos.cpp
│   ├── PilaMemoria.cpp
│   └── Proceso.h
├── Documentación/
└── README.md
```

## Funcionalidades

- Registrar, buscar, modificar y eliminar procesos.
- Mostrar la lista de procesos y la cola de ejecucion.
- Ejecutar procesos segun prioridad.
- Gestionar memoria con una pila de bloques.
- Guardar y cargar informacion desde `procesos.txt`.

## Requisitos

- g++ o Dev C++ 5.11

## Compilacion y ejecucion

### Con g++

```bash
g++ src/*.cpp -o sistema_procesos
./sistema_procesos
```

### En Dev C++

1. Crear un proyecto de consola en C++.
2. Agregar todos los archivos de la carpeta `src`.
3. Compilar y ejecutar.

## Nota

El archivo `procesos.txt` se crea o actualiza al salir del programa.

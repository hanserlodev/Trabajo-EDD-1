#include <iostream>
#include <fstream>
#include "Paciente.h"

using namespace std;

// Inicio de la lista enlazada de procesos.
Proceso* cabeza = NULL;

// Helpers simples para cadenas y lectura de archivo.
void CopiarCadena(char* destino, int tam, const char* origen)
{
    if (destino == NULL || tam <= 0)
    {
        return;
    }
    if (origen == NULL)
    {
        destino[0] = '\0';
        return;
    }
    int i = 0;
    while (i < tam - 1 && origen[i] != '\0')
    {
        destino[i] = origen[i];
        i++;
    }
    destino[i] = '\0';
}

int CompararCadenas(const char* a, const char* b)
{
    if (a == NULL && b == NULL)
    {
        return 0;
    }
    if (a == NULL)
    {
        return -1;
    }
    if (b == NULL)
    {
        return 1;
    }
    int i = 0;
    while (a[i] != '\0' && b[i] != '\0')
    {
        if (a[i] != b[i])
        {
            return (int)a[i] - (int)b[i];
        }
        i++;
    }
    return (int)a[i] - (int)b[i];
}

int ConvertirEntero(const char* texto)
{
    if (texto == NULL)
    {
        return 0;
    }
    int i = 0;
    int signo = 1;
    if (texto[i] == '-')
    {
        signo = -1;
        i++;
    }
    int valor = 0;
    while (texto[i] >= '0' && texto[i] <= '9')
    {
        valor = valor * 10 + (texto[i] - '0');
        i++;
    }
    return valor * signo;
}

void SepararLinea(char* linea, char* tokens[], int maxTokens, int& cantidad)
{
    cantidad = 0;
    if (linea == NULL || maxTokens <= 0)
    {
        return;
    }

    tokens[cantidad++] = linea;
    char* p = linea;
    while (*p != '\0' && cantidad < maxTokens)
    {
        if (*p == '|')
        {
            *p = '\0';
            p++;
            tokens[cantidad++] = p;
            continue;
        }
        p++;
    }
}

// Retorna el primer nodo de la lista.
Proceso* ObtenerCabeza()
{
    return cabeza;
}

// Inserta un proceso al final de la lista.
Proceso* InsertarProceso(int id, const char* nombre, int prioridad, const char* estado, int memoria)
{
    Proceso* nuevo = new Proceso;
    nuevo->id = id;
    CopiarCadena(nuevo->nombre, (int)sizeof(nuevo->nombre), nombre);
    nuevo->prioridad = prioridad;
    CopiarCadena(nuevo->estado, (int)sizeof(nuevo->estado), estado);
    nuevo->memoria = memoria;
    nuevo->siguiente = NULL;

    if (cabeza == NULL)
    {
        cabeza = nuevo;
        return nuevo;
    }

    Proceso* temp = cabeza;
    while (temp->siguiente != NULL)
    {
        temp = temp->siguiente;
    }
    temp->siguiente = nuevo;
    return nuevo;
}

// Busca un proceso por ID.
Proceso* BuscarProcesoID(int id)
{
    Proceso* temp = cabeza;
    while (temp != NULL)
    {
        if (temp->id == id)
        {
            return temp;
        }
        temp = temp->siguiente;
    }
    return NULL;
}

// Busca un proceso por nombre.
Proceso* BuscarProcesoNombre(const char* nombre)
{
    Proceso* temp = cabeza;
    while (temp != NULL)
    {
        if (CompararCadenas(temp->nombre, nombre) == 0)
        {
            return temp;
        }
        temp = temp->siguiente;
    }
    return NULL;
}

// Modifica prioridad, estado o memoria por ID.
bool ModificarProcesoID(int id, int nuevaPrioridad, const char* nuevoEstado, int nuevaMemoria)
{
    Proceso* temp = BuscarProcesoID(id);
    if (temp == NULL)
    {
        return false;
    }

    if (nuevaPrioridad >= 1 && nuevaPrioridad <= 3)
    {
        temp->prioridad = nuevaPrioridad;
    }
    if (nuevoEstado != NULL && nuevoEstado[0] != '\0')
    {
        CopiarCadena(temp->estado, (int)sizeof(temp->estado), nuevoEstado);
    }
    if (nuevaMemoria >= 0)
    {
        temp->memoria = nuevaMemoria;
    }
    return true;
}

// Elimina un proceso por ID.
bool EliminarProcesoID(int id)
{
    if (cabeza == NULL)
    {
        return false;
    }

    if (cabeza->id == id)
    {
        Proceso* temp = cabeza;
        cabeza = cabeza->siguiente;
        delete temp;
        return true;
    }

    Proceso* temp = cabeza;
    while (temp->siguiente != NULL)
    {
        if (temp->siguiente->id == id)
        {
            Proceso* eliminar = temp->siguiente;
            temp->siguiente = temp->siguiente->siguiente;
            delete eliminar;
            return true;
        }
        temp = temp->siguiente;
    }
    return false;
}

// Muestra todos los procesos.
void MostrarProcesos()
{
    if (cabeza == NULL)
    {
        cout << "No hay procesos registrados." << endl;
        return;
    }

    Proceso* temp = cabeza;
    while (temp != NULL)
    {
        cout << "ID: " << temp->id
             << ", Nombre: " << temp->nombre
             << ", Prioridad: " << temp->prioridad
             << ", Estado: " << temp->estado
             << ", Memoria: " << temp->memoria << endl;
        temp = temp->siguiente;
    }
}

// Guarda la lista en un archivo.
void GuardarProcesosEnArchivo(const char* ruta)
{
    ofstream archivo(ruta);
    if (!archivo.is_open())
    {
        cout << "No se pudo guardar el archivo de procesos." << endl;
        return;
    }

    Proceso* temp = cabeza;
    while (temp != NULL)
    {
        archivo << temp->id << "|"
                << temp->nombre << "|"
                << temp->prioridad << "|"
                << temp->estado << "|"
                << temp->memoria << endl;
        temp = temp->siguiente;
    }
}

// Carga procesos desde un archivo.
void CargarProcesosDesdeArchivo(const char* ruta)
{
    ifstream archivo(ruta);
    if (!archivo.is_open())
    {
        return;
    }

    char linea[512];
    while (archivo.getline(linea, sizeof(linea)))
    {
        char* tokens[5];
        int cantidad = 0;
        SepararLinea(linea, tokens, 5, cantidad);
        if (cantidad < 5)
        {
            continue;
        }

        int id = ConvertirEntero(tokens[0]);
        char nombre[50];
        CopiarCadena(nombre, (int)sizeof(nombre), tokens[1]);
        int prioridad = ConvertirEntero(tokens[2]);
        char estado[20];
        CopiarCadena(estado, (int)sizeof(estado), tokens[3]);
        int memoria = ConvertirEntero(tokens[4]);

        if (BuscarProcesoID(id) == NULL)
        {
            InsertarProceso(id, nombre, prioridad, estado, memoria);
        }
    }
}

// Libera la memoria de la lista.
void LiberarLista()
{
    Proceso* temp = cabeza;
    while (temp != NULL)
    {
        Proceso* siguiente = temp->siguiente;
        delete temp;
        temp = siguiente;
    }
    cabeza = NULL;
}

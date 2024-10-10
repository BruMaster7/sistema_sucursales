#ifndef CABEZALES_H // Include guard: si no ha sido definido, defínelo
#define CABEZALES_H

#include <iostream>
#include <stdio.h>
#include <vector>
#include <list>

using namespace std;

#define MAX_SUCURSALES 100
#define INF 0x3f3f3f3f  // Define INF como un número que representa el infinito

// Estructura que representa una sucursal
typedef struct {
	int id;
	char nombre[100];
	char departamento[50];
	char telefono[20];
	char responsable[100];
	vector<int> conexionesSalientes; // Lista de IDs de sucursales a las que está conectada esta sucursal
} Sucursal;

// Nodo para la lista de sucursales
typedef struct Nodo {
	Sucursal sucursal;
	struct Nodo* siguiente;
} Nodo;

// Nodo de adyacencia para representar conexiones entre sucursales
struct AdyacenciaNodo {
	int destino;  // Índice del nodo destino
	int peso;     // Peso o costo de la ruta
	AdyacenciaNodo* siguiente;  // Apuntador al siguiente nodo
};

// Estructura de grafo para manejar las sucursales y sus conexiones
struct Grafo {
	int numSucursales;  // Número de sucursales (vértices)
	list<AdyacenciaNodo*>* listaAdyacencia;  // Lista de listas de adyacencia
};

// Declaración de variables globales
extern Nodo sucursales[MAX_SUCURSALES];
extern int contadorSucursales;
extern int autoIncrementalID;

// Declaración de funciones

// Menús
void sucursalmenu();
void menu();

// Sucursales
void sucursalesActuales();
int ingresarId();
void agregarSucursal();
void modificarSucursal(int id);
void eliminarSucursal(int id);

// Rutas
void rutasActuales(Grafo* grafo);
void modificarRuta(Grafo* grafo);
void guardarRutasEnArchivo(Grafo* grafo);
void cargarRutasDesdeArchivo(Grafo* grafo);
void rutaOptima();

// Grafo y adyacencias
AdyacenciaNodo* crearNodo(int destino, int peso);
Grafo* crearGrafo(int V);
void inicializarGrafoConCentral(Grafo* grafo, int nodoCentral);
void agregarArista(Grafo* grafo, int src, int dest, int peso);
void mostrarGrafo(Grafo* grafo);

// Utilidades
int obtenerIndicePorId(int id);
void mostrarSucursalesConId();

// Archivos
void guardarSucursalesEnArchivo();
void cargarSucursalesDesdeArchivo();

#endif // Fin del include guard

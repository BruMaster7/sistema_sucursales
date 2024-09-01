#include <iostream>
#include <stdio.h>
using namespace std;

typedef struct {
	int id;
	char nombre[100];
	char departamento[50];
	char telefono[20];
	char responsable[100];
} Sucursal;

typedef struct Nodo {
	Sucursal sucursal;
	struct Nodo *siguiente;
} Nodo;

struct AdyacenciaNodo {
	int destino;   // �ndice del nodo destino
	int peso;      // Peso o costo de la ruta, si aplica
	AdyacenciaNodo* siguiente;  // Apuntador al siguiente nodo
};

struct Grafo {
	int numSucursales;  // N�mero de sucursales (v�rtices)
	AdyacenciaNodo** listaAdyacencia;  // Arreglo de listas de adyacencia
};


void sucursalmenu();
void menu();
void sucursalesActuales();
int ingresarId();
void agregarSucursal();
void modificarSucursal(int id);
void eliminarSucursal(int id);
void rutasActuales(Grafo* grafo);
void modificarRuta(Grafo* grafo);
void rutaOptima();
AdyacenciaNodo* crearNodo(int destino, int peso);
Grafo* crearGrafo(int V);
void agregarArista(Grafo* grafo, int src, int dest, int peso);
void mostrarGrafo(Grafo* grafo);




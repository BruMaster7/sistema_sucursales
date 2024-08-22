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

void menu();
void sucursalmenu();


int ingresarId();
void sucursalesActuales();
void agregarSucursal();
void modificarSucursal(int id);
void eliminarSucursal(int id);
void rutasActuales();
void modificarRuta();
void rutaOptima();




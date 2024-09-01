#include <iostream>
#include <cstring>  // Para funciones de manejo de cadenas
#include <cstdio>   // Para funciones de entrada/salida estándar
#include "cabezales.h"
using namespace std;

#define MAX_SUCURSALES 100

// Declaración global para el ID auto-incremental
int autoIncrementalID = 1;

Nodo sucursales[MAX_SUCURSALES];
int contadorSucursales = 0;

// Menú de sucursales
void sucursalmenu() {
	int opmenu;
	int id;
	cout << "**************************************" << endl;
	cout << "*    Mantenimiento de sucursales     *" << endl;
	cout << "*Seleccione que acción desea realizar*" << endl;
	cout << "*1-Sucursales actuales               *" << endl;
	cout << "*2-Agregar sucursal                  *" << endl;
	cout << "*3-Modificar sucursal                *" << endl;
	cout << "*4-Eliminar sucursal                 *" << endl;
	cin >> opmenu;
	switch (opmenu) {
	case 1:
		sucursalesActuales();
		break;
	case 2:
		agregarSucursal();
		break;
	case 3:
		id = ingresarId();
		modificarSucursal(id);
		break;
	case 4:
		id = ingresarId();
		eliminarSucursal(id);
		break;
	default:
		cout << "Esa opción no está disponible, elija otra por favor" << endl;
		system("pause");
		system("cls");
	}
}

// Menú principal
void menu() {
	Grafo* grafo = crearGrafo(MAX_SUCURSALES);
	int opmenu;
	do {
		cout << "**************************************" << endl;
		cout << "*    Mantenimiento de sucursales     *" << endl;
		cout << "*Seleccione que acción desea realizar*" << endl;
		cout << "*1-Gestionar Sucursales              *" << endl;
		cout << "*2-Ver rutas actuales                *" << endl;
		cout << "*3-Modificar ruta                    *" << endl;
		cout << "*4-Buscar ruta optima                *" << endl;
		cout << "*6-Salir                             *" << endl;
		cout << "**************************************" << endl;
		cin >> opmenu;
		switch (opmenu) {
		case 1:
			sucursalmenu();
			break;
		case 2:
			rutasActuales(grafo);
			break;
		case 3:
			modificarRuta(grafo);
			break;
		case 4:
			rutaOptima();
			break;
		case 6:
			cout << "Gracias por utilizar el sistema de gestion de sucursales\n";
			break;
		default:
			cout << "Esa opción no está disponible, elija otra por favor" << endl;
			system("pause");
			system("cls");
		}
	} while (opmenu != 6);
}

// Mostrar todas las sucursales actuales
void sucursalesActuales() {
	if (contadorSucursales == 0) {
		cout << "**************************************" << endl;
		cout << "*No hay sucursales registradas.      *" << endl;
		cout << "**************************************" << endl;
		system("pause");
		system("cls");
		return;
	}
	
	for (int i = 0; i < contadorSucursales; i++) {
		cout << "**************************************" << endl;
		cout << "ID: " << sucursales[i].sucursal.id << endl;
		cout << "Nombre: " << sucursales[i].sucursal.nombre << endl;
		cout << "Departamento: " << sucursales[i].sucursal.departamento << endl;
		cout << "Teléfono: " << sucursales[i].sucursal.telefono << endl;
		cout << "Responsable: " << sucursales[i].sucursal.responsable << endl;
		cout << "**************************************" << endl;
	}
	system("pause");
	system("cls");
}

// Función para ingresar el ID
int ingresarId() {
	int id;
	cout << "Ingrese el ID de la sucursal que desea modificar: " << endl;
	cin >> id;
	return id;
}

// Agregar una nueva sucursal
void agregarSucursal() {
	if (contadorSucursales >= MAX_SUCURSALES) {
		cout << "*****************************************************************" << endl;
		cout << "No se pueden agregar más sucursales, el límite ha sido alcanzado." << endl;
		cout << "*****************************************************************" << endl;
		system("pause");
		system("cls");
		return;
	}
	
	cout << "*************************************" << endl;
	sucursales[contadorSucursales].sucursal.id = autoIncrementalID++; // Asignación de ID auto-incremental
	cout << "Ingrese el nombre de la sucursal: ";
	cin.ignore(); // Limpiar el buffer de entrada
	cin.getline(sucursales[contadorSucursales].sucursal.nombre, 100);
	cout << "Ingrese el departamento de la sucursal: ";
	cin.getline(sucursales[contadorSucursales].sucursal.departamento, 50);
	cout << "Ingrese el teléfono de la sucursal: ";
	cin.getline(sucursales[contadorSucursales].sucursal.telefono, 20);
	cout << "Ingrese el nombre del responsable: ";
	cin.getline(sucursales[contadorSucursales].sucursal.responsable, 100);
	cout << "*************************************" << endl;
	
	contadorSucursales++;
	system("pause");
	system("cls");
}

// Modificar una sucursal existente
void modificarSucursal(int id) {
	for (int i = 0; i < contadorSucursales; i++) {
		if (sucursales[i].sucursal.id == id) {
			cout << "***************************************************************" << endl;
			cout << "Modificar Nombre (Actual: " << sucursales[i].sucursal.nombre << "): ";
			cin.ignore();
			cin.getline(sucursales[i].sucursal.nombre, 100);
			cout << "Modificar Departamento (Actual: " << sucursales[i].sucursal.departamento << "): ";
			cin.getline(sucursales[i].sucursal.departamento, 50);
			cout << "Modificar Teléfono (Actual: " << sucursales[i].sucursal.telefono << "): ";
			cin.getline(sucursales[i].sucursal.telefono, 20);
			cout << "Modificar Responsable (Actual: " << sucursales[i].sucursal.responsable << "): ";
			cin.getline(sucursales[i].sucursal.responsable, 100);
			cout << "****************************************************************" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
	cout << "**************************************" << endl;
	cout << "Sucursal con ID " << id << " no encontrada" << endl;
	cout << "**************************************" << endl;
	system("pause");
	system("cls");
}

// Eliminar una sucursal
void eliminarSucursal(int id) {
	for (int i = 0; i < contadorSucursales; i++) {
		if (sucursales[i].sucursal.id == id) {
			for (int j = i; j < contadorSucursales - 1; j++) {
				sucursales[j] = sucursales[j + 1];
			}
			contadorSucursales--;
			cout << "Sucursal con ID " << id << " eliminada" << endl;
			system("pause");
			system("cls");
			return;
		}
	}
	cout << "**************************************" << endl;
	cout << "Sucursal con ID " << id << " no encontrada" << endl;
	cout << "**************************************" << endl;
	system("pause");
	system("cls");
}


// Función para crear un nuevo nodo de adyacencia
AdyacenciaNodo* crearNodo(int destino, int peso) {
	AdyacenciaNodo* nuevoNodo = new AdyacenciaNodo;
	nuevoNodo->destino = destino;
	nuevoNodo->peso = peso;
	nuevoNodo->siguiente = nullptr;
	return nuevoNodo;
}

// Función para crear un grafo de V vértices
Grafo* crearGrafo(int V) {
	Grafo* grafo = new Grafo;
	grafo->numSucursales = V;
	
	// Crear un arreglo de listas de adyacencia. El tamaño del arreglo es V
	grafo->listaAdyacencia = new AdyacenciaNodo*[V];
	
	// Inicializar cada lista de adyacencia como vacía
	for (int i = 0; i < V; ++i)
		grafo->listaAdyacencia[i] = nullptr;
	
	return grafo;
}

// Función para agregar una arista al grafo no dirigido
void agregarArista(Grafo* grafo, int src, int dest, int peso) {
	// Agregar una arista de src a dest. Un nuevo nodo se añade a la lista de adyacencia de src
	AdyacenciaNodo* nuevoNodo = crearNodo(dest, peso);
	nuevoNodo->siguiente = grafo->listaAdyacencia[src];
	grafo->listaAdyacencia[src] = nuevoNodo;
	
	// Como el grafo es no dirigido, agregar también una arista de dest a src
	nuevoNodo = crearNodo(src, peso);
	nuevoNodo->siguiente = grafo->listaAdyacencia[dest];
	grafo->listaAdyacencia[dest] = nuevoNodo;
}

// Función para mostrar las listas de adyacencia del grafo
void mostrarGrafo(Grafo* grafo) {
	for (int v = 0; v < grafo->numSucursales; ++v) {
		AdyacenciaNodo* temp = grafo->listaAdyacencia[v];
		cout << "\n Lista de adyacencia de la sucursal " << v << "\n";
		while (temp) {
			cout << " -> " << temp->destino << " (Peso: " << temp->peso << ")";
			temp = temp->siguiente;
		}
		cout << endl;
	}
}

// Funciones de rutas
void rutasActuales(Grafo* grafo) {
	cout << "Rutas actuales entre sucursales:" << endl;
	for (int i = 0; i < contadorSucursales; i++) {  // Iterar sobre las sucursales registradas
		if (i >= grafo->numSucursales) {
			break;  // Salir si el índice supera el número de sucursales en el grafo
		}
		
		AdyacenciaNodo* nodoActual = grafo->listaAdyacencia[i];
		if (nodoActual == nullptr) {
			continue;  // Si no hay rutas desde esta sucursal, pasar a la siguiente
		}
		
		cout << "Sucursales conectadas desde " << sucursales[i].sucursal.nombre << ":" << endl;
		while (nodoActual != nullptr) {
			int destino = nodoActual->destino;
			
			// Verificar si el destino tiene una sucursal asignada
			if (destino < contadorSucursales) {
				cout << "  -> " << sucursales[destino].sucursal.nombre 
					<< " (Peso: " << nodoActual->peso << ")" << endl;
			}
			
			nodoActual = nodoActual->siguiente;
		}
	}
	system("pause");
	system("cls");
}

void modificarRuta(Grafo* grafo) {
	int src, dest, peso;
	cout << "Ingrese el índice de la sucursal de origen: ";
	cin >> src;
	cout << "Ingrese el índice de la sucursal de destino: ";
	cin >> dest;
	cout << "Ingrese la distancia de la ruta: ";
	cin >> peso;
	
	agregarArista(grafo, src, dest, peso);
	cout << "Ruta modificada/añadida exitosamente." << endl;
}


void rutaOptima() {
	cout << "En proceso de creación..." << endl;
}






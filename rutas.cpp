#include "sucursales.cpp"
#include "dijkstra.cpp"
#include <iostream>
#include <cstring>  // Para funciones de manejo de cadenas
#include <cstdio>   // Para funciones de entrada/salida est�ndar
#include <fstream>  // Para manejo de archivos
#include <sstream>
#include <string>




using namespace std;

// Funci�n para crear un nuevo nodo de adyacencia
AdyacenciaNodo* crearNodo(int destino, int peso) {
	AdyacenciaNodo* nuevoNodo = new AdyacenciaNodo;
	nuevoNodo->destino = destino;
	nuevoNodo->peso = peso;
	nuevoNodo->siguiente = nullptr;
	return nuevoNodo;
}

// Funci�n para crear un grafo de v v�rtices
Grafo* crearGrafo(int v) {
	Grafo* grafo = new Grafo;
	grafo->numSucursales = v;
	
	// Crear un arreglo de listas de adyacencia. El tama�o del arreglo es v
	grafo->listaAdyacencia = new list<AdyacenciaNodo*>[v];
	
	
	return grafo;
}

// Funci�n para agregar una arista al grafo dirigido
void agregarArista(Grafo* grafo, int src, int dest, int peso) {
	// Agregar una arista de src a dest. Un nuevo nodo se a�ade a la lista de adyacencia de src
	// En caso de que ya exista, sobreescribe
	for(auto &nodo : grafo->listaAdyacencia[src]) {
		if (nodo->destino == dest) {
			nodo->peso = peso;
			return;
		}
	}
	AdyacenciaNodo* nuevoNodo = crearNodo(dest, peso);
	grafo->listaAdyacencia[src].push_back(nuevoNodo);
}
void eliminarArista(Grafo* grafo, int src, int dest) {
	// Buscar el nodo en la lista de adyacencia de src
	auto& lista = grafo->listaAdyacencia[src];
	for (auto it = lista.begin(); it != lista.end(); ++it) {
		if ((*it)->destino == dest) {
			// Eliminar el nodo
			delete *it;  // Liberar memoria
			lista.erase(it);  // Eliminar de la lista
			return;
		}
	}
}
// Funciones de rutas
void rutasActuales(Grafo* grafo) {
	cout << "Rutas actuales entre sucursales:" << endl;
	for (int i = 0; i < contadorSucursales; i++) {  // Iterar sobre las sucursales registradas
		cout << "Sucursales conectadas desde " << sucursales[i].sucursal.nombre << ":" << endl;
		
		// Variable para verificar si hay rutas
		bool hayRutas = false; // Inicializar como false
		
		for (auto &nodoActual : grafo->listaAdyacencia[i]) {
			int destino = nodoActual->destino;
			
			// Verificar si el destino tiene una sucursal asignada
			if (destino < contadorSucursales) {
				cout << "  -> " << sucursales[destino].sucursal.nombre 
					<< " (Kilometros: " << nodoActual->peso << ")" << endl;
				hayRutas = true; // Cambiar a true si se encuentra una ruta
			}
		}
		
		// Mensaje cuando no hay rutas
		if (!hayRutas) {
			cout << "  -> No hay rutas disponibles." << endl;
		}
	}
	system("pause");
	system("cls");
}

void modificarRuta(Grafo* grafo) {
	system("cls");
	
	mostrarSucursalesConId();
	
	int idSrc, idDest, peso;
	cout << "Ingrese el ID de la sucursal de origen: ";
	cin >> idSrc;
	cout << "Ingrese el ID de la sucursal de destino: ";
	cin >> idDest;
	if(idSrc == idDest){
		cout << "Error: No se puede crear un camino hacia si mismo." << endl;
		system("pause");
		system("cls");
		return;
	}
	cout << "Ingrese la distancia de la ruta: ";
	cin >> peso;
	
	// Convertir ID a �ndice
	int src = obtenerIndicePorId(idSrc);
	int dest = obtenerIndicePorId(idDest);
	
	if (src == -1 || dest == -1) {
		cout << "Error: una o ambas sucursales no fueron encontradas." << endl;
		system("pause");
		system("cls");
		return;
	}
	agregarArista(grafo, src, dest, peso);
	guardarRutasEnArchivo(grafo);
	cout << "Ruta modificada/a�adida exitosamente." << endl;
	system("pause");
	system("cls");
}

// Funci�n para eliminar una ruta entre dos sucursales
void eliminarRuta(Grafo* grafo) {
	system("cls");
	
	mostrarSucursalesConId();
	
	int idSrc, idDest;
	cout << "Ingrese el ID de la sucursal de origen: ";
	cin >> idSrc;
	cout << "Ingrese el ID de la sucursal de destino: ";
	cin >> idDest;
	
	// Convertir ID a �ndice
	int src = obtenerIndicePorId(idSrc);
	int dest = obtenerIndicePorId(idDest);
	
	if (src == -1 || dest == -1) {
		cout << "Error: una o ambas sucursales no fueron encontradas." << endl;
		return;
	}
	
	eliminarArista(grafo, src, dest);
	guardarRutasEnArchivo(grafo);  // Guardar cambios en el archivo
	cout << "Ruta eliminada exitosamente." << endl;
	system("pause");
	system("cls");
}

void rutaOptima(Grafo* grafo) {
	shortestPath(grafo, 0);
}


void guardarRutasEnArchivo(Grafo* grafo) {
	ofstream archivo("sucursales/rutas.txt");
	if (!archivo) {
		cerr << "Error al abrir el archivo para guardar las rutas." << endl;
		return;
	}
	
	for (int i = 0; i < contadorSucursales; i++) {
		for (auto &nodoActual : grafo->listaAdyacencia[i]) {
			int destino = nodoActual->destino;
			int peso = nodoActual->peso;
			
			// Guardar la ruta solo si el destino es v�lido y tiene una sucursal asociada
			if (destino < contadorSucursales) {
				archivo << sucursales[i].sucursal.id << ", "
					<< sucursales[destino].sucursal.id << ", "
					<< peso << "\n";
			}
		}
	}
	
	archivo.close();
}

void cargarRutasDesdeArchivo(Grafo* grafo) {
	ifstream archivo("sucursales/rutas.txt");
	if (!archivo) {
		cerr << "Error al abrir el archivo de rutas o el archivo no existe." << endl;
		return;
	}
	
	string linea;
	while (getline(archivo, linea)) {
		stringstream ss(linea);
		string idSrcStr, idDestStr, pesoStr;
		
		// Leer y parsear cada campo separado por comas
		getline(ss, idSrcStr, ',');
		getline(ss, idDestStr, ',');
		getline(ss, pesoStr, ',');
		
		int idSrc = stoi(idSrcStr);
		int idDest = stoi(idDestStr);
		int peso = stoi(pesoStr);
		
		// Convertir IDs a �ndices
		int src = obtenerIndicePorId(idSrc);
		int dest = obtenerIndicePorId(idDest);
		
		// Verificar que las sucursales existan antes de agregar la arista
		if (src != -1 && dest != -1) {
			agregarArista(grafo, src, dest, peso);
		}
	}
	
	archivo.close();
}
int obtenerIndicePorId(int id) {
	for (int i = 0; i < contadorSucursales; i++) {
		if (sucursales[i].sucursal.id == id) {
			return i; // Retornar el �ndice si encuentra la sucursal	
		}
	}
	return -1; // Retornar -1 si no se encuentra la sucursal
}

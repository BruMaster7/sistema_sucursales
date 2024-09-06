#include "sucursales.cpp"
#include "dijkstra.cpp"
#include <iostream>
#include <cstring>  // Para funciones de manejo de cadenas
#include <cstdio>   // Para funciones de entrada/salida estándar
#include <fstream>  // Para manejo de archivos



using namespace std;

// Función para crear un nuevo nodo de adyacencia
AdyacenciaNodo* crearNodo(int destino, int peso) {
	AdyacenciaNodo* nuevoNodo = new AdyacenciaNodo;
	nuevoNodo->destino = destino;
	nuevoNodo->peso = peso;
	nuevoNodo->siguiente = nullptr;
	return nuevoNodo;
}

// Función para crear un grafo de v vértices
Grafo* crearGrafo(int v) {
	Grafo* grafo = new Grafo;
	grafo->numSucursales = v;
	
	// Crear un arreglo de listas de adyacencia. El tamaño del arreglo es v
	grafo->listaAdyacencia = new list<AdyacenciaNodo*>[v];
	
	// Inicializar cada lista de adyacencia como vacía
	//for (int i = 0; i < v; ++i)
		//grafo->listaAdyacencia[i] = nullptr;
	
	return grafo;
}

void inicializarGrafoConCentral(Grafo* grafo, int nodoCentral) {
	for (int i = 0; i < grafo->numSucursales; ++i) {
		if (i != nodoCentral) { // Evitar conectar el nodo central a sí mismo
			agregarArista(grafo, nodoCentral, i, INF); // 0 es un peso default ya que es la sucursal central
		}
	}
}

// Función para agregar una arista al grafo dirigido
void agregarArista(Grafo* grafo, int src, int dest, int peso) {
	// Agregar una arista de src a dest. Un nuevo nodo se añade a la lista de adyacencia de src
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

// Función para mostrar las listas de adyacencia del grafo
void mostrarGrafo(Grafo* grafo) {
	for (int v = 0; v < grafo->numSucursales; ++v) {
		for (auto &nodo : grafo->listaAdyacencia[v]) {
			
			cout << "\n Lista de adyacencia de la sucursal " << v << "\n";

			cout << " -> " << nodo->destino << " (Peso: " << nodo->peso << ")";
			cout << endl;
		}
	}
}

// Funciones de rutas
void rutasActuales(Grafo* grafo) {
	cout << "Rutas actuales entre sucursales:" << endl;
	for (int i = 0; i < contadorSucursales; i++) {  // Iterar sobre las sucursales registradas
		
		
		cout << "Sucursales conectadas desde " << sucursales[i].sucursal.nombre << ":" << endl;
		for (auto &nodoActual : grafo->listaAdyacencia[i]) {
			int destino = nodoActual->destino;
			
			// Verificar si el destino tiene una sucursal asignada
			if (destino < contadorSucursales) {
				cout << "  -> " << sucursales[destino].sucursal.nombre 
					<< " (Kilometros: " << nodoActual->peso << ")" << endl;
			}
			
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
	system("pause");
	system("cls");
}


void rutaOptima(Grafo* grafo) {
	shortestPath(grafo, 0);
}


// Función para guardar las sucursales en un archivo
void guardarSucursalesEnArchivo() {
	ofstream archivo("sucursales/sucursales.txt");
	if (!archivo) {
		cerr << "Error al abrir el archivo para guardar." << endl;
		return;
	}
	
	for (int i = 0; i < contadorSucursales; i++) {
		archivo << sucursales[i].sucursal.id << "\n";
		archivo << sucursales[i].sucursal.nombre << "\n";
		archivo << sucursales[i].sucursal.departamento << "\n";
		archivo << sucursales[i].sucursal.telefono << "\n";
		archivo << sucursales[i].sucursal.responsable << "\n";
	}
	
	archivo.close();
}

void cargarSucursalesDesdeArchivo() {
	ifstream archivo("sucursales/sucursales.txt");
	if (!archivo) {
		cerr << "Error al abrir el archivo para cargar o el archivo no existe." << endl;
		return;
	}
	
	while (!archivo.eof() && contadorSucursales < MAX_SUCURSALES) {
		archivo >> sucursales[contadorSucursales].sucursal.id;
		archivo.ignore(); // Ignorar el salto de línea después del ID
		archivo.getline(sucursales[contadorSucursales].sucursal.nombre, 100);
		archivo.getline(sucursales[contadorSucursales].sucursal.departamento, 50);
		archivo.getline(sucursales[contadorSucursales].sucursal.telefono, 20);
		archivo.getline(sucursales[contadorSucursales].sucursal.responsable, 100);
		
		if (archivo.eof()) break;
		contadorSucursales++;
		if (sucursales[contadorSucursales - 1].sucursal.id >= autoIncrementalID) {
			autoIncrementalID = sucursales[contadorSucursales - 1].sucursal.id + 1;
		}
	}
	
	archivo.close();
}


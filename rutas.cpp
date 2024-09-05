#include "sucursales.cpp"
#include <iostream>
#include <cstring>  // Para funciones de manejo de cadenas
#include <cstdio>   // Para funciones de entrada/salida est�ndar
#include <fstream>  // Para manejo de archivos


using namespace std;

// Funci�n para crear un nuevo nodo de adyacencia
AdyacenciaNodo* crearNodo(int destino, int peso) {
	AdyacenciaNodo* nuevoNodo = new AdyacenciaNodo;
	nuevoNodo->destino = destino;
	nuevoNodo->peso = peso;
	nuevoNodo->siguiente = nullptr;
	return nuevoNodo;
}

// Funci�n para crear un grafo de V v�rtices
Grafo* crearGrafo(int V) {
	Grafo* grafo = new Grafo;
	grafo->numSucursales = V;
	
	// Crear un arreglo de listas de adyacencia. El tama�o del arreglo es V
	grafo->listaAdyacencia = new AdyacenciaNodo*[V];
	
	// Inicializar cada lista de adyacencia como vac�a
	for (int i = 0; i < V; ++i)
		grafo->listaAdyacencia[i] = nullptr;
	
	return grafo;
}

void inicializarGrafoConCentral(Grafo* grafo, int nodoCentral) {
	for (int i = 0; i < grafo->numSucursales; ++i) {
		if (i != nodoCentral) { // Evitar conectar el nodo central a s� mismo
			agregarArista(grafo, nodoCentral, i, 0); // 0 es un peso default ya que es la sucursal central
		}
	}
}

// Funci�n para agregar una arista al grafo no dirigido
void agregarArista(Grafo* grafo, int src, int dest, int peso) {
	// Agregar una arista de src a dest. Un nuevo nodo se a�ade a la lista de adyacencia de src
	AdyacenciaNodo* nuevoNodo = crearNodo(dest, peso);
	nuevoNodo->siguiente = grafo->listaAdyacencia[src];
	grafo->listaAdyacencia[src] = nuevoNodo;
}

// Funci�n para mostrar las listas de adyacencia del grafo
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
			break;  // Salir si el �ndice supera el n�mero de sucursales en el grafo
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
					<< " (Kilometros: " << nodoActual->peso << ")" << endl;
			}
			
			nodoActual = nodoActual->siguiente;
		}
	}
	system("pause");
	system("cls");
}

void modificarRuta(Grafo* grafo) {
	int src, dest, peso;
	cout << "Ingrese el �ndice de la sucursal de origen: ";
	cin >> src;
	cout << "Ingrese el �ndice de la sucursal de destino: ";
	cin >> dest;
	cout << "Ingrese la distancia de la ruta: ";
	cin >> peso;
	
	agregarArista(grafo, src, dest, peso);
	cout << "Ruta modificada/a�adida exitosamente." << endl;
}


void rutaOptima() {
	cout << "En proceso de creaci�n..." << endl;
}


// Funci�n para guardar las sucursales en un archivo
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
		archivo.ignore(); // Ignorar el salto de l�nea despu�s del ID
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


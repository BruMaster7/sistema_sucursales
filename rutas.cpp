#include "sucursales.cpp"
#include "dijkstra.cpp"
#include <iostream>
#include <cstring>  // Para funciones de manejo de cadenas
#include <cstdio>   // Para funciones de entrada/salida estándar
#include <fstream>  // Para manejo de archivos
#include <sstream>
#include <string>




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
	system("cls");
	
	mostrarSucursalesConId();
	
	int idSrc, idDest, peso;
	cout << "Ingrese el ID de la sucursal de origen: ";
	cin >> idSrc;
	cout << "Ingrese el ID de la sucursal de destino: ";
	cin >> idDest;
	cout << "Ingrese la distancia de la ruta: ";
	cin >> peso;
	
	// Convertir ID a índice
	int src = obtenerIndicePorId(idSrc);
	int dest = obtenerIndicePorId(idDest);
	
	if (src == -1 || dest == -1) {
		cout << "Error: una o ambas sucursales no fueron encontradas." << endl;
		return;
	}
	
	agregarArista(grafo, src, dest, peso);
	guardarRutasEnArchivo(grafo);
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
		archivo << sucursales[i].sucursal.id << ", ";
		archivo << sucursales[i].sucursal.nombre << ", ";
		archivo << sucursales[i].sucursal.departamento << ", ";
		archivo << sucursales[i].sucursal.telefono << ", ";
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
	
	string linea;
	while (getline(archivo, linea) && contadorSucursales < MAX_SUCURSALES) {
		stringstream ss(linea);
		string idStr, nombreStr, departamentoStr, telefonoStr, responsableStr;
		
		// Leer y parsear cada campo separado por comas
		getline(ss, idStr, ',');
		sucursales[contadorSucursales].sucursal.id = stoi(idStr);
		
		getline(ss, nombreStr, ',');
		strcpy(sucursales[contadorSucursales].sucursal.nombre, nombreStr.c_str());
		
		getline(ss, departamentoStr, ',');
		strcpy(sucursales[contadorSucursales].sucursal.departamento, departamentoStr.c_str());
		
		getline(ss, telefonoStr, ',');
		strcpy(sucursales[contadorSucursales].sucursal.telefono, telefonoStr.c_str());
		
		getline(ss, responsableStr);
		strcpy(sucursales[contadorSucursales].sucursal.responsable, responsableStr.c_str());
		
		contadorSucursales++;
		if (sucursales[contadorSucursales - 1].sucursal.id >= autoIncrementalID) {
			autoIncrementalID = sucursales[contadorSucursales - 1].sucursal.id + 1;
		}
	}
	
	
	archivo.close();
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
			
			// Guardar la ruta solo si el destino es válido y tiene una sucursal asociada
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
		
		// Convertir IDs a índices
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
			return i; // Retornar el índice si encuentra la sucursal	
		}
	}
	return -1; // Retornar -1 si no se encuentra la sucursal
}

void mostrarSucursalesConId() {
	cout << "IDs de las Sucursales registradas:" << endl;
	for (int i = 0; i < contadorSucursales; i++) {
		cout << "ID: " << sucursales[i].sucursal.id
			<< " -" << sucursales[i].sucursal.nombre << endl;
	}
}

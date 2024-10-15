#include "cabezales.h"

#include <iostream>
#include <cstring>  // Para funciones de manejo de cadenas
#include <cstdio>   // Para funciones de entrada/salida estándar
#include <fstream>  // Para manejo de archivos
#include <sstream>


using namespace std;

// Definición de las variables globales
Nodo sucursales[MAX_SUCURSALES];
int contadorSucursales = 0;
int autoIncrementalID = 1;

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
	cout << "Ingrese el ID de la sucursal: " << endl;
	cin >> id;
	return id;
}
//Void para cuando no se encuentra la ID que seleccionó el usuario
void IdNoEncontrada(int id){
	cout << "**************************************" << endl;
	cout << "Sucursal con ID " << id << " no encontrada" << endl;
	cout << "**************************************" << endl;
	system("pause");
	system("cls");
}

void mostrarSucursalesConId() {
		cout << "IDs de las Sucursales actuales:" << endl;
		for (int i = 0; i < contadorSucursales; i++) {
			cout << "ID: " << sucursales[i].sucursal.id
				<< " -" << sucursales[i].sucursal.nombre << endl;
		}
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
	guardarSucursalesEnArchivo();
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
			guardarSucursalesEnArchivo();
			system("pause");
			system("cls");
			return;
		}
	}
	IdNoEncontrada(id);
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
			guardarSucursalesEnArchivo();
			system("pause");
			system("cls");
			return;
		}
	}
	IdNoEncontrada(id);
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


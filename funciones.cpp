#include <iostream>
#include <cstring>  // Para funciones de manejo de cadenas
#include <cstdio>   // Para funciones de entrada/salida est�ndar
#include "cabezales.h"
using namespace std;

#define MAX_SUCURSALES 100

// Declaraci�n global para el ID auto-incremental
int autoIncrementalID = 1;

Nodo sucursales[MAX_SUCURSALES];
int contadorSucursales = 0;

// Men� de sucursales
void sucursalmenu() {
	int opmenu;
	int id;
	cout << "**************************************" << endl;
	cout << "*    Mantenimiento de sucursales     *" << endl;
	cout << "*Seleccione que acci�n desea realizar*" << endl;
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
		cout << "Esa opci�n no est� disponible, elija otra por favor" << endl;
		system("pause");
		system("cls");
	}
}

// Men� principal
void menu() {
	int opmenu;
	do {
		cout << "**************************************" << endl;
		cout << "*    Mantenimiento de sucursales     *" << endl;
		cout << "*Seleccione que acci�n desea realizar*" << endl;
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
			rutasActuales();
			break;
		case 3:
			modificarRuta();
			break;
		case 4:
			rutaOptima();
			break;
		case 6:
			cout << "Adi�s\n";
			break;
		default:
			cout << "Esa opci�n no est� disponible, elija otra por favor" << endl;
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
		cout << "Tel�fono: " << sucursales[i].sucursal.telefono << endl;
		cout << "Responsable: " << sucursales[i].sucursal.responsable << endl;
		cout << "**************************************" << endl;
	}
	system("pause");
	system("cls");
}

// Funci�n para ingresar el ID
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
		cout << "No se pueden agregar m�s sucursales, el l�mite ha sido alcanzado." << endl;
		cout << "*****************************************************************" << endl;
		system("pause");
		system("cls");
		return;
	}
	
	cout << "*************************************" << endl;
	sucursales[contadorSucursales].sucursal.id = autoIncrementalID++; // Asignaci�n de ID auto-incremental
	cout << "Ingrese el nombre de la sucursal: ";
	cin.ignore(); // Limpiar el buffer de entrada
	cin.getline(sucursales[contadorSucursales].sucursal.nombre, 100);
	cout << "Ingrese el departamento de la sucursal: ";
	cin.getline(sucursales[contadorSucursales].sucursal.departamento, 50);
	cout << "Ingrese el tel�fono de la sucursal: ";
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
			cout << "Modificar Tel�fono (Actual: " << sucursales[i].sucursal.telefono << "): ";
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

// Funciones de rutas
void rutasActuales() {
	cout << "Rutas actuales no implementadas." << endl;
}

void modificarRuta() {
	cout << "En proceso de creaci�n..." << endl;
}

void rutaOptima() {
	cout << "En proceso..." << endl;
}


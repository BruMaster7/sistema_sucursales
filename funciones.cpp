#include <iostream>
#include <stdio.h>
#include <string.h>
#include "cabezales.h"
using namespace std;

#define MAX_SUCURSALES 100



Nodo sucursales[MAX_SUCURSALES];
int contadorSucursales = 0;

void sucursalmenu() {
	int opmenu;
	int id;
	cout<<"**************************************"<<endl;
	cout<<"*    Mantenimiento de sucursales     *"<<endl;
	cout<<"*Seleccione que acción desea realizar*"<<endl;
	
	cout<<"*1-Sucursales actuales               *"<<endl;
	cout<<"*2-Agregar sucursal                  *"<<endl;
	cout<<"*3-Modificar sucursal                *"<<endl;
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
		cout<<"Esa opción no está disponible, elija otra por favor"<<endl;
		system ("pause");
		system("cls");
	}
	
	
	
}



void menu() {
	int opmenu;
	int id; // Sacar al final
	do {
		cout<<"**************************************"<<endl;
		cout<<"*    Mantenimiento de sucursales     *"<<endl;
		cout<<"*Seleccione que acción desea realizar*"<<endl;

		cout<<"*1-Eliminar Sucursal                 *"<<endl;
		cout<<"*2-Ver rutas actuales                *"<<endl;
		cout<<"*3-Modificar ruta                    *"<<endl;
		cout<<"*4-Buscar ruta optima                *"<<endl;
		cout<<"*8-Salir                             *"<<endl;
		cout<<"**************************************"<<endl;
		cin >> opmenu;
		switch (opmenu) {
		case 1: 
			sucursalmenu();
			break;
		case 3:
			rutasActuales();
			break;
		case 4:
			modificarRuta();
			break;
		case 5:
			rutaOptima();
			break;
		case 6:
			cout<<"Adiós\n";
			break;
		default:
			cout<<"Esa opción no está disponible, elija otra por favor"<<endl;
			system ("pause");
			system("cls");
		}
	} while(opmenu != 6);
}

void sucursalesActuales() {
	if (contadorSucursales == 0) {
		
		cout<<"**************************************"<<endl;
		cout<<"*No hay sucursales registradas.      *"<<endl;
		cout<<"**************************************"<<endl;
		system ("pause");
		system("cls");
		return;
	}
	
	for (int i = 0; i < contadorSucursales; i++) {
		cout<<"**************************************"<<endl;
		cout<<"ID: "<< sucursales[i].sucursal.id<<endl;
		cout<<"Nombre: "<< sucursales[i].sucursal.nombre<<endl;
		cout<<"Departamento: "<< sucursales[i].sucursal.departamento<<endl;
		cout<<"Teléfono: "<< sucursales[i].sucursal.telefono<<endl;
		cout<<"Responsable: "<< sucursales[i].sucursal.responsable<<endl;
		cout<<"**************************************"<<endl;
	}
	system ("pause");
	system("cls");
}

int ingresarId(){
	int id;
	cout<<"Ingrese el ID de la sucursal que desea modificar: "<<endl;
	cin>>id;
	return id;
}
	
	void agregarSucursal() {
		if (contadorSucursales >= MAX_SUCURSALES) {
			cout<<"*****************************************************************"<<endl;
			cout<<"No se pueden agregar más sucursales, el límite ha sido alcanzado."<<endl;
			cout<<"*****************************************************************"<<endl;
			system ("pause");
			system("cls");
			return;
		}
		cout<<"*************************************"<<endl;
		cout<<"Ingrese la id de la sucursal: ";
		cin>>sucursales[contadorSucursales].sucursal.id;
		cout<<"Ingrese el nombre de la sucursal: ";
		cin>>sucursales[contadorSucursales].sucursal.nombre;
		cout<<"Ingrese el departamento de la sucursal: ";
		cin>>sucursales[contadorSucursales].sucursal.departamento;
		cout<<"Ingrese el teléfono de la sucursal: ";
		cin>>sucursales[contadorSucursales].sucursal.telefono;
		cout<<"Ingrese el nombre del responsable: ";
		cin>>sucursales[contadorSucursales].sucursal.responsable;
		cout<<"*************************************"<<endl;
		contadorSucursales = contadorSucursales+1;
		system ("pause");
		system("cls");
	}
	
	void modificarSucursal(int id) {
		for (int i = 0; i < contadorSucursales; i++) {
			if (sucursales[i].sucursal.id == id) {
				cout<<"***************************************************************"<<endl;
				cout<<"Modificar Nombre (Actual: "<< sucursales[i].sucursal.nombre<<"):";
				cin>>sucursales[i].sucursal.nombre;
				cout<<"Modificar Departamento (Actual: "<< sucursales[i].sucursal.departamento<<"):";
				cin>>sucursales[i].sucursal.departamento;
				
				cout<<"Modificar Teléfono (Actual: "<< sucursales[i].sucursal.telefono<<"):";
				cin>>sucursales[i].sucursal.telefono;
				
				cout<<"Modificar Responsable (Actual: "<< sucursales[i].sucursal.responsable<<"):";
				cin>>sucursales[i].sucursal.responsable;
				cout<<"****************************************************************"<<endl;
				system ("pause");
				system("cls");
				return;
			}
		} 
		system ("pause");
		system("cls");
		cout<<"**************************************"<<endl;
		cout<<"Sucursal con ID "<<id<<" no encontrada"<<endl;
		cout<<"**************************************"<<endl;
		system ("pause");
		system("cls");
	}
	
	void eliminarSucursal(int id) {
		
		for (int i = 0; i < contadorSucursales; i++) {
			if (sucursales[i].sucursal.id == id) {
				for (int j = i; j < contadorSucursales - 1; j++) {
					sucursales[j] = sucursales[j + 1];
				}
				contadorSucursales--;
				cout<<"Sucursal con ID "<<id<<" eliminada"<<endl;
				system ("pause");
				system("cls");
				return;
			}
		}
		cout<<"**************************************"<<endl;
		cout<<"Sucursal con ID "<<id<<" no encontrada"<<endl;
		cout<<"**************************************"<<endl;
		system ("pause");
		system("cls");
	}
	
	void rutasActuales() {
		cout<<"ola"<<endl;
	}
	
	void modificarRuta() {
		cout<<"hola"<<endl;
	}
	
	void rutaOptima() {
		cout<<"Fjils"<<endl;
	}
	
	


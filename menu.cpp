#include "rutas.cpp"
#include <iostream>

using namespace std;

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
		guardarSucursalesEnArchivo(); // Guardar después de agregar
		break;
	case 3:
		id = ingresarId();
		modificarSucursal(id);
		guardarSucursalesEnArchivo(); // Guardar después de modificar
		break;
	case 4:
		id = ingresarId();
		eliminarSucursal(id);
		guardarSucursalesEnArchivo(); // Guardar después de eliminar
		break;
	default:
		cout << "Esa opción no está disponible, elija otra por favor" << endl;
		system("pause");
		system("cls");
	}
}

// Menú principal
void menu() {
	cargarSucursalesDesdeArchivo(); // Cargar sucursales al iniciar el programa
	Grafo* grafo = crearGrafo(MAX_SUCURSALES);
	
	int nodoCentral = 0; // El nodo central puede ser el primero, o el que elijas, generalmente el de indice 0
	inicializarGrafoConCentral(grafo, nodoCentral);
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
			rutaOptima(grafo);
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


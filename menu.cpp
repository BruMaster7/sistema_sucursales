#include "rutas.cpp"
#include <iostream>

using namespace std;

//Menú de rutas
void rutasMenu(Grafo* grafo){
	int opmenu; //variable que toma la elección del usuario
	do{
		cout << "**************************************" << endl;
		cout << "*    Mantenimiento de rutas          *" << endl;
		cout << "*Seleccione que acción desea realizar*" << endl;
		cout << "*1-Rutas actuales                    *" << endl;
		cout << "*2-Agregar/Modificar ruta            *" << endl;
		cout << "*3-Eliminar ruta                     *" << endl;
		cout << "*4-Volver a menú                     *" << endl;
		cout << "**************************************" << endl;
		cin >> opmenu;
		switch (opmenu) {
		case 1:
			rutasActuales(grafo); //me muestra las rutas actuales
			break;
		case 2:
			modificarRuta(grafo); //me permitirá modificar una ruta ya existente o agregarla si no existe
			break;
		case 3:
			eliminarRuta(grafo); //me permitirá eliminar una ruta ya existente
			break;
		case 4:
			system("pause"); 
			system("cls"); //me devuelve al menú
			break;
		default:
			cout << "Esa opción no está disponible, elija otra por favor" << endl;
			system("pause");
			system("cls");
		}
	}while(opmenu !=4);
}
	

// Menú de sucursales
void sucursalMenu(){ //menú de sucursales
	int opmenu; //variable que toma la elección del usuario
	int id;
	do{	
		cout << "**************************************" << endl;
		cout << "*    Mantenimiento de sucursales     *" << endl;
		cout << "*Seleccione que acción desea realizar*" << endl;
		cout << "*1-Sucursales actuales               *" << endl;
		cout << "*2-Agregar sucursal                  *" << endl;
		cout << "*3-Modificar sucursal                *" << endl;
		cout << "*4-Eliminar sucursal                 *" << endl;
		cout << "*5-Volver a menú                     *" << endl;
		cout << "**************************************" << endl;
		cin >> opmenu;
		switch (opmenu) {
		case 1:
			sucursalesActuales(); //mostrará las sucursales actuales
			break;
		case 2:
			mostrarSucursalesConId();
			agregarSucursal(); //me permitirá agregar una sucursal nueva
			break;
		case 3:
			mostrarSucursalesConId();
			id = ingresarId();
			modificarSucursal(id); //me permitirá modificar una sucursal que ya existe
			break;
		case 4:
			mostrarSucursalesConId();
			id = ingresarId();
			eliminarSucursal(id); //me permitirá eliminar una sucursal que ya existe
			break;
		case 5:
			system("pause");
			system("cls"); //vuelvo al menú principal
			break;
		default:
			cout << "Esa opción no está disponible, elija otra por favor" << endl;
			system("pause");
			system("cls");
		}
	} while (opmenu !=5);
}

// Menú principal
void menu() {
	cargarSucursalesDesdeArchivo();// Cargar sucursales al iniciar el programa
	Grafo* grafo = crearGrafo(MAX_SUCURSALES);

	cargarRutasDesdeArchivo(grafo);
	int opmenu;
	do {
		cout << "**************************************" << endl;
		cout << "*    Mantenimiento de sucursales     *" << endl;
		cout << "*Seleccione que acción desea realizar*" << endl;
		cout << "*1-Gestionar Sucursales              *" << endl;
		cout << "*2-Gestionar Rutas                   *" << endl;
		cout << "*3-Buscar ruta optima                *" << endl;
		cout << "*4-Salir                             *" << endl;
		cout << "**************************************" << endl;
		cin >> opmenu;
		switch (opmenu) {
		case 1:
			sucursalMenu();
			break;
		case 2:
			rutasMenu(grafo);
			break;
		case 3:
			mostrarSucursalesConId();
			rutaOptima(grafo);
			break;
		case 4:
			cout << "Gracias por utilizar el sistema de gestion de sucursales\n";
			break;
		default:
			cout << "Esa opción no está disponible, elija otra por favor" << endl;
			system("pause");
			system("cls");
		}
	} while (opmenu != 4);
}


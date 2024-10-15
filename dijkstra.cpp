#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> iPair;

// Function to print shortest paths from source
void shortestPath(Grafo* grafo, int src) {
	priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
	vector<int> dist(contadorSucursales, INF), prev(contadorSucursales, -1);
	
	pq.push({0, src});
	dist[src] = 0;
	
	while (!pq.empty()) {
		int u = pq.top().second;
		pq.pop();
		
		for (auto &neighbor : grafo->listaAdyacencia[u]) {
			int v = neighbor->destino, weight = neighbor->peso;
			
			if (dist[v] > dist[u] + weight) {
				dist[v] = dist[u] + weight;
				prev[v] = u; 
				pq.push({dist[v], v});
			}
		}
	}
	
	int idDest;
	cout << "¿A qué sucursal deseas ir? (Ingresa el ID de la sucursal)" << endl;
	cin >> idDest;
	int dest = obtenerIndicePorId(idDest);
	if (idDest == 1){
		cout<<"No hay camino desde la central hacia si misma\n";
		system("pause");
		system("cls");
		return;
	}
	if (dest == -1) {
		cout << "Error: la sucursal no fue encontrada" << endl;
		system("pause");
		system("cls");
		return;
	}
	
	cout << "El camino más corto hacia la sucursal " << sucursales[dest].sucursal.nombre <<" es de: " << dist[dest] << " kilómetros" << endl;
	
	vector<int> path;
	for (int v = dest; v != -1; v = prev[v]) {
		path.push_back(v);
	}
	reverse(path.begin(), path.end());
	
	cout << "El camino es: \n";
	for (size_t i = 0; i < path.size(); ++i) {
		cout << sucursales[path[i]].sucursal.nombre;
		if (i < path.size() - 1) {
			int next = path[i + 1], distance = INF;
			for (auto &neighbor : grafo->listaAdyacencia[path[i]]) {
				if (neighbor->destino == next) {
					distance = neighbor->peso;
					break;
				}
			}
			cout << " -> Distancia hasta " << sucursales[next].sucursal.nombre << ": " << distance << " kilómetros" << endl;
		} else {
			cout << endl;
		}
	}
	
	system("pause");
	system("cls");
}

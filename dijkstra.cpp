#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> iPair;

// Function to print shortest paths from source
void shortestPath(Grafo* grafo, int src) {
	// Create a priority queue to store vertices being processed
	// Priority queue sorted by the first element of the pair (distance)
	priority_queue<iPair, vector<iPair>, greater<iPair>> pq;
	
	// Create a vector to store distances and initialize all distances as INF
	vector<int> dist(contadorSucursales, INF);
	
	// Insert source into priority queue and initialize its distance as 0
	pq.push(make_pair(0, src));
	dist[src] = 0;
	// Process the priority queue
	while (!pq.empty()) {
	
		// Get the vertex with the minimum distance
		int u = pq.top().second;
		pq.pop();
		
		// Iterate through all adjacent vertices of the current vertex
		
			for (auto &neighbor : grafo->listaAdyacencia[u]) {
				if (grafo->listaAdyacencia[u].empty()) {
					return;
				}
			
				int v = neighbor->destino;
				
				int weight = neighbor->peso;
				
				// If a shorter path to v is found
				if (dist[v] > dist[u] + weight) {
					// Update distance and push new distance to the priority queue
					dist[v] = dist[u] + weight;
					pq.push(make_pair(dist[v], v));
				}
			}
		
	}
	
	// Print the shortest distances
	cout << "El camino mas corto entre las sucursales es: " << endl;
	for (int i = 0; i < contadorSucursales; ++i)
		cout << i << " \t\t " << dist[i] << "kilometros" << endl;
	
	system("pause");
	system("cls");
}


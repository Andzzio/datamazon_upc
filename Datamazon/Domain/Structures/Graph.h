#pragma once
#include "SimpleList.h"
#include <windows.h>
#include <iostream>

template <typename T>
class Graph {
public:
    struct Edge {
        int dest;
        int weight;
    };

private:
    int V;
    T* vertices;
    int* posX;
    int* posY;
    SimpleList<Edge>* adj;

    int absolute(int val) {
        return (val < 0) ? -val : val;
    }

    template <typename Funcion>
    void dfsHelper(int u, bool* visited, Funcion lambda) {
        visited[u] = true;
        lambda(u);
        for (typename SimpleList<Edge>::Iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
            int v = (*it).dest;
            if (!visited[v]) {
                dfsHelper(v, visited, lambda);
            }
        }
    }

public:
    Graph(int verticesCount) {
        V = verticesCount;
        vertices = new T[V];
        posX = new int[V];
        posY = new int[V];
        adj = new SimpleList<Edge>[V];
        for (int i = 0; i < V; ++i) {
            posX[i] = 0;
            posY[i] = 0;
        }
    }

    ~Graph() {
        delete[] vertices;
        delete[] posX;
        delete[] posY;
        delete[] adj;
    }

    void addEdge(int u, int v, int weight, bool bidirectional = true) {
        Edge edge1 = { v, weight };
        adj[u].addBack(edge1);
        if (bidirectional) {
            Edge edge2 = { u, weight };
            adj[v].addBack(edge2);
        }
    }

    void setVertex(int id, T info, int x, int y) {
        if (id >= 0 && id < V) {
            vertices[id] = info;
            posX[id] = x;
            posY[id] = y;
        }
    }

    T getVertex(int id) const {
        if (id >= 0 && id < V) {
            return vertices[id];
        }
        return T();
    }

    int getVertexX(int id) const {
        if (id >= 0 && id < V) return posX[id];
        return 0;
    }

    int getVertexY(int id) const {
        if (id >= 0 && id < V) return posY[id];
        return 0;
    }

    int getV() const { return V; }

    SimpleList<Edge>& getAdj(int u) { return adj[u]; }

    int dijkstra(int start, int end, int* path, int& pathLength) {
        int* dist = new int[V];
        bool* visited = new bool[V];
        int* parent = new int[V];

        for (int i = 0; i < V; ++i) {
            dist[i] = 1000000000;
            visited[i] = false;
            parent[i] = -1;
        }

        dist[start] = 0;

        for (int count = 0; count < V; ++count) {
            int u = -1;
            int minDist = 1000000000;

            for (int i = 0; i < V; ++i) {
                if (!visited[i] && dist[i] < minDist) {
                    minDist = dist[i];
                    u = i;
                }
            }

            if (u == -1 || minDist == 1000000000) {
                break;
            }

            visited[u] = true;

            if (u == end) {
                break;
            }

            for (typename SimpleList<Edge>::Iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
                int v = (*it).dest;
                int weight = (*it).weight;

                if (!visited[v] && dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                }
            }
        }

        int totalDistance = dist[end];

        if (totalDistance == 1000000000) {
            pathLength = 0;
            delete[] dist;
            delete[] visited;
            delete[] parent;
            return -1;
        }

        int* tempPath = new int[V];
        int tempLength = 0;
        int curr = end;

        while (curr != -1) {
            tempPath[tempLength++] = curr;
            curr = parent[curr];
        }

        pathLength = tempLength;
        for (int i = 0; i < tempLength; ++i) {
            path[i] = tempPath[tempLength - 1 - i];
        }

        delete[] tempPath;
        delete[] dist;
        delete[] visited;
        delete[] parent;

        return totalDistance;
    }

    template <typename Funcion>
    void bfs(int start, Funcion lambda) {
        bool* visited = new bool[V];
        for (int i = 0; i < V; ++i) {
            visited[i] = false;
        }

        int* queue = new int[V];
        int head = 0;
        int tail = 0;

        queue[tail++] = start;
        visited[start] = true;

        while (head < tail) {
            int u = queue[head++];
            lambda(u);

            for (typename SimpleList<Edge>::Iterator it = adj[u].begin(); it != adj[u].end(); ++it) {
                int v = (*it).dest;
                if (!visited[v]) {
                    visited[v] = true;
                    queue[tail++] = v;
                }
            }
        }

        delete[] visited;
        delete[] queue;
    }

    template <typename Funcion>
    void dfs(int start, Funcion lambda) {
        bool* visited = new bool[V];
        for (int i = 0; i < V; ++i) {
            visited[i] = false;
        }
        dfsHelper(start, visited, lambda);
        delete[] visited;
    }
};

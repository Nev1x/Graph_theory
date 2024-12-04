#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Структура для представления ребра
struct Edge {
    int u, v, weight;
    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

// Класс для реализации Union-Find (DSU)
class UnionFind {
private:
    vector<int> parent, rank;
public:
    UnionFind(int n) {
        parent.resize(n);
        rank.resize(n, 0);
        for (int i = 0; i < n; i++) {
            parent[i] = i;
        }
    }

    // Найти корень множества с сжатием путей
    int find(int x) {
        if (parent[x] != x) {
            parent[x] = find(parent[x]);
        }
        return parent[x];
    }

    // Объединить два множества
    bool unite(int x, int y) {
        int rootX = find(x);
        int rootY = find(y);
        if (rootX != rootY) {
            if (rank[rootX] < rank[rootY]) {
                swap(rootX, rootY);
            }
            parent[rootY] = rootX;
            if (rank[rootX] == rank[rootY]) {
                rank[rootX]++;
            }
            return true;
        }
        return false;
    }
};

// Алгоритм Краскала
int kruskal(int n, vector<Edge>& edges) {
    sort(edges.begin(), edges.end()); // Сортировка рёбер по весу
    UnionFind uf(n);
    int mstWeight = 0;

    for (const auto& edge : edges) {
        if (uf.unite(edge.u, edge.v)) { // Если вершины не в одном компоненте связности
            mstWeight += edge.weight;
            cout << "Ребро включено в MST: (" << edge.u << ", " << edge.v << ") с весом " << edge.weight << endl;
        }
    }

    return mstWeight;
}

int main() {
    int n = 5; // Число вершин
    vector<Edge> edges = {
            {0, 1, 10}, {0, 2, 6}, {0, 3, 5},
            {1, 3, 15}, {2, 3, 4}
    };

    cout << "Общий вес минимального остовного дерева: " << kruskal(n, edges) << endl;

    return 0;
}

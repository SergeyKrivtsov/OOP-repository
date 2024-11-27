#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Функція для пошуку всіх шляхів
void findAllPaths(int current, int end, vector<vector<int>>& graph, vector<bool>& visited, vector<int>& path, vector<vector<int>>& allPaths) {
    // Додаємо поточну вершину до шляху
    path.push_back(current);

    // Якщо досягли кінцевої вершини
    if (current == end) {
        allPaths.push_back(path);
    }
    else {
        // Перебираємо сусідів
        for (int neighbor : graph[current]) {
            if (!visited[neighbor]) { // Уникаємо циклів
                visited[neighbor] = true;
                findAllPaths(neighbor, end, graph, visited, path, allPaths);
                visited[neighbor] = false; // Повертаємося
            }
        }
    }

    // Видаляємо поточну вершину зі шляху
    path.pop_back();
}

int main() {
    // Граф заданий у вигляді списку суміжності
    vector<vector<int>> graph = {
        {},          // Вершина 0 (не використовується)
        {2, 3},      // Вершина 1 -> 2, 3
        {4, 5},      // Вершина 2 -> 4, 5
        {2, 6},      // Вершина 3 -> 2, 6
        {6},         // Вершина 4 -> 6
        {6},         // Вершина 5 -> 6
        {3, 5}       // Вершина 6 -> 3, 5
    };

    int start = 1, end = 6; // Початкова і кінцева вершини

    // Масив для збереження, чи відвідана вершина
    vector<bool> visited(graph.size(), false);
    visited[start] = true;

    vector<int> path;                 // Поточний шлях
    vector<vector<int>> allPaths;     // Усі знайдені шляхи

    // Викликаємо функцію для пошуку всіх шляхів
    findAllPaths(start, end, graph, visited, path, allPaths);

    // Виводимо всі знайдені шляхи
    cout << "Усі шляхи від вершини " << start << " до вершини " << end << ":\n";
    for (const auto& p : allPaths) {
        for (int node : p) {
            cout << node << " ";
        }
        cout << endl;
    }

    return 0;
}

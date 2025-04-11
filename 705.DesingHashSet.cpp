#include <vector>
#include <list>  

class MyHashSet {
private:
    static const int SIZE = 1009; // Tamaño de la tabla hash (se elige un número primo para reducir colisiones)
    std::vector<std::list<int>> table; // Tabla hash: vector de listas (cada lista es un bucket)

    // Función hash simple: toma una clave y devuelve un índice dentro de los límites de la tabla.
    int hash(int key) {
        return key % SIZE;
    }

public:
    // Constructor: inicializa la tabla con SIZE buckets vacíos.echo "# 705.HashSet" >> README.md
    MyHashSet() {
        table.resize(SIZE);
    }
    
    // Método para añadir una clave al conjunto
    void add(int key) {
        int idx = hash(key); // Obtener el índice de la tabla
        // Verificar si la clave ya está presente en el bucket correspondiente
        for (int val : table[idx]) {
            if (val == key) return; // Si ya existe, no se agrega de nuevo
        }
        table[idx].push_back(key); // Si no existe, se agrega al bucket
    }
    
    // Método para eliminar una clave del conjunto
    void remove(int key) {
        int idx = hash(key); // Obtener el índice correspondiente
        table[idx].remove(key); // Elimina la clave si existe (si no, no hace nada)
    }
    
    // Método para verificar si una clave existe en el conjunto
    bool contains(int key) {
        int idx = hash(key); // Obtener el índice correspondiente
        // Buscar la clave en el bucket
        for (int val : table[idx]) {
            if (val == key) return true; // La clave fue encontrada.
        }
        return false; // No se encontró la clave.
    }
};

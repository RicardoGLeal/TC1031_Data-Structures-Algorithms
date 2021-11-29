/*
TC1031 Programaci�n de estructuras de datos y algoritmos fundamentales (Gpo 13)
Act 4.2 - Grafos: Algoritmos complementarios
La funci�n de este programa es recibir un grafo dirigido (DAG), con "n" vertices y "m" arcos, y determinar si el grafo
es un �rbol. As�mismo se despliega su orden topol�gico
Autor: Ricardo Gonz�lez Leal, A01639036
Fecha de creaci�n: 12/11/21
*/

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <set>

using namespace std;

class Grafo {
public:
    // La lista de adjacencia est� conformada por un hashmap que tiene un valor string para la llave y un set de strings
    // como valores. 
    map<string, set<string>> listaAdj;

    // N�mero de nodos y arcos.
    int n;
    int m;

    Grafo() {
    }

    /// <summary>
    /// Carga los valores del n�mero de arcos y el n�mero de nodos. 
    /// </summary>
    /// <param name="n">N�mero de arcos</param>
    /// <param name="m">N�mero de nodos</param>
    void loadGraph(int n, int m) {
        this->n = n;
        this->m = m;
    }

    /// <summary>
    /// Crea un nuevo arco entre el nodo A y el nodo B.
    /// </summary>
    /// <param name="a">Nodo A</param>
    /// <param name="b">Nodo B</param>
    void addEdge(string a, string b) {
        listaAdj[a].insert(b);
    }

    /// <summary>
    /// Esta funci�n despliega el orden topol�gico del grafo. 
    /// Complejidad: O(n)
    /// </summary>
    void imprimir() {
        for (auto const& x : listaAdj)
        {
            cout << x.first  // string (key)
                << ": ";
            for (auto y : x.second) {
                cout << y << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    /// <summary>
    /// Esta funci�n utiliza el algoritmo Depth First Traversal para detectar si hay ciclos en el grafo, checando 
    /// de manera recursiva los back edges de cada nodo.
    /// Complejidad: O(n+m) 
    /// </summary>
    /// <param name="node"> Nodo actual que se est� visitando </param>
    /// <param name="visited"> Almacena los nodos que ya fueron visitados. </param>
    /// <param name="recurtionStack">Almacena los nodos que se van recorriendo recursivamente.</param>
    /// <returns> Si se encontr� un ciclo o no /returns>
    bool DFS(string node, set<string>& visited, set<string>& recurtionStack) {
        if (recurtionStack.find(node) != recurtionStack.end()) 
            return false;
        visited.insert(node);
        recurtionStack.insert(node);
        for (auto x : listaAdj[node])
        {
            bool res = DFS(x, visited, recurtionStack);
            if (!res)
                return false;
        }
        return true;
    }

    /// <summary>
    /// Se encarga de comprobar si el grafo es un �rbol 
    /// Complejidad: O(n(m+n))
    /// </summary>
    /// <returns>True si es un �rbol, False si no es un �rbol</returns>
    bool isTree() {
        set<string> visited;
        // Se itera sobre los nodos en la lista de adyacencia
        for (auto const& node : listaAdj) {
            set<string> recurtionStack;
            // Si se encuentra que en los nodos visitados est� el nodo actual, el cu�l es igual al �ltimo visitado..
            if (visited.find(node.first) == visited.end()) {
                bool found = DFS(node.first, visited, recurtionStack);
                if (!found)
                    return false;
            }
        }
        return true;
    }
};

/// <summary>
/// Ejecuta el primer caso de prueba
/// </summary>
void caso1() {
    Grafo graph;
    cout << "Caso 1:" << endl;
    graph.addEdge("A", "B");
    graph.addEdge("A", "C");
    graph.addEdge("A", "D");
    graph.addEdge("B", "D");
    graph.addEdge("B", "E");
    graph.addEdge("C", "E");
    graph.addEdge("D", "E");
    graph.loadGraph(5, 7);
    graph.imprimir();
    if (graph.isTree())
        cout << "Este grafo Si es un arbol" << endl;
    else
        cout << "Este grafo No es un arbol" << endl;
}

/// <summary>
/// Ejecuta el segundo caso de prueba
/// </summary>
void caso2() {
    Grafo graph;
    cout << "Caso 2:" << endl;
    graph.addEdge("A", "B");
    graph.addEdge("B", "C");
    graph.addEdge("A", "C");
    graph.addEdge("C", "D");
    graph.loadGraph(4, 4);
    graph.imprimir();
    if (graph.isTree())
        cout << "Este grafo Si es un arbol" << endl;
    else
        cout << "Este grafo No es un arbol" << endl;
}

/// <summary>
/// Ejecuta el tercer caso de prueba
/// </summary>
void caso3() {
    Grafo graph;
    cout << "Caso 3:" << endl;
    graph.addEdge("A", "B");
    graph.addEdge("B", "C");
    graph.addEdge("A", "C");
    graph.addEdge("C", "A");
    graph.addEdge("C", "D");
    graph.addEdge("D", "D");
    graph.loadGraph(4, 6);
    graph.imprimir();
    if (graph.isTree())
        cout << "Este grafo Si es un arbol" << endl;
    else
        cout << "Este grafo No es un arbol" << endl;
}

/// <summary>
/// Ejecuta el cuarto caso de prueba
/// </summary>
void caso4() {
    Grafo graph;
    cout << "Caso 4:" << endl;
    graph.addEdge("A", "B");
    graph.addEdge("A", "C");
    graph.addEdge("B", "D");
    graph.addEdge("B", "E");
    graph.addEdge("C", "F");
    graph.addEdge("C", "G");
    graph.loadGraph(6, 6);
    graph.imprimir();
    if (graph.isTree())
        cout << "Este grafo Si es un arbol" << endl;
    else
        cout << "Este grafo No es un arbol" << endl;
}

/// <summary>
/// Le pregunta al usuario por el n�mero del caso a comprobar.
/// </summary>
int main() {
    int option = 0;
    cout << "Selecciona un caso (1-4)" << endl;
    cin >> option;
    switch (option)
    {
    case 1:
        caso1();
        break;
    case 2:
        caso2();
        break;
    case 3:
        caso3();
        break;
    case 4:
        caso4();
        break;
    default:
        break;
    }
}
/*
TC1031 Programación de estructuras de datos y algoritmos fundamentales (Gpo 13)
Act 3.2 - Árbol Heap: Implementando una fila priorizada
Este programa contiene los métodos básicos de un Árbol Heap (con una fila priorizada), como lo son:
push(), top() y pop(). Asímismo se generan con números aleatorios 4 filas priorizadas.
Autor: Ricardo González Leal, A01639036
Fecha de creación: 15/10/21
*/

#include <iostream>
#include <vector>
#include <math.h>

using namespace std;

template <class T> class priority_queue {
public:
	vector<T> heapTree;

	/// <summary>
	/// Regresa el índice del hijo izquierdo del nodo.
	/// Tiempo de complejidad O (1). 
	/// </summary>
	/// <param name="i">Nodo actual</param>
	/// <returns>índice del nodo izquierdo</returns>
	int left(int i) { return (2 * i + 1); }

	/// <summary>
	/// Regresa el índice del hijo derecho del nodo.
	/// Tiempo de complejidad O (1). 
	/// </summary>
	/// <param name="i">Nodo actual</param>
	/// <returns>índice del nodo derecho</returns>
	int right(int i) { return (2 * i + 2); }

	/// <summary>
	/// Regresa el índice del nodo padre
	/// Tiempo de complejidad O (1). 
	/// </summary>
	/// <param name="i">Nodo actual</param>
	/// <returns>índice del nodo padre</returns>
	int parent(int i) { return (i - 1) / 2; }

	/// <summary>
	/// Esta función se encarga de iterar en la fila priorizada tras haber eliminado el nodo máximo,
	/// acomodando los nodos nuevamente navegando hacia abajo y comprobando si son mayores.
	/// Tiempo de complejidad O log (n). 
	/// </summary>
	/// <param name="i">índice del nodo a comprobar si está en la posición correcta</param>
	/// <param name="heapTree">fila priorizada</param>
	void MaxHeapify(int i, vector<int>& heapTree) {

		// Se obtienen los nodos hijos izquierdo y derecho
		int l = left(i);
		int r = right(i);

		int biggest = i;

		// Se comprueba si el nodo de la izquierda es mayor que el actual.
		if (l < heapTree.size() && heapTree[l] > heapTree[i])
			biggest = l;

		// Se comprueba si el nodo de la izquierda es mayor que el actual.
		if (r < heapTree.size() && heapTree[r] > heapTree[biggest])
			biggest = r;

		// Si el valor mayor no corresponde al del nodo actual, se realiza un intercambio.
		if (biggest != i)
		{
			// Se realiza el intercambio y se vuelve 
			swap(heapTree[i], heapTree[biggest]);
			MaxHeapify(biggest, heapTree);
		}
	}

	/// <summary>
	/// Saca de la fila priorizada el dato que tiene mayor prioridad
	/// Tiempo de complejidad O log (n). 
	/// </summary>
	int pop() {
		if (!empty()) {
			// El último valor se convierte en el primero (root)
			heapTree[0] = heapTree[heapTree.size() - 1];
			heapTree.pop_back();
			MaxHeapify(0, heapTree);
		}
		else {
			return -1;
		}
	}

	/// <summary>
	/// Regresa el valor del dato que esta con mayor prioridad en la fila priorizada.
	/// Tiempo de complejidad O (1). 
	/// </summary>
	/// <returns>El dato que tiene mayor prioridad dentro de la Fila priorizada</returns>
	int top() {
		return heapTree[0];
	}

	/// <summary>
	/// Regresa un valor boleando diciendo si la fila priorizada esta vacía o tiene datos.
	/// Tiempo de complejidad O (1). 
	/// </summary>
	/// <returns>True si está vacío</returns>
	bool empty() {
		return !(heapTree.size() > 0);
	}

	/// <summary>
	/// Regresa la cantidad de datos que tiene la fila priorizada
	/// Tiempo de complejidad O (1). 
	/// </summary>
	/// <returns>cantidad de datos de la fila priorizada</returns>
	int size() {
		return heapTree.size();
	}

	/// <summary>
	/// Se encarga de insertar un nuevo elemento en el árbol, comprobando que el último elemento insertado sea 
	/// colocado correctamente en la posición adecuada, de manera en la que se respete la condición en la cual el 
	/// padre del nodo tenga que tener un valor mayor. Esto se hace iterativamente hasta que se cumpla la condición.
	/// Tiempo de complejidad O log (n). 
	/// </summary>
	/// <param name="data">entero que se desea agregar a la fila priorizada</param>
	void push(T data) {
		if (heapTree.empty()) {
			heapTree.push_back(data);
		}
		else {
			// Inserta el nuevo valor al final
			heapTree.push_back(data);
			int index = heapTree.size() - 1;
			bool isMin = false;

			// Se intercambia el padre por el hijo si el padre es menor.
			while (index != 0 && heapTree[parent(index)] < heapTree[index]) {
				// Se intercambia el padre por el hijo
				swap(heapTree[index], heapTree[parent(index)]);
				// Se avanza al siguiente nodo padre
				index = parent(index);
			}
		}
	}

	/// <summary>
	/// Imprime el arbol en manera de lista. 
	/// Tiempo de complejidad O (n). 
	/// </summary>
	void imprimir() {
		for (int i = 0; i < heapTree.size(); i++) {
			cout << heapTree[i] << ',';
		}
		cout << endl;
	}
};

void generateRandomQueue(priority_queue<int>&);

int main() {
	priority_queue<int> heapTree;
	for (int i = 0; i < 4; i++) {
		cout << "Prueba " << i + 1 << ": " << endl;
		generateRandomQueue(heapTree);
		heapTree.imprimir();
		cout << "Top():" << endl;
		cout<<(heapTree.top())<<endl;
		cout << "Pop():" << endl;
		heapTree.pop();
		heapTree.imprimir();
		cout << endl;
		heapTree.heapTree.clear();
	}
	return 0;
}

/// <summary>
/// Genera una queue con números aleatorios.
/// Tiempo de complejidad O (n). 	
/// </summary>
/// <param name="heapTree">Fila priorizada</param>
void generateRandomQueue(priority_queue<int>& heapTree) {
	srand(time(NULL) + rand());
	for (int i = 0; i <= 10; i++) {
		heapTree.push(rand() % 100);
	}
}


/*
TC1031 Programación de estructuras de datos y algoritmos fundamentales (Gpo 13)

Act 3.1 - Árbol ABL
Este programa se encarga de realizar las operaciones funtamentales del árbol ABL: Insertar, Eliminar, Imprimir,
Buscar, realizando las rotaciones correspondientes al insertar y al eliminar nodos del árbol.
Autor: Ricardo González Leal, A01639036
Fecha de creación: 21/10/21
*/

#include <iostream>
#include <queue> 
#include <algorithm>  
#include <vector>

using namespace std;

template <class T> class Node {
public:
	T data;
	int key;
	Node* left;
	Node* right;

	Node(T new_data, int key, Node<T>* left, Node<T>* right) {
		this->data = new_data;
		this->key = key;
		this->left = left;
		this->right = right;
	}

	Node(T new_data, int key) {
		this->data = new_data;
		this->key = key;
		this->left = NULL;
		this->right = NULL;
	}
};

template <class T> class BinarySearchTree {
public:
	Node<T>* root;
	int size;

	BinarySearchTree<T>() {
		this->root = NULL;
		this->size = 0;
	}

	~BinarySearchTree() {
	}

	/// <summary>
	/// Limpia el arbol.
	/// </summary>
	void clear() {
		this->root = NULL;
		this->size = 0;
	}

	/// <summary>
	/// Inserta un nodo en el árbol AVL de manera recursiva. Posteriormente comprueba si el árbol
	/// está balanceado o no, para que en el caso de que no, se realicen las rotaciones adecuadas. 
	/// Complejidad de tiempo: Θ(log(n))
	/// </summary>
	/// <param name="current_node">Nodo a insertar.</param>
	/// <param name="data">Dato a trabajar en base al template utilizado.</param>
	/// <param name="key">Valor que se asigna al nodo como llave.</param>
	Node<T>* insert(Node<T>* current_node, Node<T>* node_insert) {
		if (current_node == NULL) {
			return node_insert;
		}
		if (node_insert->key < current_node->key)
			current_node->left = this->insert(current_node->left, node_insert);
		else
			current_node->right = this->insert(current_node->right, node_insert);

		Node<T>* rotatedNode = performRotationsAfterInsert(current_node);

		if (rotatedNode == NULL) {
			return current_node;
		}
		else {
			return rotatedNode;
		}
	}

	/// <summary>
	/// Esta función se encarga de obtener el balance del nodo. Posteriormente, realizando comprobaciones se 
	/// verifica si está balanceado o no. Si no está balanceado, se realizan rotaciones LL, RR, LR o RL, según
	/// corresponda.
	/// Complejidad de tiempo: O(n).  
	/// </summary>
	/// <param name="current_node">Nodo a verificar</param>
	/// <returns>El arbol actualizado</returns>
	Node<T>* performRotationsAfterInsert(Node<T>* node) {
		int balance = this->balanceF(node);
		int balanceLeft = this->balanceF(node->left);
		int balanceRight = this->balanceF(node->right);

		if (balance == 2 && balanceLeft == 1)
			return this->left_left(node);

		if (balance == -2 && balanceRight == -1)
			return this->right_right(node);

		if (balance == -2 && balanceRight == 1)
			return this->right_left(node);

		if (balance == 2 && balanceLeft == -1)
			return this->left_right(node);

		return NULL;
	}

	/// <summary>
	/// Esta función inserta un nodo en el árbol.
	/// Complejidad de Tiempo: O(n)
	/// </summary>
	/// <param name="data">Valor a insertar</param>
	/// <param name="key">Llave del nuevo nodo</param>
	void insert(T data, int key) {
		Node<T>* node_insert = new Node<T>(data, key);
		if (this->root)
			root = this->insert(this->root, node_insert);
		else
			this->root = node_insert;
		this->size++;
	}

	/// <summary>
	/// Imprime el árbol de manera InOrder. 
	/// </summary>
	/// <param name="current_node">Nodo a imprimir</param>
	void inOrder(Node<T>* current_node)
	{
		if (current_node) {
			inOrder(current_node->left);
			cout << current_node->key << " ";
			inOrder(current_node->right);
		}
		if (this->root == current_node) {
			cout << endl;
		}
	}

	/// <summary>
	/// Imprime el árbol de manera InOrder. 
	/// </summary>
	void inOrder() {
		inOrder(root);
	}

	/// <summary>
	/// Busca de manera recursiva un nodo en el árbol según el valor de la llave recibido. 
	/// Complejidad de tiempo: Θ(log(n))
	/// </summary>
	/// <param name="Node">Nodo en el que se está buscando</param>
	/// <param name="key">Valor a buscar que tiene el nodo</param>
	/// <returns></returns>
	Node<T>* search(Node<T>* Node, int key) {
		if (Node == NULL) {
			return NULL;
		}
		else if (Node->key == key) {
			return Node;
		}
		else if (Node->key > key) {
			// si la clave buscada es menor que Node va a la izquierda de forma recursiva
			return search(Node->left, key);
		}
		else {
			// si la clave buscada es más que Node va a la derecha de forma recursiva
			return search(Node->right, key);
		}
	}

	/// <summary>
	/// Obtiene el menor valor del arbol
	/// Complejidad de Tiempo: O(log(n))
	/// </summary>
	/// <param name="current_node">Nodo actual</param>
	/// <returns>Menor valor del arbol</returns>
	Node<T>* minimum_element(Node<T>* current_node) {
		//gets most left item
		if (!current_node->left) {
			return current_node;
		}
		return minimum_element(current_node->left);
	}

	/// <summary>
	/// Devuelve la altura de un nodo de manera recursiva.
	/// Complejidad de tiempo: O(n)
	/// </summary>
	/// <param name="node">Nodo a comprobar</param>
	/// <returns>Altura del nodo</returns>
	int height(Node<T>* node) {
		if (!node)
			return 0;

		// Se obtiene la altura tanto del lado izquierdo, como en el derecho del nodo.
		int leftH = height(node->left);
		int rightH = height(node->right);

		return max(leftH, rightH) + 1;
	}

	/// <summary>
	/// Obtiene el balance del nodo según la fórmula de los árboles AVL (se resta la altura del nodo 
	/// izquierdo, menos la altura del nodo derecho).
	/// Complejidad de tiempo: O(n)
	/// </summary>
	/// <param name="node">Nodo a calcular balance</param>
	/// <returns>Balance del nodo</returns>
	int balanceF(Node<T>* node) {
		if (!node)
			return 0;
		return height(node->left) - height(node->right);
	}

	/// <summary>
	/// Realiza una rotación LL mediante intercambios de nodos. 
	/// Complejidad de tiempo: O(1)
	/// </summary>
	/// <param name="n1">nodo del cuál se realizará la rotación</param>
	/// <returns>raíz del nodo rotado</returns>
	Node<T>* left_left(Node<T>* n1) {
		Node<T>* n2 = n1->left;
		n1->left = n2->right;
		n2->right = n1;
		return n2;
	}

	/// <summary>
	/// Realiza una rotación RR mediante intercambios de nodos.
	/// Complejidad de Tiempo: O(1)
	/// </summary>
	/// <param name="n1">nodo del cuál se realizará la rotación</param>
	/// <returns>raíz del nodo rotado</returns>
	Node<T>* right_right(Node<T>* n1) {
		Node<T>* n2 = n1->right;
		n1->right = n2->left;
		n2->left = n1;
		return n2;
	}

	/// <summary>
	/// Realiza una rotación RL mediante intercambios de nodos. 
	/// </summary>
	/// <param name="n1">nodo del cuál se realizará la rotación</param>
	/// <returns>raíz del nodo rotado</returns>
	Node<T>* right_left(Node<T>* n1)
	{
		Node<T>* n2 = n1->right;
		Node<T>* n3 = n2->left;

		n2->left = n3->right;
		n3->right = n2;

		n1->right = n3->left;
		n3->left = n1;

		return n3;
	}

	/// <summary>
	/// Realiza una rotación LR mediante intercambios de nodos. 
	/// </summary>
	/// <param name="n1">nodo del cuál se realizará la rotación</param>
	/// <returns></returns>
	Node<T>* left_right(Node<T>* n1)
	{
		Node<T>* n2 = n1->left;
		Node<T>* n3 = n2->right;

		n2->right = n3->left;
		n3->left = n2;

		n1->left = n3->right;
		n3->right = n1;

		return n3;
	}

	/// <summary>
	/// Despliega el arbol de una manera más gráfica, en la que se pueden apreciar
	/// las posiciones de los nodos
	/// </summary>
	/// <param name="tree">Nodo root del arbol</param>
	/// <param name="count">Cuenta de los nodos impresos</param>
	void showTree(Node<T>* tree, int count) {
		if (tree == NULL) {
			return;
		}
		else {
			showTree(tree->right, count + 1);
			for (int i = 0; i < count; i++) {
				cout << "   ";
			}
			cout << tree->key << endl;
			showTree(tree->left, count + 1);
		}
	}

	/// <summary>
	/// Elimina un nodo en el árbol AVL de manera recursiva. Posteriormente comprueba si el árbol
	/// quedó balanceado o no, para que en el caso de que no, se realicen las rotaciones adecuadas. 
	/// Complejidad de tiempo: Θ(log(n))
	/// </summary>
	/// <param name="current_node">Nodo actual.</param>
	/// <param name="key_delete">Valor que tiene el nodo que se desea eliminar</param>
	Node<T>* delete_node(Node<T>* current_node, int key_delete)
	{
		// Si no se encontró el nodo, se retorna NULL.
		if (!current_node)
			return NULL;

		// Se busca el elemento a buscar 
		else if (key_delete < current_node->key)
			current_node->left = this->delete_node(current_node->left, key_delete);
		else if (key_delete > current_node->key)
			current_node->right = this->delete_node(current_node->right, key_delete);
		else
		{
			if (current_node->left == NULL || current_node->right == NULL)
			{
				// Si el nodo es un nodo hoja, se elimina.
				Node<T>* aux = current_node->left ? current_node->left : current_node->right;
				delete current_node;
				if (aux == NULL)
					current_node = NULL;
				else
					current_node = aux;
			}
			else
			{
				Node<T>* successor = this->minimum_element(current_node->right);
				Node<T>* new_node_minimum = new Node<T>(
					successor->data, successor->key,
					current_node->left, current_node->right);

				current_node = new_node_minimum;
				current_node->right = this->delete_node(current_node->right, successor->key);
			}
		}

		if (current_node == NULL)
			return current_node;

		Node<T>* aux = performRotationsAfterDelete(current_node);

		if (aux == NULL) {
			return current_node;
		}
		else {
			return aux;
		}
	}

	/// <summary>
	/// Realiza las rotaciones necesarias tras haber eliminado un nodo.
	/// Tiempo de Complejidad: O(log(n))
	/// </summary>
	/// <param name="node">Nodo a rotar</param>
	/// <returns>Nuevo nodo raíz de la rotación</returns>
	Node<T>* performRotationsAfterDelete(Node<T>* node)
	{
		int balance = this->balanceF(node);
		int balanceLeft = this->balanceF(node->left);
		int balanceRight = this->balanceF(node->right);

		if (balance > 1 && balanceLeft >= 0)
			return this->left_left(node);

		if (balance < -1 && balanceRight <= 0)
			return this->right_right(node);

		if (balance < -1 && balanceRight > 0)
			return this->right_left(node);

		if (balance > 1 && balanceLeft < 0)
			return this->left_right(node);

		return NULL;
	}
	/// <summary>
	/// Se encarga de eliminar un nodo deseado del Árbol AVL.
	/// Complejidad de tiempo: Θ(log(n))
	/// </summary>
	/// <param name="key_delete">llave del nodo a eliminar</param>
	void delete_node(int key_delete)
	{
		this->size--;
		this->root = this->delete_node(this->root, key_delete);
	}
};


int main() {
	int option;
	vector<int> insertingNumbers, deletingNumbers;
	BinarySearchTree<int> a;
	bool stop = false, validCase = false;
	do
	{
		cout << "Selecciona un caso: " << endl;
		cout << "1: Ins: [3, 4, 15, 6, 23, 8, 7, 2, 1, 0] | Del: [3, 23, 6]" << endl;
		cout << "2: Ins: [41, 20, 65, 11, 29, 50, 91, 32, 72, 99] | Del: [32, 29, 11]" << endl;
		cout << "3: Ins: [10, 12, 5, 7, 20, 4, 1, 21, 13] | Del: [7, 5, 1, 21]" << endl;
		cout << "4: Ins: [96, 94, 83, 62, 46, 27, 18, 12] | Del: [96, 46, 12, 18]" << endl;
		do
		{
			a.clear();
			cin >> option;
			system("cls");
			switch (option)
			{
			default:
				cout << "Caso no encontrado" << endl;
				break;
			case 1:
				insertingNumbers = { 3, 4, 15, 6, 23, 8, 7, 2, 1, 0 };
				deletingNumbers = { 3, 23, 6 };
				validCase = true;
				break;
			case 2:
				insertingNumbers = { 41, 20, 65, 11, 29, 50, 91, 32, 72, 99 };
				deletingNumbers = { 32, 29, 11 };
				validCase = true;
				break;
			case 3:
				insertingNumbers = { 10, 12, 5, 7, 20, 4, 1, 21, 13 };
				deletingNumbers = { 7, 5, 1, 21 };
				validCase = true;
				break;
			case 4:
				insertingNumbers = { 96, 94, 83, 62, 46, 27, 18, 12 };
				deletingNumbers = { 96, 46, 12, 18 };
				validCase = true;
				break;
			}
		} while (!validCase);

		for (int i = 0; i < insertingNumbers.size(); i++) {
			a.insert(0, insertingNumbers[i]);
			cout << "Se inserta el elemento " << insertingNumbers[i] << " | Size: " << a.size << " | BF: " << a.balanceF(a.root) << endl << endl;
			a.showTree(a.root, 0);
			cout << endl;
		}
		for (int i = 0; i < deletingNumbers.size(); i++)
		{
			a.delete_node(deletingNumbers[i]);
			cout << "Se elimina el elemento " << deletingNumbers[i] << " | Size: " << a.size << " | BF: " << a.balanceF(a.root) << endl << endl;
			a.showTree(a.root, 0);
			cout << endl;
		}
		system("pause");
		cout << "Deseas continuar? 1: Si | 2: No" << endl;
		cin >> option;
		if (option != 1) {  
			break;
		}
		system("cls");
	} while (true);
	return 0;
}

/*
TC1031 Programación de estructuras de datos y algoritmos fundamentales (Gpo 13)
Act 1.2 - Algoritmos de Búsqueda y Ordenamiento
Este programa contiene funciones que ordenan un arreglo de números utilizando distintos métodos de ordenamiento, así como
funciones para buscar un número particular en un arreglo de números.
Autor: Ricardo González Leal, A01639036
Fecha de creación: 01/09/21
*/

#include <iostream>
#include <vector>

using namespace std;

void ordenaIntercambio(vector<int>);
void ordenaBurbuja(vector<int>);
void ordenaMerge(vector<int>&);
int busqSecuencial(vector<int>, int);
int busqBinaria(vector<int>, int);
void imprimeArreglo(vector<int>);
void merge_sort(vector<int>&, int, int);
void merge(vector<int>&, int, int, int);

int main()
{
	// almacena la cantidad de números en el vector.
	int n;
	int dato;

	// vector de enteros que almacena los casos de prueba.
	vector<int> numbers;

	for (int i = 1; i <= 4; i++)
	{
		system("cls");
		cout << "CASO "<< i << ":" << endl;
		cout << "Introduce la cantidad de numeros a generar" << endl;
		cin >> n;

		// necesario para generar diferentes números aleatoriamente.
		srand(time(0));

		// se generan números aleatorios usando la función rand.
		cout << "Numeros generados aleatoriamente: " << endl;
		for (int i = 0; i < n; i++) {
			int number = rand() % 100;
			numbers.push_back(number);
			cout << number << " ";
		}
		cout << endl << endl;
		cout << "Ordenamientos:" << endl;

		// se realizan los ordenamientos
		ordenaBurbuja(numbers);
		ordenaIntercambio(numbers);
		ordenaMerge(numbers);

		// se solicita el número a buscar
		int nbusquedas, buscar;
		cout << endl << "Introduce la cantidad de busquedas a realizar" << endl;
		cin >> nbusquedas;

		// se realizan el número de búsquedas especificadas con los métodos secuencial y binario.
		for (int i = 0; i < nbusquedas; i++) {
			cout << endl << "Introduce el numero a buscar" << endl;
			cin >> dato;

			int res = busqSecuencial(numbers, dato);
			cout << "Busqueda Secuencial: " << endl;

			if (res != -1) {
				cout << "Se encontro el numero " << dato << " en la posicion " << res << endl;
			}
			else {
				cout << "No se encontro el numero " << dato << endl;
			}

			res = busqBinaria(numbers, dato);
			cout << "Busqueda Binaria: " << endl;

			if (res != -1) {
				cout << "Se encontro el numero " << dato << " en la posicion " << res << endl;
			}
			else {
				cout << "No se encontro el numero " << dato << endl;
			}
		}
		system("PAUSE");
	}
	
	return 0;
}

/// <summary>
/// Esta función ordena en forma ascendente los datos con el método de intercambio o también
/// conocido como método de Inserción.
/// Complejidad de la función: O(n^2)
/// </summary>
/// <param name="numbers">vector con los números a ordenar</param>
void ordenaIntercambio(vector<int> numbers) {
	int key, j;
	for (int i = 0; i < numbers.size(); i++) {
		key = numbers[i];
		j = i - 1;

		/* Se comprueba iterativamente si el número de la izquierda es mayor que key,
		de ser así se realiza un intercambio. */ 
		while (j >= 0 && numbers[j] > key) {
			numbers[j + 1] = numbers[j];
			j = j - 1;
		}
		numbers[j + 1] = key;
	}

	// Se imprime el arreglo ordenado
	cout << "Insercion: " << endl;
	imprimeArreglo(numbers);
}

/// <summary>
/// Esta función ordena en forma ascendentelos datos con el método de Burbuja
/// Complejidad de la función: O(n^2)
/// </summary>
/// <param name="numbers">vector con los números a ordenar</param>
void ordenaBurbuja(vector<int> numbers) {
	int size = numbers.size();

	// El método burbuja itera buscando el número mayor y lo va mandando al final poco a poco.
	// Su complejidad es O(n^2). 
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size - i - 1; j++) {
			if (numbers[j] > numbers[j + 1]) {
				// Se intercambian los números
				int temp = numbers[j];
				numbers[j] = numbers[j + 1];
				numbers[j + 1] = temp;
			}
		}
	}

	// Se imprime el arreglo ordenado
	cout << "Burbuja: " << endl;
	imprimeArreglo(numbers);
}

/// <summary>
/// Esta función ordena en forma ascendente los datos con el método de Merge Sort.
/// Complejidad del Merge Sort: O(n log n)
/// </summary>
/// <param name="numbers">vector con los números a ordenar</param>
void ordenaMerge(vector<int> &numbers) {
	merge_sort(numbers, 0, numbers.size()-1);
	// se imprime el arreglo ordenado
	cout << "Merge: " << endl;
	imprimeArreglo(numbers);
}

/// <summary>
/// El algoritmo merge sort estable basado en la técnica divide y vencerás. Divide iterativamente el arreglo de números 
/// en 2 partes de aproximadamente la mitad del tamaño, posteriormente se ordena cada subarreglo recursivamente y finalmente 
/// se mezclan las dos partes del arreglo en uno solo. 
/// Complejidad de la función: O(n log n)
/// </summary>
/// <param name="numbers">Vector de números a ordenar</param>
/// <param name="l">Left, o el índice del elemento inferior del subarreglo</param>
/// <param name="r">Right, o el índice del elemento final del subarreglo</param>
void merge_sort(vector<int> &numbers, int l, int r)
{
	int mid;
	if (l < r) {
		// Se calcula la mitad del arreglo.
		mid = (l + r) / 2;
		// Se ordenan la primera y la segunda mitad. 
		merge_sort(numbers, l, mid);
		merge_sort(numbers, mid + 1, r);
		// Se combinan las dos mitades previamente ordenadas.
		merge(numbers, l, r, mid);
	}
}

/// <summary>
/// Esta función forma parte del algoritmo del ordenamiento merge, y lo que hace es combinar 
/// las dos mitades del arreglo. 
/// Complejidad del Merge Sort: O(n log n)
/// </summary>
/// <param name="numbers">Vector de números</param>
/// <param name="low">Posición inicial del arreglo</param>
/// <param name="high">Posición final del arreglo</param>
/// <param name="mid">Mitad del arreglo</param>
void merge(vector<int> &numbers, int low, int high, int mid)
{
	int n1 = mid - low + 1;
	int n2 = high - mid;
	vector<int> L(numbers.size()); 
	vector<int> R(numbers.size());

	for (int i = 0; i < n1; i++) {
		L[i] = numbers[low + i];
	}
	for (int j = 0; j < n2; j++) {
		R[j] = numbers[mid + 1 + j];
	}

	// Fusiona los subarreglos
	int i = 0;
	int j = 0;
	int k = low;
	while (i<n1 && j<n2) {
		if (L[i] <= R[j]) {
			numbers[k] = L[i];
			i++;
		}
		else {
			numbers[k] = R[j];
			j++;
		}
		k += 1;
	}

	// Copia los elementos restantes, si existen
	while (i < n1) {
		numbers[k] = L[i];
		i++;
		k++;
	}
	while (j < n2) {
		numbers[k] = R[j];
		j++;
		k++;
	}
}

/// <summary>
/// Esta función busca con la busqueda secuencial un dato entero dentro del vector.
/// Complejidad de la función: O(n)
/// </summary>
/// <param name="numbers">vector con números</param>
/// <param name="nBuscado">dato entero que se desea buscar</param>
/// <returns>la posición en la que se encontró el dato, o -1 si no se encontró</returns>
int busqSecuencial(vector<int> numbers, int nBuscado) {

	int index = 0;

	/* Mientras que el índice no haya alcanzado el final del arreglo, se itera entre los elementos del
	 arreglo y se revisa si el elemento actual es el elemento buscado. */
	while (index < numbers.size() && numbers[index] != nBuscado) {
		index++;
	}
	// Si el indice es menor al tamaño del arreglo, quiere decir que si se encontró el elemento buscando.
	if (index < numbers.size()) {
		return index;
	}
	else {
		return -1;
	}
	return -1;
}

/// <summary>
/// Esta función busca con la busqueda binaria un dato entero dentro del vector.
/// Complejidad de la función: O(log n)
/// </summary>
/// <param name="numbers">vector con números</param>
/// <param name="nBuscado">dato entero que se desea buscar</param>
/// <returns></returns>
int busqBinaria(vector<int> numbers, int nBuscado) {
	int size = numbers.size();
	int left = 0;
	int right = size - 1;

	while (left <= right) {
		int middle = (left + right) / 2;
		if (nBuscado == numbers[middle]) {
			return middle;
		}
		else if (nBuscado < numbers[middle]) {
			right = middle - 1;
		}
		else {
			left = middle + 1;
		}
	}
	return -1;
}

/// <summary>
/// Esta función se encarga de imprimir el vector de números.
/// </summary>
/// <param name="numbers"> Vector que contiene los números a imprimir </param>
void imprimeArreglo(vector<int> numbers) {
	for (int i = 0; i < numbers.size(); i++) {
		cout << numbers.at(i) << " ";
	}
	cout << endl;
}

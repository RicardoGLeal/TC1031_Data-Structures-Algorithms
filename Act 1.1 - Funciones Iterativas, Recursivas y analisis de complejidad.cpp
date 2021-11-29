/*
TC1031 Programación de estructuras de datos y algoritmos fundamentales (Gpo 13)
Act 1.1 - Funciones Iterativas, Recursivas y su análisis de Complejidad:
Este programa se encarga de realizar la sumatoria de 1 hasta n (donde n es un número definido) por las siguientes maneras:
iterativa, recursiva, y utilizando un método matemático.
Autor: Ricardo González Leal, A01639036
Fecha de creación: 16/08/21
*/

#include <iostream>
#include <vector>

using namespace std;

int sumaIterativa(int);
int sumaRecursiva(int);
int sumaDirecta(int);

int main()
{
	// vector de enteros que almacena los casos de prueba.
	vector<int> numbers;

	// se agregan los números para los casos de prueba.
	numbers.push_back(8);
	numbers.push_back(16);
	numbers.push_back(24);
	numbers.push_back(32);

	// se realizan los casos de prueba, mandándo llamar a las funciones correspondientes.
	for (int i = 0; i < numbers.size(); i++) {
		cout << "Caso " << numbers.at(i) << ": " << endl;
		cout << "Suma Iterativa: " << sumaIterativa(numbers.at(i)) << endl;
		cout << "Suma Recursiva: " << sumaRecursiva(numbers.at(i)) << endl;
		cout << "Suma Directa: " << sumaDirecta(numbers.at(i)) << endl << endl;
	}
}

/// <summary>
/// Calcula la sumatoria de 1 hasta n con un método iterativo. 
/// Complejidad: O(n). 
/// </summary>
/// <returns>La sumatoria de 1 hasta n</returns>
int sumaIterativa(int n)
{
	int res = 0;
	for (int i = 1; i <= n; i++) {
		// Dentro del for se suman todos los números y el resultado se guarda en la variable res.
		// La complejidad de esta función es O(n), ya que hay un ciclo for que recorre todos los del elementos, iniciando en 1 y terminando en n.
		res += i;
	}
	return res;
}

/// <summary>
/// Calcula la sumatoria de 1 hasta n de manera recursiva.
/// Complejidad: O(n). 
/// </summary>
/// <param name="n">numero hasta el que se calcula la suma</param>
/// <returns>La sumatoria de 1 hasta n</returns>
int sumaRecursiva(int n) {
	// Caso base
	if (n == 0) {
		return 0;
	}
	// Inducción
	return n + sumaRecursiva(n - 1);
	// La complejidad de esta función es O(n), ya que por medio de recursividad se van sumando los elementos, iniciando en n y terminando en 0 
}

/// <summary>
/// Calcula la sumatoria de 1 hasta n con un método matemático directo.
/// Complejidad: O(1). 
/// </summary>
/// <param name="n"></param>
/// <returns>La sumatoria de 1 hasta n</returns>
int sumaDirecta(int n) {
	return n * (n + 1) / 2;
	// La complejidad de esta función es O(1), ya que únicamente se efectúa una operación aritmética. 
}
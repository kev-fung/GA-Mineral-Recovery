#include "Header.h"

using namespace std;


int main() {
	int numCircuits = 4; // TO TUNE
	int maxIte = 10;
	double tol = 1e-6;
	int max_iterations = 1000;

	srand(time(NULL));

	vector<int> circuit(sizeVec, 0);
	vector<vector<int>> circuits(numCircuits, vector<int>(sizeVec, 0));

	vector<double> fitVec(numCircuits, 0);

	// Generating the parents
	cout << "Generating parents" << endl;
	for (int i = 0; i < numCircuits; i++) {
		while(!Check_Validity(circuit)){  
			generateCircuit(circuit);
		}

		cout << "Circuit: ";
		for (int j = 0; j < sizeVec; j++) {
			cout << circuit[j] << " ";
		}
		cout << endl;
		
		circuits[i] = circuit;
		fitVec[i] = Evaluate_Circuit(circuit, tol, max_iterations);
	
		// Reinitialise the vector with 0
		for (int j = 0; j < sizeVec; j++) {
			circuit[j] = 0;
		}
	}
	cout << endl;

	// Check the vectors.
	cout << "Input Vectors" << endl;
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < sizeVec; j++) {
			cout << circuits[i][j] << " ";
		}
		cout << " Fitness: " << fitVec[i] << endl;
	}
	cout << endl;


	// Genetic algorithm
	cout << "Genetic algorithm" << endl;
	geneticAlgo(circuits, fitVec, maxIte, tol, max_iterations);
	cout << endl;

	// Print the output.
	cout << "Output Vectors" << endl;
	for (int i = 0; i < numCircuits; i++) {
		for (int j = 0; j < sizeVec; j++) {
			cout << circuits[i][j] << " ";
		}
		cout << endl;
	}

	system("pause");
}
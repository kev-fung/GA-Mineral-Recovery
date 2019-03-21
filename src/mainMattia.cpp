#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include "geneticAlgo.h"

using namespace std;


int main()
{
	int num0, num1, cnt;
	int size = 10*2+1;
	int numCircuits = 4;
	int sizeVec = 21;
	int maxIte = 1;
	int indmax = 0;
	int max = 0;

	srand (time(NULL));

	vector<int> circuit(sizeVec,0);
	vector<int> best_circuit(sizeVec,0);
	vector<vector<int>> circuits(numCircuits, vector<int>(sizeVec,0));

	vector<double> fitVec(numCircuits,0);

	for (int i=0; i<numCircuits; i++)
	{
		generateCircuit(circuit);
		circuits[i] = circuit;
		fitVec[i] = i*(20);
	}


    // Check the vectors.
 	cout << "Input Vectors" << endl;
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < size; j++) {
			cout << circuits[i][j] << " "; 
		}
		cout << "   Fitness: " << fitVec[i] << endl;
	}
	cout << endl;


	// find index of max fitness
	for (int i=0; i<numCircuits; i++)
	{
		if (fitVec[i] > max)
			{
			max = fitVec[i];
			indmax = i;
			}
	}
	best_circuit = circuits[indmax];


	geneticAlgo(circuits, fitVec, maxIte);


    // Test genetic algo is working.
	bool pass = true;
	for (int i = 0; i<sizeVec; i++)
	{
		if (circuits[0][i] != best_circuit[i]) pass = false;
	}
	cout << endl << "PASS is = " << pass << endl << endl;


    // Print the output.
    cout << "Output Vectors" << endl;
	for (int i = 0; i<numCircuits;i++){
		for (int j =0; j<size; j++){
		cout << circuits[i][j] << " ";
		}
		cout << endl;
	}

}
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

	srand (time(NULL));

	vector<int> circuit(sizeVec,0);
	vector<vector<int>> circuits(numCircuits, vector<int>(sizeVec,0));

	vector<double> fitVec(numCircuits,0);

	for (int i=0; i<numCircuits; i++)
	{
		generateCircuit(circuit);
		circuits[i] = circuit;
		fitVec[i] = i*2;
	}


    // Check the vectors.
 	cout << "what we put in the list" << endl;
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < size; j++) {
			cout << circuits[i][j] << " "; 
		}
		cout << "fitness: " << fitVec[i] << endl;
	}
	cout << endl;


	geneticAlgo(circuits, fitVec);


	for (int i = 0; i<numCircuits;i++){
		cout << "circuit " << i << endl;
		for (int j =0; j<size; j++){
		cout << circuits[i][j] << " ";
		}
		cout << endl;
	}

}
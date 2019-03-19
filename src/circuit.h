#include <vector>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>

using namespace std;

class Circuit
{
public:
	Circuit(int size, double fit);
	~Circuit();

	void generateCircuit();

	
	double fitness;
	int size_vect;

	vector<int> values;

	int* vals;

};


#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include "circuit.h"

using namespace std;

int num0, num1, cnt;
int size = 10*2+1;
int size_children = 4;


void geneticAlgo(vector<Circuit> &circuits)
{
	srand (time(NULL));

	vector<Circuit> children;
	Circuit circuit(2*10+1, 0);
	Circuit circuit0(2*10+1, 0);
	Circuit circuit1(2*10+1, 0);


    // keep track of the children.
	cnt = 0;


	// The best goes on unchanged.
	int min = 0;
	int max = 0;
	int indmax = 0;
	for (int i=0; i<size_children; i++)
	{
		if (circuits[i].fitness > max)
			{
				max = circuits[i].fitness;
				indmax = i;
			}
		if (circuits[i].fitness < min) min = circuits[i].fitness;
	}
	children.push_back(circuits[indmax]);
	cnt++;



	// Find the range of fitness.
	vector<int> intervals(size_children+1);
	intervals[0] = 0;
	int range = 0;
	for (int i=0; i<size_children; i++)
	{
		circuits[i].fitness -= min;
		range += circuits[i].fitness;
		intervals[i+1] = range;
	}


	for (int i=0; i<size_children;i++){


    	// Find the indexes of the parents.
		double num0, num1; 
		int ind0=0, ind1=0;

		while (ind0==ind1){
    		// Pick a random number.
			//double num0 = rand() % (range+1);
			num0 = ((double) rand() / (RAND_MAX));
			num0 *= range;
			num1 = ((double) rand() / (RAND_MAX));
			num1 *= range;


			for (int i=1; i<size_children+1; i++)
			{
				if (num0>intervals[i-1] &&  num0<=intervals[i]) ind0=i-1;
				if (num1>intervals[i-1] &&  num1<=intervals[i]) ind1=i-1;
			}
		}



    	// Do the cross-over and the mutation..
    	num0 = ((double) rand() / (RAND_MAX));
	    if ( num0>0.8 && num0<1){
    		// Select a random point in the vector.
    		int pivot = (rand() % (size-1)) + 1;

    		// Do the first child.
    		for (int i=0; i<pivot; i++)
    		{
    			circuit0.values[i] = circuits[ind1].values[i];
    			circuit1.values[i] = circuits[ind0].values[i];
    		}
    		for (int i=pivot; i<size; i++)
    		{
    			circuit0.values[i] = circuits[ind0].values[i];
    			circuit1.values[i] = circuits[ind1].values[i];
    		}
    	}




    // Do the mutation.



}
















	//cout << max << endl;
	//cout << min << endl;
	//cout << range<< endl;
	cout << ind0 << "  " << ind1 << endl;
	//for (int i=0; i<size_children; i++) cout << "  " << intervals[i];
	cout << endl;
}



int main()
{
	// vector<int> circuit0(size);
	// vector<int> circuit0(size);

	// generateCircuit(circuit);

	vector<Circuit> list_circuits;
	Circuit test_circuit(2*10+1, 3);
	test_circuit.generateCircuit();
	list_circuits.push_back(test_circuit);

	Circuit test_circuit1(2*10+1, -2);
	test_circuit1.generateCircuit();
	list_circuits.push_back(test_circuit1);

	Circuit test_circuit2(2*10+1, 5);
	test_circuit2.generateCircuit();
	list_circuits.push_back(test_circuit2);

	Circuit test_circuit3(2*10+1, 11);
	test_circuit3.generateCircuit();
	list_circuits.push_back(test_circuit3);

	geneticAlgo(list_circuits);

}




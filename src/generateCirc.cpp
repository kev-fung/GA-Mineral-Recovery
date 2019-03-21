

#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include "circuit.h"

using namespace std;

int num0, num1, cnt;
int size = 10*2+1;
int size_children = 4;


bool Check_Validity(int &circuit_vector)
{
  return true;
}


void geneticAlgo(vector<Circuit> &circuits)
{
 
	int ite = 0;
	int maxIte = 10;
	bool convergence = false;
	srand (time(NULL));

	Circuit circuit0(size, 0);
	Circuit circuit1(size, 0);

	vector<Circuit> children;

	// To get the max and min values of fitness
	int min = 0;
	int max = 0;
	int indmax = 0; // index of the best vector



    //while(ite<maxIte)
    for (ite = 0; ite<maxIte;ite++)
    {



    // keep track of the children.
	cnt = 0;



	// The best goes on unchanged.
	for (int i=0; i<size_children; i++)
	{
		if (circuits[i].fitness > max)
			{
				max = circuits[i].fitness;
				indmax = i;
			}
		if (circuits[i].fitness < min) min = circuits[i].fitness;
	}
	cout << "IND MAX" << indmax << endl;
	children.push_back(circuits[indmax]);
	
	cout << "first child values: " << endl;
	for (int i =0; i<size;i++){
		cout << circuits[indmax].values[i] << " ";
	}
	cout << endl;

	cnt++;



	// Find the range of fitness.
	vector<int> intervals(size_children+1);
	intervals[0] = 0;
	int range = 0;
	for (int i=0; i<size_children; i++)
	{
		circuits[i].fitness -= (min-1e-3);  // We subtract the min minus a little bit.
		range += circuits[i].fitness;
		intervals[i+1] = range;
	}



	// Iterate till we have all the children.
	while (cnt != size_children)
	{

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



    	// Do the cross-over.
    	num0 = ((double) rand() / (RAND_MAX));
	    if ( num0>0.8 && num0<1)
	    {
    		// Select a random point in the vector.
    		int pivot = rand() % (size-1) + 1;

    		// Do the first child.
    		for (int i=0; i<pivot; i++)
    		{
    			circuit0.vals[i] = circuits[ind1].vals[i];
    			circuit1.vals[i] = circuits[ind0].vals[i];
    		}
    		for (int i=pivot; i<size; i++)
    		{
    			circuit0.vals[i] = circuits[ind0].vals[i];
    			circuit1.vals[i] = circuits[ind1].vals[i];
    		}
    	} else
    	{
    		for (int i=0; i<size; i++)
    		{
    			circuit0.vals[i] = circuits[ind0].vals[i];
    			circuit1.vals[i] = circuits[ind1].vals[i];
    		}
    	}


    	// Do the mutation.
    	int randInt;
    	int stepSize =3;
    	num0 = ((double) rand() / (RAND_MAX));


		// Mutate the feed.
		if (num0>0 && num0<0.01)
		{
			randInt = rand()%stepSize+1;
			circuit0.vals[0] = (circuit0.vals[0]+randInt)%12;
			randInt = rand()%stepSize+1;
			circuit1.vals[0] = (circuit1.vals[0]+randInt)%12;
		}
		for (int i=1; i<size; i++)
		{
			num0 = ((double) rand() / (RAND_MAX));
			if (num0>0 && num0<0.01)
			{
				randInt = rand()%stepSize+1;
				circuit0.vals[i] = (circuit0.vals[0]+randInt)%12;
				randInt = rand()%stepSize+1;
				circuit1.vals[i] = (circuit1.vals[0]+randInt)%12;
			}
		}



		cout << "CHECKING VALIDITY" << endl;
        if (Check_Validity(*circuit0.vals)){
        	children.push_back(circuit0);
        	cnt++;
        }

        if (cnt < size_children && Check_Validity(*circuit1.vals)){
        	children.push_back(circuit1);
			cnt++;
        }


	}  // end while on the children.



	// updating the parents vector with the children
	for (int i =0; i<size_children;i++){
		for (int j =0; j<size; j++){
			circuits[i].vals[j] = children[i].vals[j];	
		}
		circuits[i].fitness = rand()%6 - 5; // have to change it by calculation of the fitness
	}


	// ite++;
	children.clear(); // clear the children vector for next iteration
	cout << "N ITE:" << ite+1 << endl;


	}  // end of the while loop on the iterations.

}





int main()
{

	srand (time(NULL));

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

    // Check the vectors.
 	cout << "what we put in the list" << endl;
	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < size; j++) {
			cout << list_circuits[i].vals[j] << " "; 
		}
		cout << "fitness: " << list_circuits[i].fitness << endl;
	}
	cout << endl;

	geneticAlgo(list_circuits);

	for (int i = 0; i<size_children;i++){
		cout << "circuit " << i << endl;
		for (int j =0; j<size; j++){
		cout << list_circuits[i].vals[j] << " ";
		}
		cout << endl;
	}

}




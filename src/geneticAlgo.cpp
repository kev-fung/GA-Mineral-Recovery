#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdlib.h>

using namespace std;


bool Check_Validity(vector<int> &circuit_vector)
{
  return true;
}


void geneticAlgo(vector<vector<int>> &circuits, vector<double> fitVec)
{
	int num0, num1, cnt;
	int numUnits = 10;
	int sizeCirc = numUnits*2+1;
	int numCircuits = 4;

 
	int ite = 0;
	int maxIte = 1;
	bool convergence = false;


	vector<int> circuit0(sizeCirc, 0);
	vector<int> circuit1(sizeCirc, 0);

	vector<vector<int>> children(numCircuits, vector<int>(sizeCirc,0));

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
		for (int i=0; i<numCircuits; i++)
		{
			if (fitVec[i] > max)
				{
					max = fitVec[i];
					indmax = i;
				}
			if (fitVec[i] < min) min = fitVec[i];
		}
		children[0] = circuits[indmax];
		cnt++;



	// Find the range of fitness.
	vector<int> intervals(numCircuits+1);
	intervals[0] = 0;
	int range = 0;
	for (int i=0; i<numCircuits; i++)
	{
		fitVec[i] -= (min-1e-3);  // We subtract the min minus a little bit.
		range += fitVec[i];
		intervals[i+1] = range;
	}



	// Iterate till we have all the children.
	while (cnt != numCircuits)
	{


    	// Find the indexes of the parents.
		double num0, num1; 
		int ind0=0, ind1=0;
		while (ind0==ind1){
    		// Pick a random number.
			num0 = ((double) rand() / (RAND_MAX));
			num0 *= range;
			num1 = ((double) rand() / (RAND_MAX));
			num1 *= range;


			for (int i=1; i<numCircuits+1; i++)
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
    		int pivot = rand() % (sizeCirc-1) + 1;

    		// Do the children.
    		for (int i=0; i<pivot; i++)
    		{
    			circuit0[i] = circuits[ind1][i];
    			circuit1[i] = circuits[ind0][i];
    		}
    		for (int i=pivot; i<sizeCirc; i++)
    		{
    			circuit0[i] = circuits[ind0][i];
    			circuit1[i] = circuits[ind1][i];
    		}
    	} else
    	{
    		circuit0 = circuits[ind0];
    		circuit1 = circuits[ind1];
    	}


    	// Do the mutation.
    	int randInt;
    	int stepSize =3;
    	num0 = ((double) rand() / (RAND_MAX));

		// Mutate the feed.
		if (num0>0 && num0<0.01)
		{
			randInt = rand()%stepSize+1;
			circuit0[0] = (circuit0[0]+randInt)%numUnits;
			randInt = rand()%stepSize+1;
			circuit1[0] = (circuit1[0]+randInt)%numUnits;
		}
		// Mutate the rest of the circuit.
		for (int i=1; i<sizeCirc; i++)
		{
			num0 = ((double) rand() / (RAND_MAX));
			if (num0>0 && num0<0.01)
			{
				randInt = rand()%stepSize+1;
				circuit0[i] = (circuit0[0]+randInt) % (numUnits+2);
				randInt = rand()%stepSize+1;
				circuit1[i] = (circuit1[0]+randInt) % (numUnits+2);
			}
		}


		cout << "CHECKING VALIDITY" << endl;
        if (Check_Validity(circuit0)){
        	children[cnt] = circuit0;
        	cnt++;
        }
        if (cnt < numCircuits && Check_Validity(circuit1)){
        	children[cnt]=circuit1;
			cnt++;
        }


	}  // end while on the children.



	// Updating the parents vector with the children.
	for (int i =0; i<numCircuits;i++)
	{
		circuits[i] = children[i];
		// Compute the new fitness!!!!!
	}


	//ite++;
	cout << "N ITE:" << ite+1 << endl;


	}  // end of the while loop on the iterations.

}



void generateCircuit(vector<int> &vals)
{

	// Set the feed.
	vals[0] = rand()%10;

	int cnt = 1;
	int num0, num1;

	for (int i = 0; i < 10;i++){
		bool fin=false;
		while(fin==false)
		{
			num0 = rand() % 12;
			num1 = rand() % 12;
			if (num0 != num1 && num0!=i && num1!=i) fin = true;
		}
		vals[cnt] = num0;
		vals[cnt+1] = num1;

		cnt+=2;
	}	
}




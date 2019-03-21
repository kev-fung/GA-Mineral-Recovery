#include "circuit.h"

using namespace std;


Circuit::Circuit(int size, double fit): size_vect(size), fitness(fit) 
{
	vals = new int[size];
}

Circuit::~Circuit()
{
	//cout << "deleting" << endl;
	//delete[] vals;
}



void Circuit::generateCircuit()
{
	
	// Set the feed.
	vals[0] = rand()%10;

	
	/* generate number between 0 and 9: */
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




// Compile with:
//   mpic++ -std=c++11 *.h  *.cpp -o run

#include <iostream>
#include <vector>
#include "Genetic_Algorithm.h"
#include "Circuit.h"

#include <mpi.h>

using namespace std;


int id, p, tagNum = 1;


// Get the time.
double wTime()
{
	return (double)clock() / CLOCKS_PER_SEC;
}


int main(int argc, char *argv[])
{

	MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &id);
	MPI_Comm_size(MPI_COMM_WORLD, &p);


	//The timing starts here.
	double tdif = -wTime();

	int num_units = 10;
	int sizeVec = num_units*2+1;
	int num_circuits = 100;
	double prob_CO = 1.;
	double prob_Mut = 0.004;

	double tol = 1e-6;
	double max_iter = 1e3;

	int bestIndCnt = 2000;		// Minimum number of iterations for the best circuit to be the same
	int minIte =  1000;			// Minimum number of iterations to be done
	int maxIte = 10000;			// Maximum number of iterations possible
	bool time_GA = true;

	vector<int> best_circuit;


	Genetic_Algorithm GA(num_units, num_circuits, prob_CO, prob_Mut, tol, max_iter, time_GA);
	best_circuit = GA.runAlgo(bestIndCnt, minIte, maxIte);


	MPI_Finalize();
	//system("pause");
	return 0;
}

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

	int bestIndCnt = 100;		// Minimum number of iterations for the best circuit to be the same
	int minIte = 0;				// Minimum number of iterations to be done
	int maxIte = 1000;			// Maximum number of iterations possible
	bool time_GA = true;

	vector<int> best_circuit;


	Genetic_Algorithm GA(num_units, num_circuits, prob_CO, prob_Mut, tol, max_iter, time_GA);
	best_circuit = GA.runAlgo(bestIndCnt, minIte, maxIte);

	if(time_GA)
	{ 
		// Print the output.
		cout << "Output best vector for process " << id << ":" << endl;
		for (int j = 0; j < 2 * num_units + 1; j++) 
		{
			cout << best_circuit[j] << " ";
		}
	}

	Circuit circ;
	double best_fitness;
	best_fitness = circ.Evaluate_Circuit(best_circuit, tol, max_iter);
	cout << "  Fitness: " << best_fitness;
	cout << endl;



	// Send best circuit and its fitness to the master.
	if (id != 0)
	{
		MPI_Send(best_circuit.data(), sizeVec, MPI_INT, 0, tagNum, MPI_COMM_WORLD);
		MPI_Send(&best_fitness, 1, MPI_DOUBLE, 0, tagNum, MPI_COMM_WORLD);
	}



	// Master receives the best circuits and its fitness.
	if (id == 0)
	{
		MPI_Status status;

        // Store best circuit and its fitness, from the master.
		vector<vector<int>> best_circuits(p, vector<int>(sizeVec, 0));
		vector<double> best_fitvec(p, 0);
		best_circuits[0] = best_circuit;
		best_fitvec[0] = best_fitness;


		// Recieve circuits and fitness.
		int indbest = 0;
		for (int i=1; i<p; i++)
		{
			MPI_Recv(best_circuits[i].data(), sizeVec, MPI_INT, i, tagNum, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			MPI_Recv(&best_fitvec[i], 1, MPI_DOUBLE, i, tagNum, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			if (best_fitvec[i]>best_fitvec[indbest]) indbest=i;
		}


		// Print the best of the best.
		cout << endl << endl << "Output best circuits overall:" << endl;
		for (int j=0; j<p; j++)
		{
			if (best_fitvec[j]==best_fitvec[indbest])
			{
				for (int j = 0; j < sizeVec; j++)
				{
					cout << best_circuits[indbest][j] << " ";
				}
				cout << "   Fitness: " << best_fitvec[indbest] << endl;
			}
		}
	}




	MPI_Finalize();
	//system("pause");
	return 0;
}

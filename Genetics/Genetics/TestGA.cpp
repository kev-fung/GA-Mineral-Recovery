#include <iostream>
#include <vector>
#include "Genetic_Algorithm.h"
#include "Circuit.h"

using namespace std;


int main()
{

	int num_units = 15;
	int num_circuits = 100;
	double prob_CO = 1.;
	double prob_Mut = 0.004;

	double tol = 1e-6;
	double max_iter = 1e3;

	int bestIndCnt = 2000;		// Minimum number of iterations for the best circuit to be the same
	int minIte = 0;				// Minimum number of iterations to be done
	int maxIte = 15000;			// Maximum number of iterations possible
	bool time_GA = true;

	vector<int> best_circuit;

	for (int i = 0; i < 3; i++)
	{
		Genetic_Algorithm GA(num_units, num_circuits, prob_CO, prob_Mut, tol, max_iter, time_GA);
		best_circuit = GA.runAlgo(bestIndCnt, minIte, maxIte);

		if (time_GA)
		{
			// Print the output.
			cout << "Output best vector" << endl;
			for (int j = 0; j < 2 * num_units + 1; j++)
			{
				cout << best_circuit[j] << " ";
			}
		}

		Circuit circ;
		double best_fitness;
		best_fitness = circ.Evaluate_Circuit(best_circuit, tol, max_iter);
		cout << "Fitness: " << best_fitness;
		cout << endl;
	}
	


	system("pause");
	return 0;
}

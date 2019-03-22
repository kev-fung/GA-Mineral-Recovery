#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include <string>
#include "Genetic_Algorithm.h"
#include "Circuit.h"

using namespace std;


void analysis(string name, int num_units, int num_circuits, double prob_CO, double prob_Mut, double tol, double max_iter, int bestIndCnt, int minIte, int maxIte, bool time_GA, int avg_q, int quant, double model[6])
{
	vector<int> best_circuit;

	double avg_fitness;
	int avg_it;
	double avg_time;


	stringstream fname;
	fstream f1;

	fname << name << ".csv";

	f1.open(fname.str().c_str(), ios_base::out);

	// Run the GA with varying input parameter x.
	for (int x = 0; x < quant; x++)
	{
		avg_fitness = 0.;
		avg_it = 0.;
		avg_time = 0.;

		// MUST CHANGE THIS!!!
		prob_Mut = ((double)(x + 1) / (double)quant) / 40.;

		f1 << prob_Mut;

		cout << "TESTING: " << prob_Mut << endl;
		// Run the GA avg_q times to work out the average fitness.
		for (int i = 0; i < avg_q; i++)
		{
			Genetic_Algorithm GA(num_units, num_circuits, prob_CO, prob_Mut, tol, max_iter, model, time_GA);
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

			avg_fitness += best_fitness / avg_q;
			avg_it += GA.it / avg_q;
			avg_time += GA.tdif / avg_q;
		}
		cout << endl;

		f1 << "," << avg_fitness << "," << avg_it << "," << avg_time << endl;
	}

	f1.close();
}


int main()
{
	int num_units = 10;
	int num_circuits = 100;
	double prob_CO = 1.;
	double prob_Mut = 0.004;

	double circuit_model[6];
	circuit_model[0] = 100.;	// cprice
	circuit_model[1] = -500.;	// tcost
	circuit_model[2] = 10.;		// cfeed
	circuit_model[3] = 100.;	// tfeed
	circuit_model[4] = 0.20;	// cfrac
	circuit_model[5] = 0.05;	// tfrac

	double tol = 1e-6;
	double max_iter = 2e3;

	int bestIndCnt = 2000;		// Minimum number of iterations for the best circuit to be the same
	int minIte = 0;				// Minimum number of iterations to be done
	int maxIte = 10;			// Maximum number of iterations possible
	bool time_GA = true;
	bool pass = true;

	vector<int> best_circuit;

	int avg_q = 5;
	int quant = 10;

	/*string file_name = "";
	analysis(file_name, num_units, num_circuits, prob_co, prob_mut, tol, max_iter, bestindcnt, minite, maxite, time_ga, avg_q, quant, circuit_model);
*/
	Genetic_Algorithm ga(num_units, num_circuits, prob_CO, prob_Mut, tol, max_iter, circuit_model, time_GA);
	best_circuit = ga.runAlgo(bestIndCnt, minIte, maxIte);

	if (time_GA)
	{
		// print the output.
		cout << "output best vector" << endl;
		for (int j = 0; j < 2 * num_units + 1; j++)
		{
			if (ga.circuits[0][j] != best_circuit[j])
				pass = false;
			cout << best_circuit[j] << " ";
		}
	}
	if (pass) cout << "Test PASSED\n";
	else cout << "Test FAILED\n";

	Circuit circ;
	double best_fitness;
	best_fitness = circ.Evaluate_Circuit(best_circuit, tol, max_iter);
	cout << "Fitness: " << best_fitness;
	cout << endl;

	system("pause");
	return 0;
}

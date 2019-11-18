#include <iostream>
#include <vector>
#include "Genetic_Algorithm.h"
#include "Circuit.h"

using namespace std;

template<typename T>
T input(T max, T min) //Validates the user input depending on type and range
{

	// This function was developped during a project in ACSE 5  it is used for the demonstration
	// during the presentation only.  
	T value;
	while (true)
	{
		cin >> value; // get user input

		if (!(cin))		// if the input method failed (eg. wrong data type)
		{
			cout << "\nWrong input type, please try again: ";
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		}
		else if (value < min || value > max)  // if the value is out of range
		{
			cout << "\nValue is out of range, please try again: ";
		}
		else  // else return the input
		{
			return value;
		}
	}
}

void interface(int &num_units, int &num_components, vector<double> &flow, vector<double> &fraction, vector<double> &prices)
{
	cout << "============================================================" << endl;
	cout << "============================================================" << endl;
	cout << "      CIRCUIT CONFIGURATION USING GENETIC ALGORITHM         " << endl;
	cout << "============================================================" << endl;
	cout << "============================================================" << endl;
	cout << endl;

	cout << "Please input number of units in circuit: ";
	num_units = input<int>(100, 0); //input number of units
	cout << endl;

	cout << "Would you like to use the base circuit parameters, or your own? Enter 1 or 2: ";
	int choice = input<int>(2, 1);
	cout << endl;

	switch (choice)
	{
	case 1:
		num_components = 2;  //base number of components
		cout << "Number of flow components is: " << num_components << endl;
		flow.reserve(num_components);
		flow[0] = 0.20;
		flow[1] = 0.05;
		fraction.reserve(num_components);
		fraction[0] = 0.20;
		fraction[1] = 0.05;
		prices.reserve(num_components);
		prices[0] = 100;
		prices[1] = -500;
		cout << "Flow of valuable component is " << flow[0] << "kg/s and waste is " << flow[1] << "kg/s" << endl;
		cout << endl;
		cout << "Fraction of valuable and waste components going into concentrate is: "
			<< 100 * fraction[0] << "% and " << 100 * fraction[1] << "%" << endl;
		cout << endl;
		cout << "Price of valuable component: " << prices[0] << "£ and waste " << prices[1] << "£" << endl;
		cout << endl;
		cout << "Simulation will start running now ..." << endl;
		break;
	case 2:
		cout << "Please type the number of components in the flow of the circuit: ";
		num_components = input<int>(20, 2); //input number of components
		cout << endl;

		flow.resize(num_components); //resize fraction vector to the number of components
		cout << "\tInput flow of valuable component from feed rate in kg/s: ";
		flow[0] = input<double>(500, 0);
		cout << endl;
		for (int i = 1; i < flow.size(); i++)
		{
			cout << "\tInput flow of waste " << i << " component from feed rate in kg/s: ";
			flow[i] = input<double>(500, 0);
			cout << endl;
		}

		fraction.resize(num_components); //resize fraction vector to the number of components
		cout << "\tInput fraction of valuable component going into concentrate stream: ";
		fraction[0] = input<double>(1, 0);
		cout << endl;
		for (int i = 1; i < fraction.size(); i++)
		{
			cout << "\tInput fraction of waste component " << i << " going into concentrate stream: ";
			fraction[i] = input<double>(1, 0);
			cout << endl;
		}

		prices.resize(num_components); //resize fraction vector to the number of components
		cout << "\tInput price of valuable component: ";
		prices[0] = input<double>(2000, -2000);
		cout << endl;
		for (int i = 1; i < fraction.size(); i++)
		{
			cout << "\tInput price of waste " << i << " component as a negative value: ";
			prices[i] = input<double>(2000, -2000);
			cout << endl;
		}
		break;
	}

}

int main()
{

	int num_units = 10;
	int num_circuits = 100;
	double prob_CO = 1.;
	double prob_Mut = 0.004;

	//Circuit Evaluation
	double tol = 1e-6;
	double max_iter = 1e3;

	// Circuit information
	int num_components = 2;	//numnber of flow components in circuit
	vector<double> flow(num_components); //flow rate values for each component
	vector<double> fraction(num_components); //fraction of concentrate stream for each component
	vector<double> prices(num_components); //prices of each component
	
	//interface(num_units, num_components, flow, fraction, prices);
	////Assigning values needs to be done manually
	flow[0] = 10;		//kg/s
	flow[1] = 100;		//kg/s
	fraction[0] = 0.20;
	fraction[1] = 0.05;
	prices[0] = 100;
	prices[1] = -500;

	int bestIndCnt = 1000;		// Minimum number of iterations for the best circuit to be the same
	int minIte = 0;				// Minimum number of iterations to be done
	int maxIte = 10000;			// Maximum number of iterations possible
	bool time_GA = false;

	vector<int> best_circuit;


	Genetic_Algorithm GA(num_units, num_circuits, prob_CO, 
		prob_Mut, tol, max_iter, time_GA, flow, fraction, 
		prices, num_components);
	best_circuit = GA.runAlgo(bestIndCnt, minIte, maxIte);

	if(time_GA)
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
	best_fitness = circ.Evaluate_Circuit(best_circuit, tol, max_iter, fraction);
	cout << "Fitness: " << best_fitness;
	cout << endl;

	system("pause");
	return 0;
}

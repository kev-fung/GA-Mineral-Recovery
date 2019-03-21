#include "Header.h"
#include "Circuit.h"

using namespace std;

template<typename T>
T input(T max, T min) //Validates the user input depending on type and range
{
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
			<< 100*fraction[0] << "% and " << 100 * fraction[1] << "%" << endl;
		cout << endl;
		cout << "Price of valuable component: " << prices[0] << "£ and waste " << prices[1] << "£" << endl;
		cout << endl;
		cout << "Simulation will start running now ..." << endl;
		break;
	case 2:
		cout << "Please type the number of components in the flow of the circuit: ";
		num_components = input<int>(20, 0); //input number of components
		cout << endl;

		flow.reserve(num_components); //resize fraction vector to the number of components
		cout << "\tInput flow of valuable component from feed rate in kg/s";
		flow[0] = input<double>(500, 0);
		cout << endl;
		for (int i = 1; i < fraction.size(); i++)
		{
			cout << "\tInput flow of waste " << i << " component from feed rate in kg/s";
			flow[i] = input<double>(500, 0);
			cout << endl;
		}

		fraction.reserve(num_components); //resize fraction vector to the number of components
		cout << "\tInput fraction of valuable component going into concentrate stream: ";
		fraction[0] = input<double>(1, 0);
		cout << endl;
		for (int i = 1; i < fraction.size(); i++)
		{
			cout << "\tInput fraction of waste component " << i << " going into concentrate stream: ";
			fraction[i] = input<double>(1, 0);
			cout << endl;
		}
		
		prices.reserve(num_components); //resize fraction vector to the number of components
		cout << "\tInput price of valuable component: ";
		prices[0] = input<double>(2000, -2000);
		cout << endl;
		for (int i = 1; i < fraction.size(); i++)
		{
			cout << "\tInput price of waste " << i << " component as a negative value";
			prices[i] = input<double>(2000, -2000);
			cout << endl;
		}
		break;
	}

}

int main() {
	int numCircuits = 100; // TO TUNE
	int maxIte = 10000;

	// parameters for the Evaluate_Circuit function
	double tol = 1e-6;
	int max_iterations = 2000;

	// random seed
	srand(time(NULL));

	// Circuit and list of circuits
	vector<int> circuit(sizeVec, 0);
	vector<vector<int>> circuits(numCircuits, vector<int>(sizeVec, 0));

	// List of fitness values
	vector<double> fitVec(numCircuits, 0);
		
	// Generating the parents
	cout << "Generating parents" << endl;
	for (int i = 0; i < numCircuits; i++) {
		while(!Check_Validity(circuit)){  
			generateCircuit(circuit);
		}
		Circuit circ(100.0, -500.0, 10, 100);

		circuits[i] = circuit;
		fitVec[i] = circ.Evaluate_Circuit(circuit, tol, max_iterations);
	
		// Reinitialise the vector with 0
		for (int j = 0; j < sizeVec; j++) {
			circuit[j] = 0;
		}
	}
	cout << endl;


	// Check the vectors.
	cout << "Input Vectors" << endl;
	for (int i = 0; i < numCircuits; i++) {
		for (int j = 0; j < sizeVec; j++) {
			cout << circuits[i][j] << " ";
		}
		cout << " Fitness: " << fitVec[i] << endl;
	}
	cout << endl;


	vector<int> best_circuit;
	// Genetic algorithm
	cout << "Genetic algorithm" << endl;
	best_circuit = geneticAlgo(circuits, fitVec, maxIte, tol, max_iterations);
	//cout << endl;

	// Print the output.
	cout << "Output best vector" << endl;
	for (int j = 0; j < sizeVec; j++) {
		cout << best_circuit[j] << " ";
	}

	Circuit circ(100.0, -500.0, 10, 100);
	double best_fitness;
	best_fitness = circ.Evaluate_Circuit(best_circuit, tol, max_iterations);
	cout << "Fitness: " << best_fitness;
	cout << endl;
	

	system("pause");
}

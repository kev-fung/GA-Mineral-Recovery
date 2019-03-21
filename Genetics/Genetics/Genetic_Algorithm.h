#pragma once
#include "Validity.h"
#include <vector>

class Genetic_Algorithm {
public:
	// Constructors:
	Genetic_Algorithm(int num_units, int numCircuits, double pCrossOver, double pMut, double tol, int max_iterations, bool timeGA);
	~Genetic_Algorithm();

	// Methods:
	void generateCircuit(std::vector<int> &vals);
	std::vector<int> geneticAlgo(int minIte, int maxIte, int bestIndCnt, Validity &val);
	std::vector<int> runAlgo(int bestIndCnt, int minIte, int maxIte);
	double wTime();

private:

	// Number of units and size of the vector
	int num_units;						// Number of units in a circuit
	int sizeVec;						// Initialise size of the GA circuit vector

	// Parameters for Evaluate_Circuit
	double tol;							// 1e-6
	int max_iterations;					// 2000

	// Genetic algorithm parameters.
	double proCrossOver;				//= 1.;	// Probability of cross-over.
	double proMut;						//= 0.004;		// Probability of mutation.
	
	// Circuit and list of circuits
	int numCircuits;
	std::vector<int> circuit;
	std::vector<std::vector<int>> circuits;
	std::vector<double> fitVec;			// List of fitness values

	
	// Timing
	bool timeGA;
	double tdif = 0;
};




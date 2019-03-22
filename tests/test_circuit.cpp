#include <iostream>
#include <cmath>
#include "Circuit.h"
#include <vector>
#include "Genetic_Algorithm.h"

using namespace std;

int main()
{
	// Test 1
	vector<int> example1 = {0, 4, 3, 2, 0, 5, 4, 4, 6, 2, 1};

	//// Test 2
	vector<int> example2 = { 0, 1, 2, 3, 4, 4, 5, 6, 7, 7, 8, 8, 9, 10, 11, 10, 11, 10, 11, 10, 11 };

	//// Test 3
	vector<int> example3 = { 0, 1, 11, 2, 11, 3, 11, 4, 11, 5, 11, 6, 11, 7, 11, 8, 11, 9, 11, 10, 11 };

	// HOW TO USE CLASS:
	// Make new circuit object:
	// Note: circ() uses default settings of price and circuit feeds
	// The contructor below allows you to specify the pricings and the circuit feeds
	Circuit circ1;
	Circuit circ2;
	Circuit circ3;

	double tol = 1e-6;
	int max_iter = 1000;
	double fitness1 = circ1.Evaluate_Circuit(example1, tol, max_iter);
	double fitness2 = circ2.Evaluate_Circuit(example2, 0.0, 1);
	double fitness3 = circ3.Evaluate_Circuit(example3, 0.0, 1);

	//test1
	bool pass = true;
	double diff = fitness1 - 24.8165;

	cout << "Difference between true known value = " << diff << endl;

	if (diff > tol) // if fitness reaches this known value for the specified circuit (myarray[]) test should pass
		pass = false;

	if (pass)
	{
		cout << "pass" << endl;
	}
	else
	{
		cout << "fail" << endl;
	}

	cout << "Fitness: " << fitness1 << endl;

	////// Test 2
	//std::cout << "Evaluate_Circuit(Example2, 0.0, 1) close to 42000.0:\n";
	//std::cout << fitness2 << "<---\n";
	//if (std::fabs(fitness2 - 42000.0) < 1.0e-8)
	//	std::cout << "pass\n";
	//else
	//	std::cout << "fail\n";

	////// Test 3
	//std::cout << "Evaluate_Circuit(Example3, 0.0, 1) close to 37500.0:\n";
	//std::cout << fitness3 << "<---\n";
	//if (std::fabs(fitness3 - 37500.0) < 1.0e-8)
	//	std::cout << "pass\n";
	//else
	//	std::cout << "fail\n";

	system("pause");
	return 0;
}
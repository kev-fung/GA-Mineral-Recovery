#include "Circuit.h"
#include <vector>
#include "Header.h"

using namespace std;

//int main()
//{
//	vector<int> example;
//	int myarray[] = { 0, 4, 3, 2, 0, 5, 4, 4, 6, 2, 1 }; //{ 6, 16, 7, 7, 13, 11, 12, 15, 5, 3, 6, 0, 2, 14, 12, 1, 12, 14, 11, 5, 16, 11, 9, 4, 1, 0, 8, 5, 10, 2, 6 }; //	// { 0, 1, 2, 3, 0, 0, 4 }; //	// //{ 0, 4, 3, 2, 0, 5, 4, 4, 6, 2, 1 }; // //{ 0, 1, 2, 3, 0, 0, 4 }; // // //
//	example.insert(example.begin(), myarray, myarray + 11);	// 31 //11 //7
// 
//
//	// HOW TO USE CLASS:
//	// Make new circuit object:
//	// Note: circ() uses default settings of price and circuit feeds
//	// The contructor below allows you to specify the pricings and the circuit feeds
//	Circuit circ(100.0, -500.0, 10, 100);
//
//	double tol = 1e-6;
//	int max_iter = 1000;
//	double fitness = circ.Evaluate_Circuit(example, tol, max_iter);
//
//	cout << "Fitness: " << fitness << endl;
//
//	system("pause");
//	return 0;
//}
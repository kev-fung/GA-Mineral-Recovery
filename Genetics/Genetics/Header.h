#pragma once

#include <iostream>
#include <vector>
//#include <cstdlib>
#include <cmath>
#include <stdlib.h>
#include "time.h"

using namespace std;

// Number of units and size of the vector
extern const int num_units;
extern int sizeVec;

// Parameters for Evaluate_Circuit
extern double tol; 
extern int max_iterations;

bool Check_Validity(vector<int> circuit_vector);

vector<int> geneticAlgo(vector<vector<int>> &circuits, vector<double>& fitVec, int minIte, int maxIte, int bestIndCnt, double proCrosOver, double proMut);

void generateCircuit(vector<int> &vals);

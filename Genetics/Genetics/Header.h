#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include "time.h"
#include <assert.h> // to remove?

using namespace std;

extern const int num_units;
extern const int sizeVec;

bool Check_Validity(vector<int> circuit_vector);

void geneticAlgo(vector<vector<int>> &circuits, vector<double>& fitVec, int iter, double tol, int max_iterations);

void generateCircuit(vector<int> &vals);

double Evaluate_Circuit(vector<int> circuit_vector, double tolerance, int max_iterations);

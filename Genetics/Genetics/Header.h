#pragma once

#include <iostream>
#include <vector>
#include <cstdlib>
#include <stdlib.h>
#include "time.h"
#include <assert.h> // to remove?

using namespace std;

extern const int num_units;
extern int sizeVec;

bool Check_Validity(vector<int> circuit_vector);

vector<int> geneticAlgo(vector<vector<int>> &circuits, vector<double>& fitVec, int iter, double tol, int max_iterations);

void generateCircuit(vector<int> &vals);

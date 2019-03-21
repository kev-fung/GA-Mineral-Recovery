#pragma once
#include "CUnit.h"
#include <vector>

class Validity {
public:
	// Constructors:
	Validity(int num_units, int sizeVec);
	~Validity();

	// Methods:
	void mark_units(int unit_num);
	bool Check_Validity(std::vector<int> circuit_vector);

private:
	int num_units;
	int sizeVec;

	//int *units;
	std::vector<CUnit> units;

	int feed_num;
	bool seen_conc;
	bool seen_tail;

};
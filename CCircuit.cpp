#include <vector>

#include <stdio.h>
#include <CUnit.h>
#include <CCircuit.h>

using namespace std;
std::vector<CUnit> units(num_units);

//bool Check_Validity(int *circuit_vector)
//{
//  cout << vect.size()
//  return true;
//}

bool Check_Validity(vector<int> circuit_vector)
{
	//cout << circuit_vector.size();
	bool test1 = true;

	// Test 1 -- feed to every process --every process would receive something
	for (int i = 0; i < 10; i++) {

		if ((std::count(circuit_vector.begin(), circuit_vector.end(), i)) == false) {
			test1 = false;
		}
	}

	bool test2 = true;

	// Test 2 -- no pairs are the same
	for (int i = 1; i < circuit_vector.size() - 1; i += 2) {
		if (circuit_vector[i] == circuit_vector[i + 1]) {
			test2 = false;
		}
	}

	bool test3 = true;

	// Test 3 -- no messege send to itself
	int id = 0;
	for (int i = 1; i < circuit_vector.size() - 1; i += 2) {
		if (circuit_vector[i] == id || circuit_vector[i + 1] == id) {
			test3 = false;
		}
		cout << id << endl;
		id += 1;
	}

	bool test4 = true;
	vector<bool> tests4(10)

		// test 4 check that all unit paths lead to an circuit outlet		
		for (i = 0; i < 10; i++)
		{
			test4.push_back(mark_units(i));
		}

	// if not not valid
	if ((count(test4.begin(), test4.end(), 0)) >= 1) { test4 = false; }

	if (test1 = true && test2 = true && test3 = true && test4 = true) { return true; }
	else { return false; }
}


void mark_units(int unit_num) {

	if (units[unit_num].mark) return;

	units[unit_num].mark = true;

	bool  test2 = false;   bool test3 = false; bool test = false;

	// If we have seen this unit already exit
	// Mark that we have now seen the unit

	//If conc_num does not point at a circuit outlet recursively call the function
	int counter = 0;
	if (units[unit_num].conc_num < num_units) {
		mark_units(units[unit_num].conc_num);
		counter += 1;
		if (counter >= 50) { test2 = false; break; }
	}
	else {
		// ...Potentially do something to indicate that you have seen an exit
		test2 = true;
	}

	counter = 0;
	//If tails_num does not point at a circuit outlet recursively call the function
	if (units[unit_num].tails_num < num_units) {
		mark_units(units[unit_num].tails_num);
		counter += 1;
		if (counter >= 50) { test3 = false; break; }
	}
	else {
		// ...Potentially do something to indicate that you have seen an exit
		test3 = true;
	}

	if (test2 = true && test3 = true) { test = true; }
	else (test = false;)

	return test;
}

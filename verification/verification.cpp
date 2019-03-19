#include "Header.h"
#include "CUnit.h"

using namespace std;
int num_units;
CUnit *units;

//bool Check_Validity(int *circuit_vector)
//{
//  cout << vect.size()
//  return true;
//}


int mark_units(int unit_num, vector<int> circuit_vector) {

	for (int i = 0; i < num_units; i++)
	{
		// Fill up our unit_list vector from circuit_vector:
		// We'll be using unit_list to pick out units in this class.
		CUnit unit(i, circuit_vector[1 + i], circuit_vector[i + 2]);
		units[i] = unit;

		// Initialise feeds
		//units[i].feed = CStream(circuit_feed);

	}
	
	if (units[unit_num].mark) return -1; //this unit has already been seen

	units[unit_num].mark = true; // Mark that we have now seen the unit

	//bool  test2 = false;   bool test3 = false; bool test = false;
	bool test2, test3, test;
	

	//If conc_num does not point at a circuit outlet recursively call the function
	int counter = 0;
	if (units[unit_num].conc_num < num_units && counter <= 50) {
		mark_units(units[unit_num].conc_num, circuit_vector);
		counter += 1;
		if (counter == 50) { test2 = false; }
	}
	else {
		// ...Potentially do something to indicate that you have seen an exit
		test2 = true;
	}

	counter = 0;
	//If tails_num does not point at a circuit outlet recursively call the function
	if (units[unit_num].tails_num < num_units && counter <= 50) {
		mark_units(units[unit_num].tails_num, circuit_vector);
		counter += 1;
		if (counter == 50) { test3 = false; }
	}
	else {
		// ...Potentially do something to indicate that you have seen an exit
		test3 = true;
	}

	if (test2 == true && test3 == true) { test = true; }
	else { test = false; }

	return test;
}


bool Check_Validity(vector<int> circuit_vector)
{
	//cout << circuit_vector.size();
	bool test1 = true;

	// Test 1 -- feed to every process --every process would receive something
	for (int i = 0; i < num_units; i++) {

		if ((std::count(circuit_vector.begin(), circuit_vector.end(), i)) == false) {
			test1 = false;
		}
	}

	bool test2 = true;

	// Test 2 -- no pairs are the same
	for (int i = 1; i < (circuit_vector.size() - 1); i += 2) {
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
		//cout << id << endl;
		//id += 1;
	}

	bool test4 = true;
	vector<bool> tests4(num_units);

		// test 4 check that all unit paths lead to an circuit outlet		
		for (int i = 0; i < num_units; i++)
		{
			tests4.push_back(mark_units(i, circuit_vector));
		}

	// if not not valid
	if ((count(tests4.begin(), tests4.end(), 0)) >= 1) { test4 = false; }

	if (test1 == true && test2 == true && test3 == true && test4 == true) { return true; }
	else { return false; }

	if (test1 == true && test2 == true && test3 == true) { return true; }
	else { return false; }
}



int main() {
	vector<int> vec;

	for (int i = 0; i <= 11; i++) { vec.push_back(i); }
	for (int i = 11; i <= 21; i++) { vec.push_back(i - 11); }

	int myarray[] = { 0, 1, 2, 3, 0, 4, 0 }; //{ 0, 4, 3, 2, 0, 5, 4, 4, 6, 2, 1 };
	vec.insert(vec.begin(), myarray, myarray + 11);

	num_units = (vec.size() - 1) / 2;    // Number of units
	units = new CUnit[num_units];

	bool a = Check_Validity(vec);
	cout << a << endl;
	system("PAUSE");

}
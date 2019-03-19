#include "Header.h"
#include "CUnit.h"

using namespace std;

vector<CUnit> unit_list;
int num_units;
double flow[2] = { 10, 100 }; //flow for valuable and  waste component
CUnit circuit_feed, circuit_tails, circuit_conc; //feed, and two bins for tails and concentration


double Evaluate_Circuit(vector<int> circuit_vector, double tolerance, int max_iterations)
{
	for (int i = 0; i < num_units; i++)
	{
		CUnit unit(i, circuit_vector[1 + i], circuit_vector[i + 2]);
		unit_list.insert(unit_list.begin() + i, unit);

		unit.feed = CStream(flow);
		unit.output_con_tail(); //THIS RESETS FEED TO ) FOR NOW //Can be changed
	}


	return 0;
}


int main()
{
	

	vector<int> circuit;
	int myarray[] = { 0, 4, 3, 2, 0, 5, 4, 4, 6, 2, 1 };
	circuit.insert(circuit.begin(), myarray, myarray + 11);

	num_units = (circuit.size() - 1) / 2;
	unit_list.resize(num_units);

	Evaluate_Circuit(circuit, 0.005, 1000);


	system("pause");
	return 0;
}
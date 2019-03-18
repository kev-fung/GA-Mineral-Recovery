#include "Header.h"
#include "CUnit.h"

using namespace std;

vector<CUnit> unit_list;
int num_units;


void mark_units(int unit_num)
{
	if (unit_list[unit_num].mark) //If we have seen this unit already exit
		return;
	unit_list[unit_num].mark = true; //Mark that we have now seen the unit

	//If conc_num does not point at a circuit outlet recursively call the function
	if (unit_list[unit_num].conc_num < num_units)
		mark_units(unit_list[unit_num].conc_num);

	else
		//…Potentially do something to indicate that you have seen an exit
		//If tails_num does not point at a circuit outlet recursively call the function
		if (unit_list[unit_num].tails_num < num_units)
			mark_units(unit_list[unit_num].tails_num);
		else
			int a = 2;
			//…Potentially do something to indicate that you have seen an exit
}

int main()
{
	double valuable_flow = 10;
	double waste_flow = 100;

	vector<int> circuit;
	int myarray[] = { 0, 4, 3, 2, 0, 5, 4, 4, 6, 2, 1 };
	circuit.insert(circuit.begin(), myarray, myarray + 11);

	num_units = (circuit.size() - 1) / 2;
	unit_list.resize(num_units);

	for (int i = 0; i < num_units; i++)
	{
		CUnit unit(i, circuit[1 + i], circuit[i + 2]);
		unit_list.insert(unit_list.begin() + i, unit);
		unit.input_rate_val = valuable_flow;
		unit.input_rate_wst = waste_flow;

		unit.output_con_tail();

	}


	system("pause");
	return 0;
}
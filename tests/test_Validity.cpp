#include <iostream>
#include "Genetic_Algorithm.h"
#include "Validity.h"

using namespace std;

int main()
{
	bool res;
	vector<int> false1{0, 3, 1, 5, 2, 1, 5, 4, 3};
	vector<int> false2{0, 2, 1, 0, 5, 4, 0, 2, 1};
	vector<int> true1{0, 1, 2, 4, 3, 1, 5, 4, 0};

	Validity a(4, 9);

	cout << "FALSE1...";
	res = a.Check_Validity(false1);
	if (res == false) std::cout << "pass\n";
	else std::cout << "fail\n";

	cout << "FALSE2...";
	res = a.Check_Validity(false2);
	if (res == false) std::cout << "pass\n";
	else std::cout << "fail\n";

	cout << "TRUE1...";
	res = a.Check_Validity(true1);
	if (res == true) std::cout << "pass\n";
	else std::cout << "fail\n";

	system("pause");
	return 0;
}

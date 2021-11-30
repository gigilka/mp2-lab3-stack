#include <iostream>
#include <fstream>
#include <clocale>
#include <string>
#include "Calc.h"
using namespace std;

int main() {
	setlocale(LC_ALL, "russian");
	setlocale(LC_NUMERIC, "eng");
	string exp;
	Calc calc;
	int i = 1;
	while (i!=0) {
		cout << "Input the expression" << endl;
		getline(cin,exp);
		calc.SetExp(exp);
		cout << endl;
		cout << "Settled expression: " << calc.GetExp() << endl;
		if (calc.CheckExp()) {
			cout << "Correct braces" << endl;
		}
		else {
			cout << "Incorrect braces" << endl;
		}
		calc.PostEdit();
		cout << "Postfix " << calc.GetPost() << endl;
		try {
			cout << "Postfix calculated: " << calc.CalcPost() << endl;
			cout << "Expression calculated: " << calc.Calculate() <<endl;
		}
		catch (...) {
			cout << "Exception" << endl;
		}
	}
	return 0;
}
#include "test_func.h"
#include <iostream>


void info() {
	cout << "—˜_’l(Theo.out_value)‚Æo—Í‚ªA" << "\n" << "ˆê’v‚·‚ê‚Îu1v‚ðA" << "\n" << "ˆê’v‚µ‚È‚¯‚ê‚Îu0v‚ð•Ô‚µ‚Ü‚·B"
		<< "\n" << "----------" << "\n\n";
}
void title(string t) {
	cout <<"y" << t << "z" << "\n";
}

bool compare(int a, int b) {
	if (a == b) {
		return true;
	}
	else {
		return false;
	}
}

void value_disp(string in, string theo) {
	cout << "in_value(" << in << ") b theo.out_value(" <<theo<<")\n";
}

void res(int out) {
	cout << out << "\n\n";
}
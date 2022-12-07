#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <cmath>
#include <string>
#include <sstream>
using namespace std;

class Parabola {
public:
	Parabola(int a, int b, int c) :a{ a }, b{ b }, c{ c } {}
	string to_string() const;
	double extremum() const { return calc(double(-b) / 2 / a); }
	double calc(double x) const { return double(a) * x * x + b * x + c; }

	friend bool operator||(const Parabola& a, const Parabola& b);
	friend bool operator/(const Parabola& a, const Parabola& b);
private:
	int a, b, c;
};

bool operator||(const Parabola& a, const Parabola& b) {
	return ((a.a == b.a) && (a.b == b.b) && (a.c == b.c));
}

bool operator/(const Parabola& a, const Parabola& b) {
	return (((a.b - b.b) * (a.b - b.b) - 4 * (a.a - b.a) * (a.c - b.c)) >= 0);
}

string Parabola::to_string() const {
	ostringstream os;
	os << "y = " << a << "x^2" << (b>=0?"+":"") << b << "x" << (c >= 0 ? "+" : "") << c;
	return os.str();
}

int main() {
	Parabola p(1, 0, 0);
	cout << p.to_string() << endl;
	Parabola p2(1, 0, 0);
	cout << (p || p2); // 1
	Parabola p3(-4, 0, -1);
	cout << (p || p3); // 0
	cout << p3.extremum(); // -1
	cout << (p / p3); // 0
	Parabola p4(1, 3, 0);
	cout << (p / p4); // 1
	//ans 10-101
	return 0;
}

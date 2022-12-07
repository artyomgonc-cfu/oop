#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <cmath>
#include <string>
#include <sstream>
using namespace std;

class Vect {
public:
	Vect(int x, int y, int z) :coords{ x, y, z } {}
	int get_coord(int n) const { return coords[n]; }
	double get_len() const;
	string to_string() const;
private:
	vector<int> coords;
};

double Vect::get_len() const {
	double len = 0;
	for (auto i : coords)
		len += i * i;
	return sqrt(len);
}

string Vect::to_string() const {
	ostringstream os;
	os << "{ ";
	for (int i = 0; i < 3; i++) {
		os << coords[i];
		if (i != 2) os << ", ";
	}
	os << " }";
	return os.str();
}

Vect operator+(const Vect& a, const Vect& b) {
	return { a.get_coord(0) + b.get_coord(0), a.get_coord(1) + b.get_coord(1), a.get_coord(2) + b.get_coord(2) };
}

Vect operator-(const Vect& a, const Vect& b) {
	return { a.get_coord(0) - b.get_coord(0), a.get_coord(1) - b.get_coord(1), a.get_coord(2) - b.get_coord(2) };
}

int operator*(const Vect& a, const Vect& b) {
	int ans = 0;
	for (int i = 0; i < 3; i++)
		ans += a.get_coord(i) * b.get_coord(i);
	return ans;
}

double getcos(const Vect& a, const Vect& b) {
	return double(a * b) / a.get_len() / b.get_len();
}

void menu() {
	cout << "Menu:\n[1]: A + B\n[2]: A - B\n[3]: (A, B)\n[4]: cos(A, B)\n[5]: A length\n[6]: B length\n[7]: exit\n";
}

int main() {

	int a, b, c;
	cout << "Input vector A: ";
	cin >> a >> b >> c;
	Vect av{ a, b, c };

	cout << "Input vector B: ";
	cin >> a >> b >> c;
	Vect bv{ a, b, c };

	cout << "Vector A: " << av.to_string() << endl << "Vector B: " << bv.to_string() << endl;

	menu();
	while (true) {
		cout << ">> ";
		int com; cin >> com;
		if (com == 7) break;

		cout << "Answer: ";
		if (com == 1)
			cout << (av + bv).to_string();
		if (com == 2)
			cout << (av - bv).to_string();
		if (com == 3)
			cout << av * bv;
		if (com == 4)
			cout << getcos(av, bv);
		if (com == 5)
			cout << av.get_len();
		if (com == 6)
			cout << bv.get_len();
		cout << endl;
	}

	return 0;
}

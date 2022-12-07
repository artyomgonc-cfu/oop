#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <cmath>
#include <string>
using namespace std;

struct Point {
	double x, y;
};

class Triangle {
public:
	Triangle();
	Triangle(Point a, Point b, Point c);
	Triangle(const Triangle& t);

	~Triangle();

	Point get_element(int i) const { return *pts[i]; }

	virtual double area() const;
	double perimeter() const;
	bool correct() const { return area() > 0; }
	double side_len(int i, int j) const;
	virtual double angle(int i) const;
	bool is_eql() const { return eq; }
protected:
	vector<Point*> pts;
	bool eq = false;
};

Triangle::Triangle()
	:pts{ new Point{0,0}, new Point{0,0}, new Point{0,0} } {}

Triangle::Triangle(Point a, Point b, Point c)
	:pts{ new Point{a.x,a.y}, new Point{b.x,b.y}, new Point{c.x,c.y} } {}

Triangle::Triangle(const Triangle& t) {
	for (int i = 0; i < 3; i++) {
		Point el = t.get_element(i);
		pts.push_back(new Point{ el.x, el.y });
	}
}

double Triangle::area() const {
	return double(abs(pts[0]->x * (pts[1]->y - pts[2]->y) + pts[1]->x * (pts[2]->y - pts[0]->y) + pts[2]->x * (pts[0]->y - pts[1]->y))) / 2;
}

double Triangle::perimeter() const {
	double p = side_len(0, 2);
	for (int i = 0; i < pts.size() - 1; i++)
		p += side_len(i, i + 1);
	return p;
}

double Triangle::side_len(int i, int j) const {
	return sqrt(pow(pts[i]->x - pts[j]->x, 2) + pow(pts[i]->y - pts[j]->y, 2));
}

double Triangle::angle(int i) const {
	double contr_len = side_len((i + 1) % 3, (i + 2) % 3);
	double adj1_len = side_len((i + 1) % 3, i);
	double adj2_len = side_len((i + 2) % 3, i);

	double cosval = pow(adj1_len, 2) + pow(adj2_len, 2) - pow(contr_len, 2);
	cosval /= 2.0 * adj1_len * adj2_len;
	return acos(cosval) * 180 / acos(-1);
}

Triangle::~Triangle() {
	for (auto i : pts)
		delete i;
}

class Equilateral : public Triangle {
public:
	Equilateral(Point a, Point b, Point c);
	double angle(int i) const override { return 60; }
	double area() const override { return pow(side_len(0, 1), 2) * sqrt(3) / 4; }
};

Equilateral::Equilateral(Point a, Point b, Point c)
	:Triangle(a, b, c)
{
	if (side_len(0, 1) - side_len(1, 2) > 1e-7 || side_len(0, 1) - side_len(0, 2) > 1e-7)
		throw runtime_error("Bad triangle");
	eq = true;
}

bool operator==(const Triangle& a, const Triangle& b) {
	for (int i = 0; i < 3; i++)
		if (abs(a.angle(i) - b.angle(0)) < 1e-7 &&
			abs(a.side_len(i, (i + 1) % 3) - b.side_len(0, 1)) < 1e-7 && 
			abs(a.side_len(i, (i + 2) % 3) - b.side_len(0, 2)) < 1e-7)
			return true;

	return false;
}

void elab(const vector<Triangle*>& trs) {
	for (int i = 0; i < trs.size(); i++)
		for (int j = i + 1; j < trs.size(); j++)
			if (*trs[i] == *trs[j])
				cout << "Same: " << i << " " << j << "\n";

	double minv = 1e9;
	int mini;
	for (int i = 0; i < trs.size(); i++)
		if (trs[i]->is_eql() && trs[i]->side_len(0, 1) < minv) {
			minv = trs[i]->side_len(0, 1);
			mini = i;
		}

	cout << mini << endl;
}

int main() {
	vector<Triangle*> trs;
	trs.push_back(new Triangle{ {0,0}, {0.1, 0.1}, {0.1, 0} });
	trs.push_back(new Equilateral{ {0,0}, {0.5, sqrt(3) / 2}, {1, 0} });
	trs.push_back(new Equilateral{ {0,0}, {5, sqrt(3)*5}, {10, 0} });
	trs.push_back(new Equilateral{ {0,0}, {5, sqrt(3)*5}, {10, 0} });
	trs.push_back(new Triangle{ {0,0}, {10, 5}, {10, 0} });
	trs.push_back(new Triangle{ {7,1}, {2, 5}, {1, 0} });
	trs.push_back(new Triangle{ {0,0}, {0, 3}, {4, 0} });
	trs.push_back(new Triangle{ {0,0}, {0, 3}, {4, 0} });

	elab(trs);

	for (auto i : trs)
		delete i;

	return 0;
}

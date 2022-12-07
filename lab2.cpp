#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <cmath>
#include <string>
using namespace std;

struct Point {
	int x, y;
};

class Triangle {
public:
	Triangle();
	Triangle(Point a, Point b, Point c);
	Triangle(const Triangle& t);

	~Triangle();

	Point get_element(int i) const { return *pts[i]; }

	double area() const;
	double perimeter() const;
	bool correct() const { return area() > 0; }
	double side_len(int i, int j) const;
	double angle(int i) const;
private:
	vector<Point*> pts;
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
	return double(abs(pts[0]->x * (pts[1]->y - pts[2]->y) + pts[1]->x * (pts[2]->y - pts[0]->y) + pts[2]->x * (pts[0]->y - pts[1]->y)))/2;
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


int main() {
	Triangle a{ {0,0}, {0, 3}, {4, 0} };
	cout << "area: " << a.area() << endl;
	cout << "perimeter: " << a.perimeter() << endl;
	cout << "angle at (0, 0): " << a.angle(0) << endl;

	return 0;
}

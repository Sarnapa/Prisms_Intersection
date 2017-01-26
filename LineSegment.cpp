#include <iostream>
#include <sstream>
#include <cmath>
#include "LineSegment.h"

using namespace std;

LineSegment::LineSegment() 
{
}

LineSegment::LineSegment(double x1, double y1, double x2, double y2): v1(Vertex(x1, y1)), v2(Vertex(x2, y2))
{
}

LineSegment::LineSegment(const Vertex& _v1, const Vertex& _v2) : v1(_v1), v2(_v2)
{
}

LineSegment::LineSegment(const LineSegment& segment) 
{
	this->v1 = segment.v1;
	this->v2 = segment.v2;
}


LineSegment &LineSegment::operator=(const LineSegment& segment) 
{
	this->v1 = segment.v1;
	this->v2 = segment.v2;
	return *this;
}

void LineSegment::setV1(const Vertex& v1) 
{
	this->v1 = v1;
}

void LineSegment::setV2(const Vertex& v2)
{
	this->v2 = v2;
}

Vertex LineSegment::getV1() const
{
	return v1;
}

Vertex LineSegment::getV2() const
{
	return v2;
}


bool LineSegment::isOnSegment(const Vertex& p, const Vertex& q, const Vertex& r)
{
	if (q.getX() <= fmax(p.getX(), r.getX()) && q.getX() >= min(p.getX(), r.getY()) &&
		q.getY() <= fmax(p.getY(), r.getY()) && q.getY() >= min(p.getY(), r.getY()))
		return true;

	return false;
}

bool LineSegment::isOnSegment(const Vertex& q)
{
	if (q.getX() <= fmax(v1.getX(), v2.getX()) && q.getX() >= min(v1.getX(), v2.getY()) &&
		q.getY() <= fmax(v1.getY(), v2.getY()) && q.getY() >= min(v1.getY(), v2.getY()))
		return true;

	return false;
}

int LineSegment::getOrientation(const Vertex& p, const Vertex& q, const Vertex& r)
{
	int val = (q.getY() - p.getY()) * (r.getX() - q.getX()) - (q.getX() - p.getX()) * (r.getY() - q.getY());

	if (val == 0) return 0;  // colinear

	return (val > 0) ? 1 : 2; // clock or counterclock wise
}

bool LineSegment::doIntersect(const LineSegment& line) const
{
	// Find the four orientations needed for general and special cases
	int o1 = getOrientation(v1, v2, line.v1);
	int o2 = getOrientation(v1, v2, line.v2);
	int o3 = getOrientation(line.v1, line.v2, v1);
	int o4 = getOrientation(line.v1, line.v2, v2);

	// General case
	if (o1 != o2 && o3 != o4)
		return true;

	// Special Cases
	// v1, v2 and line.v1 are colinear and line.v1 lies on segment v1-v2
	if (o1 == 0 && isOnSegment(v1, line.v1, v2)) return true;

	// v1, v2 and line.v2 are colinear and v2 lies on segment v1-v2
	if (o2 == 0 && isOnSegment(v1, line.v2, v2)) return true;

	// line.v1, line.v2 and v1 are colinear and v1 lies on segment line.v1-line.v2
	if (o3 == 0 && isOnSegment(line.v1, v1, line.v2)) return true;

	// line.v1, line.v2 and v2 are colinear and v2 lies on segment line.v1-line.v2
	if (o4 == 0 && isOnSegment(line.v1, v2, line.v2)) return true;

	return false; // Doesn't fall in any of the above cases
}


pair<bool, Vertex> LineSegment::getIntersectionPoint(const LineSegment& line) const 
{
	double x1 = v1.getX();
	double y1 = v1.getY();
	double x2 = v2.getX();
	double y2 = v2.getY();
	double x3 = line.v1.getX();
	double y3 = line.v1.getY();
	double x4 = line.v2.getX();
	double y4 = line.v2.getY();

	double d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);
	//cout << (x1 - x2) << " " << (y3 - y4) << " " << (y1 - y2) << " " << (x3 - x4) << endl;
	if (d == 0)
	{
		return pair<bool, Vertex>(false, Vertex());
	}

	if (v1 == line.v1 || v1 == line.v2)
		return pair<bool, Vertex>(true, v1);
	if (v2 == line.v1 || v2 == line.v2)
		return pair<bool, Vertex>(true, v2);

	double intersectionX = ((x3 - x4) * (x1 * y2 - y1 * x2) - (x1 - x2) * (x3 * y4 - y3 * x4)) / d;
	double intersectionY = ((y3 - y4) * (x1 * y2 - y1 * x2) - (y1 - y2) * (x3 * y4 - y3 * x4)) / d;

	if (intersectionX + EPSILON < min(x1, x2) || intersectionX > max(x1, x2) + EPSILON) 
	{
		//cout << "1a" << endl;
		return pair<bool, Vertex>(false, Vertex());
	}
	else if (intersectionX + EPSILON < min(x3, x4) || intersectionX > max(x3, x4) + EPSILON)
	{
		//cout << "1b" << endl;
		return pair<bool, Vertex>(false, Vertex());
	}
	else if (intersectionY + EPSILON < min(y1, y2) || intersectionY > max(y1, y2) + EPSILON)
	{
		//cout << "1c" << endl;
		return pair<bool, Vertex>(false, Vertex());
	}
	else if (intersectionY + EPSILON < min(y3, y4) || intersectionY > max(y3, y4) + EPSILON)
	{
		//cout << "1d" << endl;
		return pair<bool, Vertex>(false, Vertex());
	}
	else 
	{
		//cout << "1e" << endl;
		return pair<bool, Vertex>(true, Vertex(intersectionX, intersectionY, true));
	}
}

string LineSegment::toString() const 
{
	stringstream ss;
	ss << "LineSegment: [" << v1.toString() << ", " << v2.toString() << "]";
	return ss.str();
}

bool LineSegment::approximatelyEqual(double a, double b) 
{
	return fabs(a - b) <= fmax(1.0f, max(fabs(a), fabs(b))) * EPSILON;
}

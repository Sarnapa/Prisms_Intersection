/*
	Micha³ Piotrak
	numer albumu: 269336
	Przeciêcie graniastos³upów
*/

#ifndef LINESEGMENT_H
#define LINESEGMENT_H

#include "Vertex.h"

using namespace std;

class LineSegment 
{
private:
	Vertex v1, v2;

	static bool approximatelyEqual(double a, double b);

	// the function checks if second point lies on line segment defined by first and third points
	// this function is for 3 colinear points
	static bool isOnSegment(const Vertex&, const Vertex&, const Vertex&);

public:
	LineSegment();
	LineSegment(const Vertex&, const Vertex&);
	LineSegment(double, double, double, double);
	LineSegment(const LineSegment&);

	LineSegment &operator=(const LineSegment&);

	void setV1(const Vertex&);
	void setV2(const Vertex&);
	Vertex getV1() const;
	Vertex getV2() const;
	
	// To find orientation of ordered triplet
	// The function returns following values
	// 0 --> Colinear
	// 1 --> Clockwise
	// 2 --> Counterclockwise
	static int getOrientation(const Vertex&, const Vertex&, const Vertex&);

	// the function checks if point lies on this line segment
	// this function is for 3 colinear points
	bool isOnSegment(const Vertex&);

	// check if point lies on line
	bool isOnLine(const Vertex&) const;

	// The function that returns true if line segment
	// and other line segment intersect.
	bool doIntersect(const LineSegment&) const;
	
	//To find intersection point
	pair<bool, Vertex> getIntersectionPoint(const LineSegment&) const;

	string toString() const;
};

#endif
/*
	Micha³ Piotrak
	numer albumu: 269336
	Przeciêcie graniastos³upów
*/

#include "Vertex.h"

Vertex::Vertex(): x(-1.0), y(-1.0) {}

Vertex::Vertex(double _x, double _y): x(_x), y(_y) {}

Vertex::Vertex(double _x, double _y, bool _isIntersectionPoint) : x(_x), y(_y), visited(false), isIntersectionPoint(_isIntersectionPoint) {}

Vertex::Vertex(const Vertex& otherVertex): x(otherVertex.x), y(otherVertex.y), visited(otherVertex.visited), isIntersectionPoint(otherVertex.isIntersectionPoint) {}

Vertex::~Vertex()
{
}

Vertex& Vertex::operator=(const Vertex& otherVertex)
{
    x = otherVertex.x;
    y = otherVertex.y;
	visited = otherVertex.visited;
	isIntersectionPoint = otherVertex.isIntersectionPoint;
    return *this;
}

bool Vertex::operator==(const Vertex& otherVertex) const
{
	return approxEqual(x, otherVertex.x) && approxEqual(y, otherVertex.y);
}

bool Vertex::approxEqual(double a, double b)
{
	//return a == b;
	//return fabs(a - b) <= fmax(1.0, fmax(fabs(a), fabs(b))) * EPSILON;
	return fabs(a - b) <= EPSILON;

}

void Vertex::setX(double x)
{
    this->x = x;
}

void Vertex::setY(double y)
{
    this->y = y;
}

void Vertex::setIntersectionPoint(bool isIntersectionPoint)
{
	this->isIntersectionPoint = isIntersectionPoint;
}

void Vertex::setVisited(bool visited)
{
	this->visited = visited;
}

double Vertex::getX() const
{
    return x;
}

double Vertex::getY() const
{
    return y;
}

bool Vertex::getVisited() const
{
	return visited;
}

bool Vertex::getIsIntersectionPoint() const
{
	return isIntersectionPoint;
}

double Vertex::getDistance(const Vertex &v) const 
{
	double dx = v.x - x;
	double dy = v.y - y;
	return sqrt(dx * dx + dy * dy);
}

void Vertex::printVertex() const
{
	//cout << "(" << x << ", " << y << ", " << isIntersectionPoint << ", " << visited << ")" << endl;
	cout << "(" << x << ", " << y << ")";
}

string Vertex::toString() const
{
	stringstream vertexString;
	//vertexString << "(" << x << ", " << y << ", " << isIntersectionPoint << ", " << visited << ")";
	vertexString << "(" << x << ", " << y << ")";
	return vertexString.str();
}

#include "Vertex.h"

Vertex::Vertex(double _x, double _y): x(_x), y(_y) {}

Vertex::Vertex(const Vertex& otherVertex): x(otherVertex.x), y(otherVertex.y) {}

Vertex::~Vertex()
{

}

Vertex& Vertex::operator=(const Vertex& otherVertex)
{
    x = otherVertex.x;
    y = otherVertex.y;
    return *this;
}

bool Vertex::operator==(const Vertex& otherVertex) const
{
    if(x == otherVertex.x && y == otherVertex.y)
        return true;
    else
        return false;
}

void Vertex::setX(double x)
{
    this->x = x;
}

void Vertex::setY(double y)
{
    this->y = y;
}

double Vertex::getX() const
{
    return x;
}

double Vertex::getY() const
{
    return y;
}

void Vertex::printVertex() const
{
    cout << x << " " << y << endl;
}


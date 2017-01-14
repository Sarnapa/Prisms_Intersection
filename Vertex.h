#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class Vertex
{
    private:
        double x, y;
    public:
		Vertex();
        Vertex(double, double);
        Vertex(const Vertex&);
        ~Vertex();

        Vertex& operator=(const Vertex&);
        bool operator==(const Vertex&) const;

        void setX(double);
        void setY(double);
        double getX() const;
        double getY() const;

        void printVertex() const;
		string toString() const;
};

#endif // VERTEX_H

#ifndef VERTEX_H
#define VERTEX_H

#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <cmath>

#define EPSILON 0.0005

using namespace std;

class Vertex
{
    private:
        double x, y;
		bool visited = false;
		bool isIntersectionPoint = false;

		static bool approxEqual(float, float);
    public:
		Vertex();
        Vertex(double, double);
		Vertex(double, double, bool);
        Vertex(const Vertex&);
        ~Vertex();

        Vertex& operator=(const Vertex&);
        bool operator==(const Vertex&) const;

        void setX(double);
        void setY(double);
		void setIntersectionPoint(bool);
        double getX() const;
        double getY() const;
		bool getVisited() const;
		bool getIsIntersectionPoint() const;

		double getDistance(const Vertex&) const;

        void printVertex() const;
		string toString() const;
};

#endif // VERTEX_H

#ifndef POLYGON_H
#define POLYGON_H

#include <vector>

#include "Vertex.h"
#include "LineSegment.h"

using namespace std;

class Polygon
{
    private:
        vector<Vertex> verticesList;
		double xMin, xMax, yMin, yMax;

		void updateMinMax(const Vertex&);
		void addVertex(const Vertex&);
    public:
		Polygon();
        Polygon(vector<Vertex>);
        Polygon(const Polygon&);
        ~Polygon();

        Polygon& operator=(const Polygon&);
        bool operator==(const Polygon&) const;

		bool isInside(const Vertex&);
		
		double getXMin();
		double getYMin();
		double getXMax();
		double getYMax();
        vector<Vertex> getVerticesList() const;

        void printPolygon() const;
		string toString() const;
};

#endif // POLYGON_H

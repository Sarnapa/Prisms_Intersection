/*
	Micha³ Piotrak
	numer albumu: 269336
	Przeciêcie graniastos³upów
*/

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
		double xMin = 100.0;
		double xMax = -100.0;
		double yMin = 100.0;
		double yMax = -100.0;

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
		// check max, min value of two polygons
		bool checkMinMax(const Polygon&) const;
		void clearVertices();

		double getXMin();
		double getYMin();
		double getXMax();
		double getYMax();
        vector<Vertex> getVerticesList() const;
			
        void printPolygon() const;
		string toString() const;
};

#endif // POLYGON_H

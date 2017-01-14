#ifndef POLYGON_H
#define POLYGON_H

#include <vector>

#include "Vertex.h"

using namespace std;

class Polygon
{
    private:
        vector<Vertex> verticesList;
    public:
        Polygon(vector<Vertex>);
        Polygon(const Polygon&);
        ~Polygon();

        Polygon& operator=(const Polygon&);
        bool operator==(const Polygon&) const;

        void addVertex(const Vertex&);

        vector<Vertex> getVerticesList() const;

        void printPolygon() const;
		string toString() const;
};

#endif // POLYGON_H

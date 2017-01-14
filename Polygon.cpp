#include "Polygon.h"


Polygon::Polygon(vector<Vertex> verticesList)
{
    for(unsigned int i = 0; i < verticesList.size(); ++i)
        addVertex(verticesList[i]);
}

Polygon::Polygon(const Polygon& otherPolygon)
{
    for(unsigned int i = 0; i < otherPolygon.verticesList.size(); ++i)
        addVertex(otherPolygon.verticesList[i]);

}

Polygon& Polygon::operator=(const Polygon& otherPolygon)
{
    for(unsigned int i = 0; i < otherPolygon.verticesList.size(); ++i)
        addVertex(otherPolygon.verticesList[i]);
    return *this;
}

bool Polygon::operator==(const Polygon& otherPolygon) const
{
    bool isEqual;
    if(verticesList.size() != otherPolygon.verticesList.size())
        return false;
    for(unsigned int i = 0; i < verticesList.size(); ++i)
    {
        isEqual = false;
        for(unsigned int j = 0; j < verticesList.size(); ++j)
            if(verticesList[i] == otherPolygon.verticesList[j])
            {
                isEqual = true;
                j = verticesList.size();
            }
        if(!isEqual)
            return false;
    }
    return true;
}

void Polygon::addVertex(const Vertex &v)
{
    verticesList.push_back(v);
}

vector<Vertex> Polygon::getVerticesList() const
{
    return verticesList;
}

void Polygon::printPolygon() const
{
    for(unsigned int i = 0; i < verticesList.size(); ++i)
        cout << verticesList[i].toString() << " ";
    cout << endl;
}

string Polygon::toString() const
{
	stringstream polygonString;
	for (int i = 0; i < verticesList.size(); i++)
		polygonString << verticesList[i].toString() << " ";
	return polygonString.str();
}

Polygon::~Polygon()
{
}


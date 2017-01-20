#include "Prism.h"

Prism::Prism()
{}

Prism::Prism(int _id, Polygon _base, pair<double,double> heightRange): id(_id), base(_base)
{
	heightRanges.insert(make_pair(id, heightRange));
}

Prism::Prism(const Prism& otherPrism): id(otherPrism.id), base(otherPrism.base), heightRanges(otherPrism.heightRanges)
{
}

Prism& Prism::operator=(const Prism& otherPrism)
{
    id = otherPrism.id;
    base = otherPrism.base;
    heightRanges = otherPrism.heightRanges;
    return *this;
}

bool Prism::operator==(const Prism& otherPrism) const
{
    if(base == otherPrism.base && heightRanges == otherPrism.heightRanges)
        return true;
    else
        return false;
}

void Prism::addHeightRange(int id, pair<double, double> heightRange)
{
	heightRanges.insert(make_pair(id, heightRange));
}

void Prism::addHeightRanges(const map<int, pair<double, double>>& ranges)
{
	for (auto r : ranges) 
	{
		heightRanges.insert(r);
	}
}

int Prism::getId() const
{
    return id;
}

Polygon Prism::getBase() const
{
    return base;
}

map<int, pair<double, double>> Prism::getHeightRanges() const
{
    return heightRanges;
}

void Prism::printPrism() const
{
	for (auto i : heightRanges) 
	{
		cout << i.first <<  " " << i.second.first << " " << i.second.second << endl;
	}
	cout << "Base: ";
    base.printPolygon();
}

string Prism::toString() const
{
	stringstream prismsString;
	for (auto i : heightRanges)
	{
		prismsString << i.first << " " << i.second.first << " " << i.second.second << endl;
	}
	prismsString << "Base: " << base.toString() << endl << endl;

	return prismsString.str();
}

Prism::~Prism()
{

}

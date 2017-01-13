#include "Prism.h"

Prism::Prism(int _id, Polygon _base, pair<double,double> _heightRange): id(_id), base(_base), heightRange(_heightRange)
{
}

Prism::Prism(const Prism& otherPrism): id(otherPrism.id), base(otherPrism.base), heightRange(otherPrism.heightRange)
{
}

Prism& Prism::operator=(const Prism& otherPrism)
{
    id = otherPrism.id;
    base = otherPrism.base;
    heightRange = otherPrism.heightRange;
    return *this;
}

bool Prism::operator==(const Prism& otherPrism) const
{
    if(base == otherPrism.base && heightRange == otherPrism.heightRange)
        return true;
    else
        return false;
}

int Prism::getId() const
{
    return id;
}

Polygon Prism::getBase() const
{
    return base;
}

pair<double,double> Prism::getHeightRange() const
{
    return heightRange;
}

void Prism::printPrism() const
{
    cout << id << " " << heightRange.first << " " << heightRange.second << " ";
    base.printPolygon();
}

Prism::~Prism()
{

}

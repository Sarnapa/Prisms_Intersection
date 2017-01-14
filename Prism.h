#ifndef PRISM_H
#define PRISM_H

#include "Polygon.h"

class Prism
{
    private:
        int id;
        Polygon base;
        pair<double,double> heightRange;
    public:
        Prism(int, Polygon, pair<double,double>);
        Prism(const Prism&);
        ~Prism();

        Prism& operator=(const Prism&);
        bool operator==(const Prism&) const;

        int getId() const;
        Polygon getBase() const;
        pair<double,double> getHeightRange() const;

        void printPrism() const;
		string toString() const;
};

#endif // PRISM_H

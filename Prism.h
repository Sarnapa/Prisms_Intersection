#ifndef PRISM_H
#define PRISM_H

#include "Polygon.h"
#include <map>

class Prism
{
    private:
        int id;
        Polygon base;
        map<int, pair<double,double>> heightRanges;
    public:
		Prism();
		Prism(int, Polygon);
        Prism(int, Polygon, pair<double,double>);
        Prism(const Prism&);
        ~Prism();

        Prism& operator=(const Prism&);
        bool operator==(const Prism&) const;

		void addHeightRange(int, pair<double,double>);
		void addHeightRanges(const map<int, pair<double, double>>&);

        int getId() const;
        Polygon getBase() const;
		map<int, pair<double, double>> getHeightRanges() const;

        void printPrism() const;
		string toString() const;
};

#endif // PRISM_H

#ifndef PRISMSGENERATOR_H
#define PRISMSGENERATOR_H

#define _USE_MATH_DEFINES
#include <iostream>
#include <time.h>
#include <vector>
#include <math.h>
#include "Prism.h"

using namespace std;

class PrismsGenerator
{
	private:
		static int id;
		int prismsNumber;
		int maxVerticesNumber; // in prism base
		bool onlyConvex;
		double minRadius; // min value circle radius to build polygon
		double maxRadius;
		const double areaRange = 100.0; // to locate circle center and limit x,y coordinates

		Prism generateConvexBase() const;
		Prism generateBase() const;
		pair<double, double> generateHeightRange() const;
		int generateVerticesNumber() const;
		static double fRand(double fMin, double fMax); // rand for double
		static void incId();
    public:
        PrismsGenerator(int, int, bool);
        ~PrismsGenerator();

		vector<Prism> generatePrisms() const;
};

#endif // PRISMSGENERATOR_H

/*
	Micha³ Piotrak
	numer albumu: 269336
	Przeciêcie graniastos³upów
*/

#include "PrismsGenerator.h"

int PrismsGenerator::id = 0;

PrismsGenerator::PrismsGenerator(int _prismsNumber, int _maxVerticesNumber, bool _onlyConvex) : prismsNumber(_prismsNumber), maxVerticesNumber(_maxVerticesNumber > 50 ? 50 : _maxVerticesNumber), onlyConvex(_onlyConvex)
{
	srand(time(NULL));
	if (maxVerticesNumber < 3)
		maxVerticesNumber = 3;
	minRadius = doubleRound(fRand(10.0, 20.0));
	maxRadius = doubleRound(fRand(minRadius, 40.0));
	//areaRange = prismsNumber < 100 ? prismsNumber : 100;
}

vector<Prism> PrismsGenerator::generatePrisms() const
{
	vector<Prism> prismsVector;
	for (int i = 0; i < prismsNumber; ++i)
	{
		if (onlyConvex)
			prismsVector.push_back(generateConvexBase());
		else
			prismsVector.push_back(generateBase());
		incId();
	}
	return prismsVector;
}

Prism PrismsGenerator::generateConvexBase() const
{
	vector<Vertex> verticesVector;
	pair<double, double> heightRange = generateHeightRange();
	int verticesNumber;
	if (maxVerticesNumber != 3)
		verticesNumber = generateVerticesNumber();
	else
		verticesNumber = 3;

	double radius = doubleRound(fRand(minRadius, maxRadius));
	double circleCenterX = doubleRound(fRand((-areaRange) / 2, areaRange / 2));
	double circleCenterY = doubleRound(fRand((-areaRange) / 2, areaRange / 2));

	double step = 2.0 * M_PI / verticesNumber;
	double maxStep = step;
	double angle = 0.0f;
	for (int i = 0; i < verticesNumber; ++i)
	{
		double x = doubleRound(circleCenterX + radius * cos(angle));
		double y = doubleRound(circleCenterY + radius * sin(angle));
		if (i == verticesNumber - 2) // to avoid that start and last point will be the same
			angle += doubleRound(fRand(0.1, 2.0 * M_PI - angle - 0.1));
		else
			angle += doubleRound(fRand(0.1, maxStep));
		maxStep = (i + 2) * step - angle;
		verticesVector.push_back(Vertex(x,y));
	}
	return Prism(id, verticesVector, heightRange);
}

// polygon coordinates have to be located in ring created by small and big circle 
Prism PrismsGenerator::generateBase() const
{
	vector<Vertex> verticesVector;
	pair<double, double> heightRange = generateHeightRange();
	int verticesNumber = generateVerticesNumber();

	double radius = doubleRound(fRand(minRadius, maxRadius));
	double circleCenterX = doubleRound(fRand((-areaRange) / 2, areaRange / 2));
	double circleCenterY = doubleRound(fRand((-areaRange) / 2, areaRange / 2));

	double smallRadius = doubleRound(fRand(minRadius, radius));
	double bigRadius = doubleRound(fRand(radius, maxRadius));

	double step = 2.0 * M_PI / verticesNumber;
	double maxStep = step;
	double angle = 0.0;
	for (int i = 0; i < verticesNumber; ++i)
	{
		double r = doubleRound(fRand(smallRadius, bigRadius));
		double x = doubleRound(circleCenterX + r * cos(angle));
		double y = doubleRound(circleCenterY + r * sin(angle));
		if (i == verticesNumber - 2)
		{
			if (angle >= M_PI)
				angle += doubleRound(fRand(0.1, 2.0 * M_PI - angle - 0.1));
			else
				angle += doubleRound(fRand(M_PI - angle, M_PI)); // to avoid sides intersection
		}
		else
 			angle += doubleRound(fRand(0.1, maxStep));
		maxStep = (i + 2) * step - angle;
		verticesVector.push_back(Vertex(x, y));
	}
	return Prism(id, verticesVector, heightRange);
}

pair<double, double> PrismsGenerator::generateHeightRange() const
{
	double minZ = doubleRound(fRand(0.0, 20.0));
	double maxZ = doubleRound(fRand(minZ + 0.01, 40));
	return make_pair(minZ, maxZ);
}

int PrismsGenerator::generateVerticesNumber() const
{
	return (rand() % (maxVerticesNumber - 3) + 3);
}

// rand for double
double PrismsGenerator::fRand(double fMin, double fMax)
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

double PrismsGenerator::doubleRound(double d)
{
	return round(d * 1000) / 1000;
}

void PrismsGenerator::incId()
{
	++id;
}

PrismsGenerator::~PrismsGenerator()
{
}

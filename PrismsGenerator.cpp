#include "PrismsGenerator.h"

int PrismsGenerator::id = 0;

PrismsGenerator::PrismsGenerator(int _prismsNumber, int _maxVerticesNumber, bool _onlyConvex) : prismsNumber(_prismsNumber), onlyConvex(_onlyConvex)
{
	srand(time(NULL));
	if (_maxVerticesNumber < 3)
		maxVerticesNumber = 3;
	minRadius = rand() % 20;
	maxRadius = rand() % 20 + minRadius;
	areaRange = prismsNumber < 100 ? prismsNumber : 100;
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
	int verticesNumber = generateVerticesNumber();

    int radius = rand() % (maxRadius - minRadius) + minRadius;
	int circleCenterX = rand() % areaRange;
	int circleCenterY = rand() % areaRange;

	double maxStep = 2.0 * M_PI / verticesNumber;
	double angle = 0.0f;
	for (int i = 0; i < verticesNumber; ++i)
	{
		double x = circleCenterX + radius * cos(angle);
		double y = circleCenterY + radius * sin(angle);
		angle += fRand(0.0, maxStep);
		maxStep = (i + 2) * maxStep - angle;
		verticesVector.push_back(Vertex(x, y));
	}
	return Prism(id, verticesVector, heightRange);
}

Prism PrismsGenerator::generateBase() const
{
	vector<Vertex> verticesVector;
	pair<double, double> heightRange = generateHeightRange();
	int verticesNumber = generateVerticesNumber();
	
	return Prism(id, verticesVector, heightRange);
}

pair<double, double> PrismsGenerator::generateHeightRange() const
{
	double minZ = rand() % 20;
	double maxZ = rand() % 20 + minZ;
	return make_pair(minZ, maxZ);
}

int PrismsGenerator::generateVerticesNumber() const
{
	return (rand() % (maxVerticesNumber - 3) + 3);
}

double PrismsGenerator::fRand(double fMin, double fMax) // rand for double
{
	double f = (double)rand() / RAND_MAX;
	return fMin + f * (fMax - fMin);
}

void PrismsGenerator::incId()
{
	++id;
}

PrismsGenerator::~PrismsGenerator()
{
}

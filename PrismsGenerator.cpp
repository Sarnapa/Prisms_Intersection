#include "PrismsGenerator.h"

int PrismsGenerator::id = 0;

PrismsGenerator::PrismsGenerator(int _prismsNumber, int _maxVerticesNumber, bool _onlyConvex) : prismsNumber(_prismsNumber), maxVerticesNumber(_maxVerticesNumber), onlyConvex(_onlyConvex)
{
	srand(time(NULL));
	if (maxVerticesNumber < 3)
		maxVerticesNumber = 3;
	minRadius = fRand(2.0, 20.0);
	maxRadius = fRand(minRadius, 40.0);
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

	double radius = fRand(minRadius, maxRadius);
	double circleCenterX = fRand((-areaRange) / 2, areaRange / 2);
	double circleCenterY = fRand((-areaRange) / 2, areaRange / 2);

	double step = 2.0 * M_PI / verticesNumber;
	double maxStep = step;
	double angle = 0.0f;
	for (int i = 0; i < verticesNumber; ++i)
	{
		double x = circleCenterX + radius * cos(angle);
		double y = circleCenterY + radius * sin(angle);
		//cout << x << " " << y << " " << radius << " " << angle << " " << maxStep << endl;
		if (i == verticesNumber - 2) // to avoid that start and last point will be the same
			angle += fRand(0.0f, 2.0 * M_PI - angle - 0.1);
		else
			angle += fRand(0.0, maxStep);
		maxStep = (i + 2) * step - angle;
		verticesVector.push_back(Vertex(x, y));
	}
	//cout << endl;
	return Prism(id, verticesVector, heightRange);
}

// polygon coordinates have to be located in ring created by small and big circle 
Prism PrismsGenerator::generateBase() const
{
	vector<Vertex> verticesVector;
	pair<double, double> heightRange = generateHeightRange();
	int verticesNumber = generateVerticesNumber();

	double radius = fRand(minRadius, maxRadius);
	double circleCenterX = fRand((-areaRange) / 2, areaRange / 2);
	double circleCenterY = fRand((-areaRange) / 2, areaRange / 2);

	double smallRadius = fRand(minRadius, radius);
	double bigRadius = fRand(radius, maxRadius);

	double step = 2.0 * M_PI / verticesNumber;
	double maxStep = step;
	double angle = 0.0;
	for (int i = 0; i < verticesNumber; ++i)
	{
		double r = fRand(smallRadius, bigRadius);
		double x = circleCenterX + r * cos(angle);
		double y = circleCenterY + r * sin(angle);
		//cout << x << " " << y << " " << r << " " << angle << " " << maxStep << " " << (i + 2) * maxStep << endl;
		if (i == verticesNumber - 2)
		{
			if (angle >= M_PI)
				angle += fRand(0.0f, 2.0 * M_PI - angle - 0.1);
			else
				angle += fRand(M_PI - angle, M_PI); // to avoid sides intersection
		}
		else
 			angle += fRand(0.0, maxStep);
		maxStep = (i + 2) * step - angle;
		verticesVector.push_back(Vertex(x, y));
	}
	//cout << endl;
	return Prism(id, verticesVector, heightRange);
}

pair<double, double> PrismsGenerator::generateHeightRange() const
{
	double minZ = fRand(0.0, 20.0);
	double maxZ = fRand(minZ + 0.01, 40);
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

void PrismsGenerator::incId()
{
	++id;
}

PrismsGenerator::~PrismsGenerator()
{
}

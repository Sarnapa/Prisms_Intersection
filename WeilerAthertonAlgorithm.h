/*
	Micha³ Piotrak
	numer albumu: 269336
	Przeciêcie graniastos³upów
*/

#pragma once

#include <vector>
#include <map>
#include "Prism.h"

// Struct for sorting points
struct DistanceFunc
{
	DistanceFunc(const Vertex& _p) : p(_p) {}

	bool operator()(const Vertex& p1, const Vertex& p2) const
	{
		return p.getDistance(p1) < p.getDistance(p2);
	}

private:
	Vertex p;
};

class WeilerAthertonAlgorithm
{
private:
	Prism p1, p2;
	vector<Vertex> p1Vertices, p2Vertices;
	vector<Vertex> p1AllPoints, p2AllPoints;
	vector<Prism> inputParts;
	vector<Prism> intersectionParts;
	vector<Prism> results;
	
	void generateAllPoints();
	void sortPoints(int, multimap<int, Vertex>);
	bool checkIfTheSame(); // polygon
	bool checkIfInside();
	int getStartPoint();
	int getNext(int, Vertex);
	int getFromOtherPolygon(int, Vertex);
	int countIntersectionPointsNumber();
public:
	WeilerAthertonAlgorithm(const Prism&, const Prism&);
	~WeilerAthertonAlgorithm();

	void doAlgo();

	vector<Prism> returnInputParts();
	vector<Prism> returnIntersectionParts();
	vector<Prism> returnResult();

	void p1AllPointsPrint() const;
	void p2AllPointsPrint() const;
};


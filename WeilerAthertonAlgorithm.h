#pragma once

#include <vector>
#include <map>
#include "Prism.h"

class WeilerAthertonAlgorithm
{
private:
	Prism p1, p2;
	vector<Vertex> p1Vertices, p2Vertices;
	vector<Vertex> p1AllPoints, p2AllPoints;
	vector<Prism> firstParts, intersectionParts, secondParts;
	
	void generateAllPoints();
	void sortPoints(int, multimap<int, Vertex>);
	bool checkIfInside();
public:
	WeilerAthertonAlgorithm(const Prism&, const Prism&);
	~WeilerAthertonAlgorithm();

	void doAlgo();

	vector<Prism> getFirstParts();
	vector<Prism> getSecondParts();
	vector<Prism> getIntersectionParts();
	vector<Prism> returnResult();

	void p1AllPointsPrint() const;
	void p2AllPointsPrint() const;
};


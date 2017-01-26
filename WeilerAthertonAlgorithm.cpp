#include "WeilerAthertonAlgorithm.h"


WeilerAthertonAlgorithm::WeilerAthertonAlgorithm(const Prism& other1, const Prism& other2)
{
	p1 = other1;
	p2 = other2;
	for (Vertex v : other1.getBase().getVerticesList())
		p1Vertices.push_back(v);
	for (Vertex v : other2.getBase().getVerticesList())
		p2Vertices.push_back(v);
}

void WeilerAthertonAlgorithm::generateAllPoints()
{
	multimap<int, Vertex> p1IntersectionPoints, p2IntersectionPoints;
	int p1Prev = p1Vertices.size() - 1;
	for (int i = 0; i < p1Vertices.size(); ++i)
	{
		int p1Next1 = (i + 1) % p1Vertices.size();
		int p1Next2 = (i + 2) % p1Vertices.size();
		LineSegment firstLine(p1Vertices[i], p1Vertices[p1Next1]);

		int p2Prev = p2Vertices.size() - 1;
		for (int j = 0; j < p2Vertices.size(); ++j)
		{
			int p2Next1 = (j + 1) % p2Vertices.size();
			int p2Next2 = (j + 2) % p2Vertices.size();
			LineSegment secondLine(p2Vertices[j], p2Vertices[p2Next1]);
			if (firstLine.doIntersect(secondLine))
			{
				pair<bool, Vertex> intersectionPoint = firstLine.getIntersectionPoint(secondLine);
				// if intersection point exists - without colinear cases
				if (intersectionPoint.first)
				{
					if (intersectionPoint.second == firstLine.getV1())
					{
						//cout << "1" << endl;
						// to avoid situation when we have two line segment on one side
						if (LineSegment::getOrientation(secondLine.getV1(), secondLine.getV2(), p1Vertices[p1Prev])
							!= LineSegment::getOrientation(secondLine.getV1(), secondLine.getV2(), p1Vertices[p1Next1])
							&& LineSegment::getOrientation(secondLine.getV1(), secondLine.getV2(), p1Vertices[p1Prev]) != 0)
						{
							if (!(intersectionPoint.second == secondLine.getV1()) &&
								!(intersectionPoint.second == secondLine.getV2()))
							{
								//cout << i << " " << j << " " << intersectionPoint.second.getX() << " " << intersectionPoint.second.getY() << endl;
								//cout << "1poWarunku" << endl;
								p1Vertices[i].setIntersectionPoint(true);
								p2IntersectionPoints.insert(pair<int, Vertex>(j, intersectionPoint.second));
							}
							else
							{
								if (intersectionPoint.second == secondLine.getV1() && !p1.getBase().isInside(secondLine.getV2()))
								{
									//cout << "1a" << endl;
									//cout << i << " " << j << " " << intersectionPoint.second.getX() << " " << intersectionPoint.second.getY() << endl;
									//cout << "1poWarunku" << endl;

									if (!((p2Vertices[p2Prev].getX() > p1.getBase().getXMax() && p2Vertices[p2Next1].getX() > p1.getBase().getXMax())
										|| (p2Vertices[p2Prev].getX() < p1.getBase().getXMin() && p2Vertices[p2Next1].getX() < p1.getBase().getXMin())
										|| (p2Vertices[p2Prev].getY() > p1.getBase().getYMax() && p2Vertices[p2Next1].getY() > p1.getBase().getYMax())
										|| (p2Vertices[p2Prev].getY() < p1.getBase().getYMin() && p2Vertices[p2Next1].getY() < p1.getBase().getYMin())))
									{
										p1Vertices[i].setIntersectionPoint(true);
										p2IntersectionPoints.insert(pair<int, Vertex>(j, intersectionPoint.second));
									}
								}
								else if (intersectionPoint.second == secondLine.getV2() && !p1.getBase().isInside(p2Vertices[p2Next2]))
								{
									//cout << "1b" << endl;
									//cout << i << " " << j << " " << intersectionPoint.second.getX() << " " << intersectionPoint.second.getY() << endl;
									//cout << "1poWarunku" << endl;
									if (!((p2Vertices[j].getX() > p1.getBase().getXMax() && p2Vertices[p2Next2].getX() > p1.getBase().getXMax())
										|| (p2Vertices[j].getX() < p1.getBase().getXMin() && p2Vertices[p2Next2].getX() < p1.getBase().getXMin())
										|| (p2Vertices[j].getY() > p1.getBase().getYMax() && p2Vertices[p2Next2].getY() > p1.getBase().getYMax())
										|| (p2Vertices[j].getY() < p1.getBase().getYMin() && p2Vertices[p2Next2].getY() < p1.getBase().getYMin())))
									{
										p1Vertices[i].setIntersectionPoint(true);
										p2IntersectionPoints.insert(pair<int, Vertex>(j, intersectionPoint.second));
									}
								}
							}
						}
					}
					else if (intersectionPoint.second == firstLine.getV2())
					{
						//cout << "2" << endl;+

						if (LineSegment::getOrientation(secondLine.getV1(), secondLine.getV2(), p1Vertices[i])
							!= LineSegment::getOrientation(secondLine.getV1(), secondLine.getV2(), p1Vertices[p1Next2])
							&& LineSegment::getOrientation(secondLine.getV1(), secondLine.getV2(), p1Vertices[p1Next2]) != 0)
						{
							if (!(intersectionPoint.second == secondLine.getV1()) &&
								!(intersectionPoint.second == secondLine.getV2()))
							{
								//cout << i << " " << j << " " << intersectionPoint.second.getX() << " " << intersectionPoint.second.getY() << endl;
								//cout << "2poWarunku" << endl;
								p1Vertices[p1Next1].setIntersectionPoint(true);
								p2IntersectionPoints.insert(pair<int, Vertex>(j, intersectionPoint.second));
							}
							else
							{
								if (intersectionPoint.second == secondLine.getV1() && !p1.getBase().isInside(secondLine.getV2()))
								{
									//cout << "2a" << endl;
									//cout << i << " " << j << " " << intersectionPoint.second.getX() << " " << intersectionPoint.second.getY() << endl;
									//cout << "1poWarunku" << endl;
									if (!((p2Vertices[p2Prev].getX() > p1.getBase().getXMax() && p2Vertices[p2Next1].getX() > p1.getBase().getXMax())
										|| (p2Vertices[p2Prev].getX() < p1.getBase().getXMin() && p2Vertices[p2Next1].getX() < p1.getBase().getXMin())
										|| (p2Vertices[p2Prev].getY() > p1.getBase().getYMax() && p2Vertices[p2Next1].getY() > p1.getBase().getYMax())
										|| (p2Vertices[p2Prev].getY() < p1.getBase().getYMin() && p2Vertices[p2Next1].getY() < p1.getBase().getYMin())))
									{
										p1Vertices[p1Next1].setIntersectionPoint(true);
										p2IntersectionPoints.insert(pair<int, Vertex>(j, intersectionPoint.second));
									}
								}
								else if (intersectionPoint.second == secondLine.getV2() && !p1.getBase().isInside(p2Vertices[p2Next2]))
								{
									//cout << "2b" << endl;
									//cout << i << " " << j << " " << intersectionPoint.second.getX() << " " << intersectionPoint.second.getY() << endl;
									//cout << "1poWarunku" << endl;
									if (!((p2Vertices[j].getX() > p1.getBase().getXMax() && p2Vertices[p2Next2].getX() > p1.getBase().getXMax())
										|| (p2Vertices[j].getX() < p1.getBase().getXMin() && p2Vertices[p2Next2].getX() < p1.getBase().getXMin())
										|| (p2Vertices[j].getY() > p1.getBase().getYMax() && p2Vertices[p2Next2].getY() > p1.getBase().getYMax())
										|| (p2Vertices[j].getY() < p1.getBase().getYMin() && p2Vertices[p2Next2].getY() < p1.getBase().getYMin())))
									{
										p1Vertices[p1Next1].setIntersectionPoint(true);
										p2IntersectionPoints.insert(pair<int, Vertex>(j, intersectionPoint.second));
									}
								}
							}
						}
					}
					else if (intersectionPoint.second == secondLine.getV1())
					{
						//cout << "3" << endl;
						if (LineSegment::getOrientation(firstLine.getV1(), firstLine.getV2(), p2Vertices[p2Prev])
							!= LineSegment::getOrientation(firstLine.getV1(), firstLine.getV2(), p2Vertices[p2Next1])
							&& LineSegment::getOrientation(firstLine.getV1(), firstLine.getV2(), p2Vertices[p2Prev]) != 0)
						{
							if (!(intersectionPoint.second == firstLine.getV1()) &&
								!(intersectionPoint.second == firstLine.getV2()))
							{
								//cout << "3poWarunku" << endl;
								p2Vertices[j].setIntersectionPoint(true);
								p1IntersectionPoints.insert(pair<int, Vertex>(i, intersectionPoint.second));
							}
						}
					}
					else if (intersectionPoint.second == secondLine.getV2())
					{
						//cout << "4" << endl;
						if (LineSegment::getOrientation(firstLine.getV1(), firstLine.getV2(), p2Vertices[j])
							!= LineSegment::getOrientation(firstLine.getV1(), firstLine.getV2(), p2Vertices[p2Next2])
							&& LineSegment::getOrientation(firstLine.getV1(), firstLine.getV2(), p2Vertices[p2Next2]) != 0)
						{
							if (!(intersectionPoint.second == firstLine.getV1()) &&
								!(intersectionPoint.second == firstLine.getV2()))
							{
								//cout << "4poWarunku" << endl;
								p2Vertices[p2Next1].setIntersectionPoint(true);
								p1IntersectionPoints.insert(pair<int, Vertex>(i, intersectionPoint.second));
							}
						}
					}
					else
					{
						//cout << "5" << endl;
						p1IntersectionPoints.insert(pair<int, Vertex>(i, intersectionPoint.second));
						p2IntersectionPoints.insert(pair<int, Vertex>(j, intersectionPoint.second));
					}
				}
			}
			p2Prev = j;
		}
		p1Prev = i;
	}
	cout << endl << endl;
	sortPoints(0, p1IntersectionPoints);
	sortPoints(1, p2IntersectionPoints);
}

void WeilerAthertonAlgorithm::sortPoints(int polygonNumber, multimap<int, Vertex> intersectionPoints)
{
	vector<Vertex> tempVertexVector;
	if (polygonNumber == 0)
	{
		for (int i = 0; i < p1Vertices.size(); ++i)
		{
			p1AllPoints.push_back(p1Vertices[i]);
			for (multimap<int, Vertex>::iterator iter = intersectionPoints.begin(); iter != intersectionPoints.end(); ++iter)
			{
				if (iter->first == i)
				{
					Vertex v = iter->second;
					if (v == p1Vertices[i])
					{
						p1Vertices[i].setIntersectionPoint(true);
						p1AllPoints.back().setIntersectionPoint(true);
					}
					else if (v == p1Vertices[(i + 1) % p1Vertices.size()])
					{
						p1Vertices[(i + 1) % p1Vertices.size()].setIntersectionPoint(true);
						if ((i + 1) % p1Vertices.size() == 0)
							p1AllPoints[0].setIntersectionPoint(true);
					}
					else
						tempVertexVector.push_back(v);
				}
			}
			sort(tempVertexVector.begin(), tempVertexVector.end(), DistanceFunc(p1Vertices[i]));
			for (Vertex v : tempVertexVector)
				p1AllPoints.push_back(v);
			tempVertexVector.clear();
		}
	}
	else
	{
		for (int i = 0; i < p2Vertices.size(); ++i)
		{
			p2AllPoints.push_back(p2Vertices[i]);
			for (multimap<int, Vertex>::iterator iter = intersectionPoints.begin(); iter != intersectionPoints.end(); ++iter)
			{
				if (iter->first == i)
				{
					//cout << i << " " << iter->second.getX() << " " << iter->second.getY() << endl;
					Vertex v = iter->second;
					if (v == p2Vertices[i])
					{
						p2Vertices[i].setIntersectionPoint(true);
						p2AllPoints.back().setIntersectionPoint(true);
					}
					else if (v == p2Vertices[(i + 1) % p2Vertices.size()])
					{
						p2Vertices[(i + 1) % p2Vertices.size()].setIntersectionPoint(true);
						if ((i + 1) % p2Vertices.size() == 0)
							p2AllPoints[0].setIntersectionPoint(true);
					}
					else
						tempVertexVector.push_back(v);
				}
			}
			sort(tempVertexVector.begin(), tempVertexVector.end(), DistanceFunc(p2Vertices[i]));
			for (Vertex v : tempVertexVector)
				p2AllPoints.push_back(v);
			tempVertexVector.clear();
		}
	}
}

void WeilerAthertonAlgorithm::doAlgo()
{
	generateAllPoints();

	if (p1AllPoints.size() == p1Vertices.size() && p2AllPoints.size() == p2Vertices.size())
	{
		if (checkIfInside())
			cout << "no elo" << endl;
	}
}

bool WeilerAthertonAlgorithm::checkIfInside()
{
	if (p1.getBase().isInside(p2Vertices[0]))
	{

	}
	else if (p2.getBase().isInside(p1Vertices[0]))
	{

	}
	return true;
}

void WeilerAthertonAlgorithm::p1AllPointsPrint() const
{
	for (Vertex v : p1AllPoints)
		cout << v.toString() << " ";
	cout << endl;
}

void WeilerAthertonAlgorithm::p2AllPointsPrint() const
{
	for (Vertex v : p2AllPoints)
		cout << v.toString() << " ";
	cout << endl;
}

vector<Prism> WeilerAthertonAlgorithm::getFirstParts() 
{
	return firstParts;
}

vector<Prism> WeilerAthertonAlgorithm::getSecondParts() 
{
	return secondParts;
}

vector<Prism> WeilerAthertonAlgorithm::getIntersectionParts() 
{
	return intersectionParts;
}

vector<Prism> WeilerAthertonAlgorithm::returnResult() 
{
	vector<Prism> result;
	for (Prism p : firstParts)
		result.push_back(p);
	for (Prism p : intersectionParts)
		result.push_back(p);
	for (Prism p : secondParts)
		result.push_back(p);
	return result;
}


WeilerAthertonAlgorithm::~WeilerAthertonAlgorithm()
{
}

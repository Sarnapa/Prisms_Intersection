/*
	Micha³ Piotrak
	numer albumu: 269336
	Przeciêcie graniastos³upów
*/

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
						// to avoid situation when we have two line segment on one side
						if (LineSegment::getOrientation(secondLine.getV1(), secondLine.getV2(), p1Vertices[p1Prev])
							!= LineSegment::getOrientation(secondLine.getV1(), secondLine.getV2(), p1Vertices[p1Next1])
							&& LineSegment::getOrientation(secondLine.getV1(), secondLine.getV2(), p1Vertices[p1Prev]) != 0)
						{
							if (!(intersectionPoint.second == secondLine.getV1()) &&
								!(intersectionPoint.second == secondLine.getV2()))
							{
								p1Vertices[i].setIntersectionPoint(true);
								p2IntersectionPoints.insert(pair<int, Vertex>(j, intersectionPoint.second));
							}
							else
							{
								if (intersectionPoint.second == secondLine.getV1() && !p1.getBase().isInside(secondLine.getV2()))
								{
									// cases when only intersection part is one vertex
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
						if (LineSegment::getOrientation(secondLine.getV1(), secondLine.getV2(), p1Vertices[i])
							!= LineSegment::getOrientation(secondLine.getV1(), secondLine.getV2(), p1Vertices[p1Next2])
							&& LineSegment::getOrientation(secondLine.getV1(), secondLine.getV2(), p1Vertices[p1Next2]) != 0)
						{
							if (!(intersectionPoint.second == secondLine.getV1()) &&
								!(intersectionPoint.second == secondLine.getV2()))
							{
								p1Vertices[p1Next1].setIntersectionPoint(true);
								p2IntersectionPoints.insert(pair<int, Vertex>(j, intersectionPoint.second));
							}
							else
							{
								if (intersectionPoint.second == secondLine.getV1() && !p1.getBase().isInside(secondLine.getV2()))
								{
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
						if (LineSegment::getOrientation(firstLine.getV1(), firstLine.getV2(), p2Vertices[p2Prev])
							!= LineSegment::getOrientation(firstLine.getV1(), firstLine.getV2(), p2Vertices[p2Next1])
							&& LineSegment::getOrientation(firstLine.getV1(), firstLine.getV2(), p2Vertices[p2Prev]) != 0)
						{
							if (!(intersectionPoint.second == firstLine.getV1()) &&
								!(intersectionPoint.second == firstLine.getV2()))
							{
								p2Vertices[j].setIntersectionPoint(true);
								p1IntersectionPoints.insert(pair<int, Vertex>(i, intersectionPoint.second));
							}
						}
					}
					else if (intersectionPoint.second == secondLine.getV2())
					{
						if (LineSegment::getOrientation(firstLine.getV1(), firstLine.getV2(), p2Vertices[j])
							!= LineSegment::getOrientation(firstLine.getV1(), firstLine.getV2(), p2Vertices[p2Next2])
							&& LineSegment::getOrientation(firstLine.getV1(), firstLine.getV2(), p2Vertices[p2Next2]) != 0)
						{
							if (!(intersectionPoint.second == firstLine.getV1()) &&
								!(intersectionPoint.second == firstLine.getV2()))
							{
								p2Vertices[p2Next1].setIntersectionPoint(true);
								p1IntersectionPoints.insert(pair<int, Vertex>(i, intersectionPoint.second));
							}
						}
					}
					else
					{
						p1IntersectionPoints.insert(pair<int, Vertex>(i, intersectionPoint.second));
						p2IntersectionPoints.insert(pair<int, Vertex>(j, intersectionPoint.second));
					}
				}
			}
			p2Prev = j;
		}
		p1Prev = i;
	}
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

int WeilerAthertonAlgorithm::getStartPoint()
{
	int posVertex = 0;
	for (int i = 0; i < p1AllPoints.size(); ++i)
	{
		int iNext = (i + 1) % p1AllPoints.size();
		// second point can be next intersection Point or point that is inside of second polygon
		if (p1AllPoints[i].getIsIntersectionPoint() && !p1AllPoints[i].getVisited() && (p1AllPoints[iNext].getIsIntersectionPoint() ||
			p2.getBase().isInside(p1AllPoints[iNext])))
		{
			posVertex = i;
			break;
		}
	}
	return posVertex;
}

int WeilerAthertonAlgorithm::getNext(int polygonNumber, Vertex v)
{
	if (polygonNumber == 0)
	{
		for (int i = 0; i < p1AllPoints.size(); ++i)
		{
			if (p1AllPoints[i] == v)
			{
				return (i + 1) % p1AllPoints.size();
				break;
			}
		}
	}
	else
	{
		for (int i = 0; i < p2AllPoints.size(); ++i)
		{
			if (p2AllPoints[i] == v)
			{
				return (i + 1) % p2AllPoints.size();
				break;
			}
		}
	}
}

int WeilerAthertonAlgorithm::getFromOtherPolygon(int polygonNumber, Vertex v)
{
	if (polygonNumber == 0)
	{
		for (int i = 0; i < p2AllPoints.size(); ++i)
		{
			if (p2AllPoints[i] == v)
			{
				return i;
				break;
			}
		}
	}
	else
	{
		for (int i = 0; i < p1AllPoints.size(); ++i)
		{
			if (p1AllPoints[i] == v)
			{
				return i;
				break;
			}
		}
	}
}

int WeilerAthertonAlgorithm::countIntersectionPointsNumber()
{
	int number = 0;
	for (Vertex v : p1AllPoints)
	{
		if (v.getIsIntersectionPoint())
			++number;
	}
	return number;
}

void WeilerAthertonAlgorithm::doAlgo()
{
	if (checkIfTheSame())
		return;

	generateAllPoints();

	if (p1AllPoints.size() == p1Vertices.size() && p2AllPoints.size() == p2Vertices.size())
	{
		if (!checkIfInside())
		{
			inputParts.push_back(p1);
			inputParts.push_back(p2);
		}
		return;
	}

	int intersectionPointsNumber = countIntersectionPointsNumber();
	if (intersectionPointsNumber > 1)
	{
		inputParts.push_back(p1);
		inputParts.push_back(p2);
		bool allIntersectionPointsVisited = false;
		int polygonFlag = 0; // p1
		int intersectionCurrentNumber = 1; // because of startPoint
		int startIndex = getStartPoint();
		int currentIndex = startIndex;
		p1AllPoints[startIndex].setVisited(true);
		Vertex startPoint = p1AllPoints[startIndex];
		Vertex currentPoint = startPoint;
		vector<Vertex> tmpPoints;
		tmpPoints.push_back(startPoint);
		while (!allIntersectionPointsVisited)
		{
			if (polygonFlag == 0)
			{
				currentIndex = getNext(0, currentPoint);
				p1AllPoints[currentIndex].setVisited(true);
				currentPoint = p1AllPoints[currentIndex];
				if (!(currentPoint == startPoint))
				{
					tmpPoints.push_back(currentPoint);

					if (currentPoint.getIsIntersectionPoint())
					{
						++intersectionCurrentNumber;
						currentIndex = getFromOtherPolygon(0, currentPoint);
						p2AllPoints[currentIndex].setVisited(true);
						currentPoint = p2AllPoints[currentIndex];
						polygonFlag = 1;
					}
				}
			}
			else
			{
				currentIndex = getNext(1, currentPoint);
				p2AllPoints[currentIndex].setVisited(true);
				currentPoint = p2AllPoints[currentIndex];
				if (!(currentPoint == startPoint))
				{
					tmpPoints.push_back(currentPoint);

					if (currentPoint.getIsIntersectionPoint())
					{
						++intersectionCurrentNumber;
						currentIndex = getFromOtherPolygon(1, currentPoint);
						p1AllPoints[currentIndex].setVisited(true);
						currentPoint = p1AllPoints[currentIndex];
						polygonFlag = 0;
					}
				}
			}
			if (currentPoint == startPoint)
			{
				Prism p3 = Prism(p1.getId() + p2.getId(), Polygon(tmpPoints));
				p3.addHeightRanges(p1.getHeightRanges());
				p3.addHeightRanges(p2.getHeightRanges());
				intersectionParts.push_back(p3);
				if (intersectionCurrentNumber == intersectionPointsNumber)
					allIntersectionPointsVisited = true;
				else
				{
					startIndex = getStartPoint();
					p1AllPoints[startIndex].setVisited(true);
					startPoint = p1AllPoints[startIndex];
					currentPoint = startPoint;
					tmpPoints.clear();
					tmpPoints.push_back(startPoint);
				}
			}
		}
	}
}

bool WeilerAthertonAlgorithm::checkIfTheSame()
{
	if (p1.getBase() == p2.getBase())
	{
		p1.addHeightRanges(p2.getHeightRanges());
		inputParts.push_back(p1);
		return true;
	}
	return false;
}

bool WeilerAthertonAlgorithm::checkIfInside()
{
	bool isOutside1 = false;
	bool isOutside2 = false;
	
	// it is necessary to do that because of cases when polygons share sides
	for (Vertex v : p2Vertices)
	{
		if (!p1.getBase().isInside(v))
		{
			isOutside1 = true;
			break;
		}
	}
	for (Vertex v : p1Vertices)
	{
		if (!p2.getBase().isInside(v))
		{
			isOutside2 = true;
			break;
		}
	}


	if (!isOutside1)
	{
		Prism p3 = p2;
		p3.addHeightRanges(p1.getHeightRanges());
		intersectionParts.push_back(p3);
		inputParts.push_back(p1);
		return true;
	}
	else if (!isOutside2)
	{
		Prism p3 = p1;
		p3.addHeightRanges(p2.getHeightRanges());
		intersectionParts.push_back(p3);
		inputParts.push_back(p2);
		return true;
	}
	return false;
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

vector<Prism> WeilerAthertonAlgorithm::returnInputParts()
{
	return inputParts;
}

vector<Prism> WeilerAthertonAlgorithm::returnIntersectionParts()
{
	return intersectionParts;
}

vector<Prism> WeilerAthertonAlgorithm::returnResult() 
{
	for (Prism p : inputParts)
		results.push_back(p);
	for (Prism p : intersectionParts)
		results.push_back(p);
	return results;
}


WeilerAthertonAlgorithm::~WeilerAthertonAlgorithm()
{
}

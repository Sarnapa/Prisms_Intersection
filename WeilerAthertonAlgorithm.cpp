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
							!= LineSegment::getOrientation(secondLine.getV1(), secondLine.getV2(), p1Vertices[p1Next1]))
							//&& LineSegment::getOrientation(secondLine.getV1(), secondLine.getV2(), p1Vertices[p1Prev]) != 0
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
									double x1 = p2Vertices[p2Prev].getX();
									double y1 = p2Vertices[p2Prev].getY();
									double x2 = p2Vertices[p2Next1].getX();
									double y2 = p2Vertices[p2Next1].getY();
									// cases when only intersection part is one vertex
									if (!((x1 - EPSILON > p1.getBase().getXMax() && x2 - EPSILON > p1.getBase().getXMax())
										|| (x1 + EPSILON < p1.getBase().getXMin() && x2 + EPSILON < p1.getBase().getXMin())
										|| (y1 - EPSILON > p1.getBase().getYMax() && y2 - EPSILON > p1.getBase().getYMax())
										|| (y1 + EPSILON < p1.getBase().getYMin() && y2 + EPSILON < p1.getBase().getYMin())))
									{
										p1Vertices[i].setIntersectionPoint(true);
										p2IntersectionPoints.insert(pair<int, Vertex>(j, intersectionPoint.second));
									}
								}
								else if (intersectionPoint.second == secondLine.getV2() && !p1.getBase().isInside(p2Vertices[p2Next2]))
								{
									double x1 = p2Vertices[j].getX();
									double y1 = p2Vertices[j].getY();
									double x2 = p2Vertices[p2Next2].getX();
									double y2 = p2Vertices[p2Next2].getY();
									if (!((x1 - EPSILON > p1.getBase().getXMax() && x2 - EPSILON > p1.getBase().getXMax())
										|| (x1 + EPSILON < p1.getBase().getXMin() && x2 + EPSILON < p1.getBase().getXMin())
										|| (y1 - EPSILON > p1.getBase().getYMax() && y2 - EPSILON > p1.getBase().getYMax())
										|| (y1 + EPSILON < p1.getBase().getYMin() && y2 + EPSILON < p1.getBase().getYMin())))
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
							!= LineSegment::getOrientation(secondLine.getV1(), secondLine.getV2(), p1Vertices[p1Next2]))
							//&& LineSegment::getOrientation(secondLine.getV1(), secondLine.getV2(), p1Vertices[p1Next2]) != 0)
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
									double x1 = p2Vertices[p2Prev].getX();
									double y1 = p2Vertices[p2Prev].getY();
									double x2 = p2Vertices[p2Next1].getX();
									double y2 = p2Vertices[p2Next1].getY();
									if (!((x1 - EPSILON > p1.getBase().getXMax() && x2 - EPSILON > p1.getBase().getXMax())
										|| (x1 + EPSILON < p1.getBase().getXMin() && x2 + EPSILON < p1.getBase().getXMin())
										|| (y1 - EPSILON > p1.getBase().getYMax() && y2 - EPSILON > p1.getBase().getYMax())
										|| (y1 + EPSILON < p1.getBase().getYMin() && y2 + EPSILON < p1.getBase().getYMin())))
									{
										p1Vertices[p1Next1].setIntersectionPoint(true);
										p2IntersectionPoints.insert(pair<int, Vertex>(j, intersectionPoint.second));
									}
								}
								else if (intersectionPoint.second == secondLine.getV2() && !p1.getBase().isInside(p2Vertices[p2Next2]))
								{
									double x1 = p2Vertices[j].getX();
									double y1 = p2Vertices[j].getY();
									double x2 = p2Vertices[p2Next2].getX();
									double y2 = p2Vertices[p2Next2].getY();
									if (!((x1 - EPSILON > p1.getBase().getXMax() && x2 - EPSILON > p1.getBase().getXMax())
										|| (x1 + EPSILON < p1.getBase().getXMin() && x2 + EPSILON < p1.getBase().getXMin())
										|| (y1 - EPSILON > p1.getBase().getYMax() && y2 - EPSILON > p1.getBase().getYMax())
										|| (y1 + EPSILON < p1.getBase().getYMin() && y2 + EPSILON < p1.getBase().getYMin())))
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
							!= LineSegment::getOrientation(firstLine.getV1(), firstLine.getV2(), p2Vertices[p2Next1]))
							//&& LineSegment::getOrientation(firstLine.getV1(), firstLine.getV2(), p2Vertices[p2Prev]) != 0)
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
							!= LineSegment::getOrientation(firstLine.getV1(), firstLine.getV2(), p2Vertices[p2Next2]))
							//&& LineSegment::getOrientation(firstLine.getV1(), firstLine.getV2(), p2Vertices[p2Next2]) != 0)
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
					{
						if (tempVertexVector.size() != 0)
						{
							if (!(v == tempVertexVector.back()) && !(v == tempVertexVector.front()))
								tempVertexVector.push_back(v);
						}
						else
							tempVertexVector.push_back(v);
					}
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
					{
						if (tempVertexVector.size() != 0)
						{
							if (!(v == tempVertexVector.back()) && !(v == tempVertexVector.front()))
								tempVertexVector.push_back(v);
						}
						else
							tempVertexVector.push_back(v);
					}
				}
			}
			sort(tempVertexVector.begin(), tempVertexVector.end(), DistanceFunc(p2Vertices[i]));
			for (Vertex v : tempVertexVector)
			{
				p2AllPoints.push_back(v);
			}
			tempVertexVector.clear();
		}
	}
}

pair<int, int> WeilerAthertonAlgorithm::getStartPoint()
{
	int posVertex;
	for (int i = 0; i < p1AllPoints.size(); ++i)
	{
		int iNext = (i + 1) % p1AllPoints.size();
		// second point can be next intersection Point or point that is inside of second polygon (but intersection point have greater priority)
		if (p1AllPoints[i].getIsIntersectionPoint() && !p1AllPoints[i].getVisited() && p1AllPoints[iNext].getIsIntersectionPoint())
		{
			posVertex = i;
			return make_pair(0, posVertex);
		}
	}
	for (int i = 0; i < p2AllPoints.size(); ++i)
	{
		int iNext = (i + 1) % p2AllPoints.size();
		if (p2AllPoints[i].getIsIntersectionPoint() && !p2AllPoints[i].getVisited() && p2AllPoints[iNext].getIsIntersectionPoint())
		{
			posVertex = i;
			return make_pair(1, posVertex);
		}
	}
	for (int i = 0; i < p1AllPoints.size(); ++i)
	{
		int iNext = (i + 1) % p1AllPoints.size();
		if (p1AllPoints[i].getIsIntersectionPoint() && !p1AllPoints[i].getVisited() && p2.getBase().isInside(p1AllPoints[iNext]))
		{
			posVertex = i;
			return make_pair(0, posVertex);
		}
	}
	for (int i = 0; i < p2AllPoints.size(); ++i)
	{
		int iNext = (i + 1) % p2AllPoints.size();
		if (p2AllPoints[i].getIsIntersectionPoint() && !p2AllPoints[i].getVisited() && p1.getBase().isInside(p2AllPoints[iNext]))
		{
			posVertex = i;
			return make_pair(1, posVertex);
		}
	}
	posVertex = -1; // fault
	return make_pair(0, posVertex);
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
	if (!(p1.getBase().checkMinMax(p2.getBase())))
	{
		inputParts.push_back(p1);
		inputParts.push_back(p2);
		return;
	}

	if (checkIfTheSame())
		return;

	if (checkIfInside())
		return;

	generateAllPoints();

	/*cout << "=========" << endl;
	p1.printPrism();
	cout << endl;
	p1AllPointsPrint();
	cout << endl;
	p2.printPrism();
	cout << endl;
	p2AllPointsPrint();
	cout << "=========" << endl;*/

	inputParts.push_back(p1);
	inputParts.push_back(p2);
	int intersectionPointsNumber = countIntersectionPointsNumber();
	if (intersectionPointsNumber > 1)
	{
		int prevIndex, currentIndex, startIndex;
		Vertex prevPoint, startPoint, currentPoint;
		bool allIntersectionPointsVisited = false;
		bool first = true;
		pair<int, int> point = getStartPoint();
		int polygonFlag = point.first;
		int intersectionCurrentNumber = 1; // because of startPoint
		startIndex = point.second;
		if (startIndex == -1)
		{
			cout << "Warning for detection of intersection for prisms: " << endl;
			//p1.printPrism();
			//p2.printPrism();
			p1AllPointsPrint();
			cout << endl;
			p2AllPointsPrint();
		}
		else
		{
			currentIndex = startIndex;
			if (polygonFlag == 0)
			{
				p1AllPoints[startIndex].setVisited(true);
				startPoint = p1AllPoints[startIndex];
			}
			else
			{
				p2AllPoints[startIndex].setVisited(true);
				startPoint = p2AllPoints[startIndex];
			}
			currentPoint = startPoint;
			prevPoint = currentPoint;
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
							// if colinear
							if (LineSegment::getOrientation(prevPoint, currentPoint, p1AllPoints[getNext(0, currentPoint)]) == 0
								&& !first)
							{
								polygonFlag = 1;
								currentIndex = getFromOtherPolygon(0, currentPoint);
								p2AllPoints[currentIndex].setVisited(true);
								currentPoint = p2AllPoints[currentIndex];
								if (currentIndex == 0)
									prevIndex = p2AllPoints.size() - 1;
								else
									prevIndex = currentIndex - 1;
								prevPoint = p2AllPoints[prevIndex];
							}
							else
							{
								first = false; // just in case
								polygonFlag = 1;
								currentIndex = getFromOtherPolygon(0, currentPoint);
								p2AllPoints[currentIndex].setVisited(true);
								currentPoint = p2AllPoints[currentIndex];
								if (currentIndex == 0)
									prevIndex = p2AllPoints.size() - 1;
								else
									prevIndex = currentIndex - 1;
								prevPoint = p2AllPoints[prevIndex];
							}
						}
						else
						{
							prevPoint = currentPoint;
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
							// if colinear
							if (LineSegment::getOrientation(prevPoint, currentPoint, p2AllPoints[getNext(1, currentPoint)]) == 0
								&& !first)
							{
								polygonFlag = 0;
								currentIndex = getFromOtherPolygon(1, currentPoint);
								p1AllPoints[currentIndex].setVisited(true);
								currentPoint = p1AllPoints[currentIndex];
								if (currentIndex == 0)
									prevIndex = p1AllPoints.size() - 1;
								else
									prevIndex = currentIndex - 1;
								prevPoint = p1AllPoints[prevIndex];
							}
							else
							{
								first = false;
								polygonFlag = 0;
								currentIndex = getFromOtherPolygon(1, currentPoint);
								p1AllPoints[currentIndex].setVisited(true);
								currentPoint = p1AllPoints[currentIndex];
								if (currentIndex == 0)
									prevIndex = p1AllPoints.size() - 1;
								else
									prevIndex = currentIndex - 1;
								prevPoint = p1AllPoints[prevIndex];
							}
						}
						else
						{
							prevPoint = currentPoint;
						}
					}
				}
				if (currentPoint == startPoint)
				{
					Prism p3;
					if (tmpPoints.size() > 2)
					{
						p3 = Prism(Polygon(tmpPoints));
						p3.addHeightRanges(p1.getHeightRanges());
						p3.addHeightRanges(p2.getHeightRanges());
						intersectionParts.push_back(p3);
					}
					if (intersectionCurrentNumber == intersectionPointsNumber)
						allIntersectionPointsVisited = true;
					else
					{
						first = true;
						pair<int, int> point = getStartPoint();
						polygonFlag = point.first;
						startIndex = point.second;
						currentIndex = startIndex;
						if (startIndex == -1)
						{
							cout << "Warning for detection of intersection for prisms: " << endl;
							p1.printPrism();
							cout << endl;
							p1AllPointsPrint();
							cout << endl;
							p2.printPrism();
							cout << endl;
							p2AllPointsPrint();
							cout << endl;
							cout << "Please check prism: " << endl;
							p3.printPrism();
							intersectionParts.pop_back();
							break;
						}
						if (polygonFlag == 0)
						{
							p1AllPoints[startIndex].setVisited(true);
							startPoint = p1AllPoints[startIndex];
						}
						else
						{
							p2AllPoints[startIndex].setVisited(true);
							startPoint = p2AllPoints[startIndex];
						}
						currentPoint = startPoint;
						prevPoint = currentPoint;
						++intersectionCurrentNumber;
						tmpPoints.clear();
						tmpPoints.push_back(startPoint);
					}
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
	if (isOutside1)
	{
		for (Vertex v : p1Vertices)
		{
			if (!p2.getBase().isInside(v))
			{
				isOutside2 = true;
				break;
			}
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

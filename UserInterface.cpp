#include "UserInterface.h"
#include "LineSegment.h"

using namespace std;

void UserInterface::printInfo()
{
    cout << "Welcome to PRISMS INTERSECTION PROGRAM" << endl;
    cout << "Details concerning data input format:" << endl;
    cout << "1. Each line in entry text file concerns one prism." << endl;
    cout << "2. Each line must have structure like this:" << endl;
    cout << "<prism_ID> <min z> <max z> <x1> <y1> <x2> <y2> <x3> <y3>..." << endl;
    cout << endl;
    cout << "Specified flags for the application:" << endl;
    cout << "\t-f <filename> - read input from text file" << endl;
    cout << "\t-g <filename> <number of prisms> <max number of vertices of base> <1 if only convex or 0 if every random polygon>" << endl;
    cout <<  "\t - generate random input and save it in file" << endl;
    cout << "\t-o <filename> - save output in file" << endl;
    cout << "\t-help - program help manual" << endl;
    cout << "\tIMPORTANT - flag -f and -g must be put before flag -o" << endl;
}

bool UserInterface::parseCommand(int argc, char **argv)
{
    string arg1 = string(argv[1]);
    if(arg1 == "-f" && argc >= 3)
    {
        if(argc > 5)
            return false;
        mode = FROM_FILE;
        inFile = string(argv[2]);
        if(argc == 5 && string(argv[3]) == "-o")
            outFile = string(argv[4]);
        return true;
    }

    else if (arg1 == "-g" && argc >= 6)
    {
        if(argc > 8)
            return false;
        mode = GENERATOR;
        genFile = string(argv[2]);
        prismsNumber = atoi(argv[3]);
        maxVerticesNumber = atoi(argv[4]);
		if (atoi(argv[5]) == 1)
		{
			onlyConvexForGenerator = true; // default option is false
		}
        if(argc == 8 && string(argv[6]) == "-o")
            outFile = string(argv[7]);
        return true;
    }
    return false;
}

bool UserInterface::loadFromFile()
{
    fstream inputData;
    inputData.open(inFile, ios::in);
    string line;
    if (inputData.good())
    {
		while (getline(inputData, line))
		{
			prismsList.push_back(generatePrism(line));
		}
		prismsNumber = prismsList.size();
        inputData.close();
    }
    else
    {
        inputData.close();
        return false;
    }
    return true;
}

// to parse row concerning one prism and create this prism
Prism UserInterface::generatePrism(string prismLine)
{
    int id;
    double minZ, maxZ, x, y;
    vector<Vertex> vertices;
    stringstream ss(prismLine);
    ss >> id;
    ss >> minZ;
    ss >> maxZ;
    while (!ss.eof())
    {
        ss >> x;
        ss >> y;
        vertices.push_back(Vertex(x,y));
    }
    Polygon base(vertices);
    return Prism(id, base, make_pair(x,y));
}

void UserInterface::usePrismsGenerator()
{
	PrismsGenerator generator(prismsNumber, maxVerticesNumber, onlyConvexForGenerator);
	prismsList = generator.generatePrisms();
}

bool UserInterface::saveToGenFile() const
{
	fstream file;
	file.open(genFile, ios::out);
	if (file.good())
	{
		for (Prism p : prismsList)
			file << p.toString();
		file.close();
	}
	else
	{
		file.close();
		return false;
	}
	return true;
}

bool UserInterface::saveToOutFile(int algo) const
{
	fstream file;
	file.open(outFile, ios::out);
	if (file.good())
	{
		if (algo == 0)
		{
			for (Prism p : weilerAthertonResult)
				file << p.toString();
		}
		file.close();
	}
	else
	{
		file.close();
		return false;
	}
	return true;
}

ProgramMode UserInterface::getMode() const
{
    return mode;
}

void UserInterface::drawInputPrisms() const
{
	DrawingPrisms prismsWindow(prismsList, prismsNumber);
	prismsWindow.drawPrisms("Prisms_Intersection - Input");
}

void UserInterface::drawWAPrisms() const
{
	DrawingPrisms prismsWindow(weilerAthertonResult, prismsNumber);
	prismsWindow.drawPrisms("Prisms_Intersection - Weiler - Atherton Algo result");
}

void UserInterface::printInputPrismsList() const
{
	for(unsigned int i = 0; i < prismsList.size(); ++i)
        prismsList[i].printPrism();
}

void UserInterface::printWAPrismsList() const
{
	cout << "Weiler - Atherton Algorithm result: " << endl << endl;
	for (unsigned int i = 0; i < weilerAthertonResult.size(); ++i)
		weilerAthertonResult[i].printPrism();
}

void UserInterface::doWeilerAthertonAlgo()
{
	for (int i = 0; i < prismsList.size() - 1; ++i) 
	{
		for (int j = i + 1; j < prismsList.size(); ++j)
		{
			WeilerAthertonAlgorithm wa(prismsList[i], prismsList[j]);
			wa.doAlgo();
			wa.firstAllPointsPrint();
			cout << endl;
			wa.secondAllPointsPrint();
			for (Prism p : wa.returnResult())
			{
				weilerAthertonResult.push_back(p);
			}
		}
	}
}


void UserInterface::printInterface() const
{
    cout << "Input File: " << inFile << endl;
    cout << "File created by generator: " << genFile << endl;
    cout << "Output File: " << outFile << endl;
    cout << "Prisms Number: " << prismsNumber << endl;
    cout << "Max Vertices Number in base: " << maxVerticesNumber << endl;
    cout << "Input Prisms List" << endl;
    printInputPrismsList();
}

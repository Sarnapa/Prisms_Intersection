#include "UserInterface.h"

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
    cout << "\t-g <filename> <number of prisms> <max number of vertices of base>" << endl;
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

    else if (arg1 == "-g" && argc >= 5)
    {
        if(argc > 7)
            return false;
        mode = GENERATOR;
        genFile = string(argv[2]);
        prismsNumber = atoi(argv[3]);
        maxVerticesNumber = atoi(argv[4]);
        if(argc == 7 && string(argv[5]) == "-o")
            outFile = string(argv[6]);
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
            prismsList.push_back(generatePrism(line));
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

ProgramMode UserInterface::getMode() const
{
    return mode;
}

void UserInterface::key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, GL_TRUE);
}

void UserInterface::printPrismsList() const
{
    for(unsigned int i = 0; i < prismsList.size(); ++i)
    {
        prismsList[i].printPrism();
    }
}

void UserInterface::printInterface() const
{
    cout << "Input File: " << inFile << endl;
    cout << "File created by generator: " << genFile << endl;
    cout << "Output File: " << outFile << endl;
    cout << "Prisms Number: " << prismsNumber << endl;
    cout << "Max Vertices Number in base: " << maxVerticesNumber << endl;
    cout << "Prisms List" << endl;
    printPrismsList();
}

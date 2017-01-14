#ifndef USERINTERFACE_H
#define USERINTERFACE_H

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "Prism.h"
#include "Polygon.h"
#include "PrismsGenerator.h"
#include "DrawingPrisms.h"

using namespace std;

enum ProgramMode
{
    FROM_FILE,
    GENERATOR
};

class UserInterface
{
    private:
        string inFile;
        string genFile;
        string outFile;
        ProgramMode mode;
        vector<Prism> prismsList;
        int prismsNumber = 0;
        int maxVerticesNumber = 0; // in base
		bool onlyConvexForGenerator = false;

		static Prism generatePrism(string); // from line from file
    public:
        static void printInfo();
        bool parseCommand(int, char **);
        bool loadFromFile();
		bool saveToGenFile() const;
		void usePrismsGenerator();
        ProgramMode getMode() const;

		void drawPrisms() const;
		void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode);

        void printPrismsList() const;
        void printInterface() const;
};

#endif // USERINTERFACE_H

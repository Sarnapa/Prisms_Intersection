#include <iostream>

#include "UserInterface.h"

using namespace std;

int main(int argc, char *argv[])
{
    UserInterface::printInfo();
	string argv1;
	if (argv[1] != NULL)
    argv1 = string(argv[1]);
    if(argc == 1 || (argc >= 2 && !(argv1 == "-f" || argv1 == "-g")))
    {
        cout << "Manual Help" << endl;
        return 0;
    }
    UserInterface interface;
    if(!interface.parseCommand(argc, argv))
    {
        cout << "Incorrect parameters" << endl;
        return 0;
    }
    else
    {
        ProgramMode mode = interface.getMode();
        if(mode == FROM_FILE)
        {
            if(!interface.loadFromFile())
                cout << "Cannot load data from file" << endl;
        }
        else
        {
			interface.usePrismsGenerator();
			if (!interface.saveToGenFile())
				cout << "Cannot save generated data to file" << endl;
        }
        interface.printInterface();
		interface.drawPrisms();
    }

    return 0;
}

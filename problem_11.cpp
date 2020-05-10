#include "ConsoleHandler.h"

int main()
{
    ConsoleHandler console;
    string command;

    while (true)
    {
        getline(cin, command);
        string firstWord = command.substr(0, command.find(" "));
        //checkFunction(firstWord, command, hotel);
        //arrOfRooms.print();
        //hotel.printRooms();
        console.processCommand(firstWord, command);
    }

    return 0;
}
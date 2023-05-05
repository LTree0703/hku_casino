#include <iostream>
#include <string>
#include <fstream>
using namespace std;

void clear() // clear console output
{
    cout << "\x1B[2J\x1B[H";
}

void read_file(string filename, string &text) // read the file and store it in a string
{
    ifstream file(filename.c_str());
    string line;
    while (getline(file, line))
    {
        text += line + "\n";
    }
}
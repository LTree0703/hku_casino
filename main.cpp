#include <iostream>
#include <ctime>
#include <fstream>
#include <string>

#include "func.h"

using namespace std;

int main()
{
    clear();
    string menu;
    read_file("menu.txt", menu);
    while (1)
    {
        cout << menu;
        cin.get();
        clear();
    }
}

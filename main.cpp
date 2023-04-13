#include <iostream>
#include <ctime>
#include <fstream>
#include <string>

#include "func.h"

using namespace std;

int main()
{
    clear();
    string menu_txt;
    read_file("menu.txt", menu_txt);
    while (1)
    {
        cout << menu_txt;
        cin.get();
        clear();
    }
}

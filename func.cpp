#include <iostream>
using namespace std;

void clear() // clear console output
{
    cout << "\x1B[2J\x1B[H";
}
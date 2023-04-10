#include <iostream>
#include <ctime>
using namespace std;

// Functions are declared here
void clear();


int main()
{
    printf("hello, world");
    clear();
}

void clear()
{
    cout << "\x1B[2J\x1B[H";
}
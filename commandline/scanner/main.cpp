#include <iostream>

#include "scanner.h"

using namespace std;

int main()
{

    Scanner* scanner = new Scanner();
    if(!scanner->init())
        return 1;

    while(1)
    {
        cout << scanner->scan() << endl;
    }



    return 0;
}

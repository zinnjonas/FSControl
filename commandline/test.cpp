#include "Controler.h"

#include <iostream>

using namespace std;

int main()
{
    FSControler* fsControler = new FSControler();

    if( !fsControler->init())
        exit(1);

    fsControler->clear();
    string text;

    while(text.compare("quit") != 0)
    {
        text = "";
        cout << "Was soll ich darstellen = ";
        getline(cin, text);
        if( text.compare("time") == 0)
            fsControler->displayTime();
        else if(  text.compare("new line") == 0)
            fsControler->newLine();
        else if( text.compare("test") == 0)
        {
for( int i = 0; i < 120; i++)
    {
        fsControler->clear();
        fsControler->displayTime();
        sleep(1);
    }
        }
        else if(text.compare("set time") == 0)
        {
            fsControler->setTime();
            fsControler->displayTime();
        }
        else if( text.compare("clear") == 0)
        {
            fsControler->clear();
        }
        else
        {
            fsControler->writeMsg(text, 2);
        }
    }

    return 0;
}

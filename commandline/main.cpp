#include "Controler.h"
#include "fsDatabase.h"
#include "scanner.h"
#include "global.h"
#include "timer.h"

#include <iostream>

using namespace std;

//#include<windows.h>
/*
void uSleep(int waitTime){
__int64 time1 = 0, time2 = 0, freq = 0;

QueryPerformanceCounter((LARGE_INTEGER *)&time1);
QueryPerformanceFrequency((LARGE_INTEGER *)&freq);
do{
QueryPerformanceCounter((LARGE_INTEGER *)&time2);

//  }while((((time2-time1)*1.0)/sysFreq)<waitTime);
  }while( (time2-time1) <waitTime);
}
8*/
int main()
{

    fsDatabase* fsDB = new fsDatabase();
    FSControler* controller = new FSControler();
    Scanner* scanner = new Scanner(controller);
    Timer* timer = new Timer();
    if( !fsDB->open("resourcen/FSControl.db"))
    {
        cerr << "can't open database" << endl;
        return 1;
    }
    if( !scanner->init())
    {
        cerr << "can't read from scanner" << endl;
        return 2;
    }
    if( !controller->init())
    {
        cerr << "can't write to FSControl" << endl;
        return 3;
    }
    controller->clear();
    bool inUserMode = false;
    for( int i = 0;  i < 4; i++)
    {
        string temp = scanner->scan();
        cout << temp << endl;

        if(inUserMode)
            if( timer->isOver(60))
                inUserMode = false;

        if( inUserMode)
        {
            if( temp.compare("exit") == 0)
            {
                controller->clear();
                controller->writeMsg("            ^ ^",0);
                controller->writeMsg("GOOD BYE    O O", 1);
                controller->writeMsg("             o ", 2);
                controller->writeMsg("             v ", 3);
                inUserMode = false;
                for( int i = 0; i < 25 ; i++)
                {
                    if( i % 2 == 0)
                        controller->writeMsg("GOOD BYE    o O", 1);
                    else
                        controller->writeMsg("GOOD BYE    O O", 1);
//                    uSleep(400000);
                }
            }
            else if(temp.compare(0, 3, "01/") == 0)
            {
                controller->clear();
                controller->writeMsg("user mode", 1);
                inUserMode = true;
                timer->reset();
            }
        }
        else
        {
            if(temp.compare(0, 3, "01/") == 0)
            {
                controller->clear();
                controller->writeMsg("user mode", 1);
                inUserMode = true;
                timer->start();
            }
            else if(temp.compare("add-userA") == 0)
            {
                User user = scanner->scan_userA();
                fsDB->add_user(user);
            }
            else if(temp.compare("ADDUSR") == 0)
            {
                User user = scanner->scan_user();
                fsDB->add_user(user);
            }
            else if( temp.compare("EXIT") == 0)
            {
                controller->clear();
                controller->writeMsg("            ^ ^",0);
                controller->writeMsg("GOOD BYE    O O", 1);
                controller->writeMsg("             o ", 2);
                controller->writeMsg("             v ", 3);
                break;
            }
            else if( temp.compare("TIME") == 0)
            {
                controller->clearLine(2);
                controller->displayTime(2);
            }
            else if(temp.compare("UPDATE"))
            {
                controller->update();
            }
            else if(temp.compare("ADDPRO") == 0)
            {
                Product pro = scanner->scan_product();
                fsDB->add_product(pro);
            }
            else if(temp.compare("show_time") == 0)
            {
                controller->showTime();
            }
        }
    }

    return 0;
}

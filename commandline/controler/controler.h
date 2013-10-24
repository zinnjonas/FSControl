#ifndef CONTROLER_H_
#define CONTROLER_H_

#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <ctime>
#include <string>
#include <usb.h>
#include "opendevice.h"
#include "../../firmware/usbconfig.h"
#include "../../firmware/requests.h"

using namespace std;

class FSControler
{
    public:
        FSControler();
        ~FSControler();

        bool init();
        void writeMsg(string text);
        void writeMsgN(string text);
        void writeMsg(string text, int line);
        void writeMsgN(string text, int line);

        void newLine();
        void displayTime();
        void displayTime(int line);
        void setTime();
        void clear();
        void clearLine(int line);

        void showTime();

        void update();

    private:
        usb_dev_handle *handle;
        char buffer[20];
        int cnt,vid, pid;
        short currentLine;

        const static unsigned char rawVid[2];
        const static unsigned char rawPid[2];
        static char vendor[];
        static char product[];
};

#endif // CONTROLER_H_

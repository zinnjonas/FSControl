#ifndef SCANNER_H_
#define SCANNER_H_

#include <iostream>
#include <sstream>
#include <string>

#include "global.h"
#include "Controler.h"

using namespace std;

#define ScannerPath "/dev/input/by-id/usb-OKE_Electron_Company_OKE_PS2-USB_V1.61-event-kbd"

class Scanner
{
    public:

        Scanner(FSControler* controller);
        virtual ~Scanner();

        bool   init();

        string scan();
        string scan_ASCII();

        int scan_name(string* name, bool putting = true);
        int scan_val(int* val, bool putting = true);
        bool scan_accept();

        User scan_userA();
        User scan_user();

        Product scan_product();

    private:

        FSControler* controller;
        const static char* keys[256];
        char name[265];
        int fevdev;

};


#endif // SCANNER_H_

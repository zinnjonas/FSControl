/*
 * =====================================================================================
 *
 *       Filename:  scanner.cpp
 *
 *    Description:  Test interface for the Barcode scanner
 *
 *        Version:  1.0
 *        Created:  11.06.2013 01:35:30
 *       Revision:  none
 *       Compiler:  gcc
 *
 *         Author:  Jonas Zinn 
 *        Company:  
 *
 * =====================================================================================
 */

#include <iostream>
#include <string>
#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <sys/time.h>
#include <termios.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

using namespace std;


const char *keys[256] = 
  { "", "<esc>", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", 
  "-", "=", "<backspace>", 
  "<tab>", "q", "w", "e", "r", "t", "y", "u", "i", "o", "p", "[", 
  "]", "\n", "<control>", "a", "s", "d", "f", "g", 
  "h", "j", "k", "l", ";", "'", "", "<shift>", 
  "\\", "z", "x", "c", "v", "b", "n", "m", ",", ".", 
  "/", "<shift>", "", "<alt>", " ", "<capslock>", "<f1>", 
  "<f2>", "<f3>", "<f4>", "<f5>", "<f6>", "<f7>", "<f8>", "<f9>", 
  "<f10>", "<numlock>", "<scrolllock>", "", "", "", "", "", "", "", 
  "", "", "", "\\", "f11", "f12", "", "", "", "", "", "", 
  "", "", "<control>", "", "<sysrq>" 
}; 

char name[256] = "Unknown";
char device[256];
int fevdev     = -1;
 
/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  read_string
 *  Description:  read a String from scanner
 * =====================================================================================
 */
	string
read_string (  )
{
	string temp = "";

	if( fevdev == -1)
	{
		cerr << "can't find barcode scanner!" << endl;
		exit(2);
	}

	struct input_event ev;
	int size = sizeof(struct input_event);
	const char* value = "";
	
	while(strcmp(value, "\n")!= 0)
	{
	    read( fevdev,&ev,size);
		value =  keys[ev.code];
		if(ev.value == 1 && ev.type == 1)
		{
			if( strcmp(value, "\n")!=0)
				temp += value;
		}
	}

	return temp;
}		/* -----  end of function readString  ----- */


/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  open_device
 *  Description:  connects to the scanner
 * =====================================================================================
 */
	void
open_device ( )
{
	fevdev = open(device, O_RDONLY);
	if(fevdev == -1)
	{
		cerr << "Failed to open device, need admin rights maybe." << endl;
		exit(1);
	}

	int result =  ioctl(fevdev, EVIOCGNAME(sizeof(name)), name);
    cout << "Reading From : " << device << ", " <<  name << endl;
	
	cout << "Getting exclusive access: ";
	result = ioctl(fevdev,EVIOCGRAB,1);
	if( result == 0)
		cout << "SUCCESS";
	else
		cout << "FAILURE";
	cout << endl;
}		/* -----  end of function open_device  ----- */
 

#include	<stdlib.h>

/* 
 * ===  FUNCTION  ======================================================================
 *         Name:  main
 *  Description:  
 * =====================================================================================
 */
	int
main ( int argc, char *argv[] )
{
	strcpy(device,"/dev/input/by-id/usb-OKE_Electron_Company_OKE_PS2-USB_V1.61-event-kbd");
	open_device();
	while(1)
	{
		cout << read_string() << endl;
	}

	return EXIT_SUCCESS;
}				/* ----------  end of function main  ---------- */


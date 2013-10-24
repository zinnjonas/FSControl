#include "scanner.h"

#include <unistd.h>
#include <errno.h>
#include <fcntl.h>
//#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
//#include <sys/select.h>
#include <sys/time.h>
//#include <termios.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

const char* Scanner::keys[256] =
         {
              "", "<esc>", "1", "2", "3", "4", "5", "6", "7", "8", "9", "0",
              "-", "=", "<backspace>",
              "<tab>", "q", "w", "e", "r", "t", "z", "u", "i", "o", "p", "[",
              "]", "\n", "<control>", "a", "s", "d", "f", "g",
              "h", "j", "k", "l", ";", "'", "", "<shift>",
              "\\", "y", "x", "c", "v", "b", "n", "m", ",", ".",
              "/", "<shift>", "", "<alt>", " ", "<capslock>", "<f1>",
              "<f2>", "<f3>", "<f4>", "<f5>", "<f6>", "<f7>", "<f8>", "<f9>",
              "<f10>", "<numlock>", "<scrolllock>", "", "", "", "", "", "", "",
              "", "", "", "\\", "f11", "f12", "", "", "", "", "", "",
              "", "", "<control>", "", "<sysrq>"
        };

Scanner::Scanner(FSControler* controller)
{
    strcpy(name ,"Unknown");
    fevdev = -1;
    this->controller = controller;
}

Scanner::~Scanner()
{
    //ioctl(fevdev, EVIOCGRAB, 1);
    close(fevdev);
}

bool Scanner::init()
{
/*    fevdev = open(ScannerPath, O_RDONLY);
	if(fevdev == -1)
	{
		cerr << "Failed to open device, need admin rights maybe." << endl;
		return false;
	}*/

//	int result =  ioctl(fevdev, EVIOCGNAME(sizeof(name)), name);

//	result = ioctl(fevdev,EVIOCGRAB,1);
//	if( result != 0)
		//return false;
	return true;
}

string Scanner::scan()
{
    string temp = "";

/*	if( fevdev == -1)
	{
		cerr << "can't find barcode scanner!" << endl;
		return "";
	}

	struct input_event ev;
	int size = sizeof(struct input_event);
	string value = "";

    //read a input line
	while(value.compare("\n")!= 0)
	{
	    read( fevdev,&ev,size);
		value =  keys[ev.code];
		if(ev.value == 1 && ev.type == 1)
		{
			if( value.compare("\n")!=0 && value.compare("\r")!= 0)
				temp += value;
		}
	}
	// read the EOL
	for( int i = 0; i < 4; i++)
        read( fevdev,&ev,size);*/
    /*
    change some ASCII to commands
    */
  /*  if(temp.compare("41")==0){
        temp = "add-user";
    }
    else if(temp.compare("54")==0){
        temp = "TIME";
    }
    else if(temp.compare("61")==0){
        temp = "ADDPROD";
    }
    else if(temp.compare("51") == 0)
       temp = "EXIT";

    size_t pos;

    cout << "scanner: " << temp << endl;

    while( (pos = temp.find("<shift>")) != string::npos)
    {
        temp.replace(pos, 7, "");
        if( pos > 0 && temp[pos-1] == ']')
            temp.replace(pos-1,1,"");
        else
            temp[pos] = toupper(temp[pos]);
    }*/

    cin >> temp;

	return temp;
}

string Scanner::scan_ASCII()
{
    string temp = "";

	/*if( fevdev == -1)
	{
		cerr << "can't find barcode scanner!" << endl;
		return "";
	}

	struct input_event ev;
	int size = sizeof(struct input_event);
	string value = "";

    //read a input line
	while(value.compare("\n")!= 0)
	{
	    read( fevdev,&ev,size);
		value =  keys[ev.code];
		if(ev.value == 1 && ev.type == 1)
		{
			if( value.compare("\n")!=0 && value.compare("\r")!= 0)
				temp += value;
		}
	}
	// read the EOL
	for( int i = 0; i < 4; i++)
        read( fevdev,&ev,size);

    if(temp.compare("41") == 0) // A
        temp = "A";
    else if(temp.compare("42") == 0)
        temp = "B";
    else if(temp.compare("43") == 0)
        temp = "C";
    else if(temp.compare("44") == 0)
        temp = "D";
    else if(temp.compare("45") == 0)
        temp = "E";
    else if(temp.compare("46") == 0)
        temp = "F";
    else if(temp.compare("47") == 0)
        temp = "G";
    else if(temp.compare("48") == 0)
        temp = "H";
    else if(temp.compare("49") == 0)
        temp = "I";
    else if(temp.compare("4<shift>a") == 0)
        temp = "J";
    else if(temp.compare("4<shift>b") == 0)
        temp = "K";
    else if(temp.compare("4<shift>c") == 0)
        temp = "L";
    else if(temp.compare("4<shift>d") == 0)
        temp = "M";
    else if(temp.compare("4<shift>e") == 0)
        temp = "N";
    else if(temp.compare("4<shift>f") == 0)
        temp = "O";
    else if(temp.compare("50") == 0)
        temp = "P";
    else if(temp.compare("51") == 0)
       temp = "Q";
    else if(temp.compare("52") == 0)
        temp = "R";
    else if(temp.compare("53") == 0)
        temp = "S";
    else if(temp.compare("54") == 0)
        temp = "T";
    else if(temp.compare("55") == 0)
        temp = "U";
    else if(temp.compare("56") == 0)
        temp = "V";
    else if(temp.compare("57") == 0)
        temp = "W";
    else if(temp.compare("58") == 0)
        temp = "X";
    else if(temp.compare("59") == 0)
        temp = "Y";
    else if(temp.compare("5<shift>a") == 0)
        temp = "Z"; // Z

    else if(temp.compare("61") == 0) // a
        temp = "a";
    else if(temp.compare("62") == 0)
        temp = "b";
    else if(temp.compare("63") == 0)
        temp = "c";
    else if(temp.compare("64") == 0)
        temp = "d";
    else if(temp.compare("65") == 0)
        temp = "e";
    else if(temp.compare("66") == 0)
        temp = "f";
    else if(temp.compare("67") == 0)
        temp = "g";
    else if(temp.compare("68") == 0)
        temp = "h";
    else if(temp.compare("69") == 0)
        temp = "i";
    else if(temp.compare("6<shift>a") == 0)
        temp = "j";
    else if(temp.compare("6<shift>b") == 0)
        temp = "k";
    else if(temp.compare("6<shift>c") == 0)
        temp = "l";
    else if(temp.compare("6<shift>d") == 0)
        temp = "m";
    else if(temp.compare("6<shift>e") == 0)
        temp = "n";
    else if(temp.compare("6f") == 0)
        temp = "o";
    else if(temp.compare("70") == 0)
        temp = "p";
    else if(temp.compare("71") == 0)
        temp = "q";
    else if(temp.compare("72") == 0)
        temp = "r";
    else if(temp.compare("73") == 0)
        temp = "s";
    else if(temp.compare("74") == 0)
        temp = "t";
    else if(temp.compare("75") == 0)
        temp = "u";
    else if(temp.compare("76") == 0)
        temp = "v";
    else if(temp.compare("77") == 0)
        temp = "w";
    else if(temp.compare("78") == 0)
        temp = "x";
    else if(temp.compare("79") == 0)
        temp = "y";
    else if(temp.compare("7a") == 0)
        temp = "z"; // z

    else if(temp.compare("30") == 0)
        temp = "0"; // 0
    else if(temp.compare("31") == 0)
        temp = "1";
    else if(temp.compare("32") == 0)
        temp = "2";
    else if(temp.compare("33") == 0)
        temp = "3";
    else if(temp.compare("34") == 0)
        temp = "4";
    else if(temp.compare("35") == 0)
        temp = "5";
    else if(temp.compare("36") == 0)
        temp = "6";
    else if(temp.compare("37") == 0)
        temp = "7";
    else if(temp.compare("38") == 0)
        temp = "8";
    else if(temp.compare("39") == 0)
        temp = "9"; // 9

    else if(temp.compare("3c") == 0) // >
    temp = ">";
    else if(temp.compare("3e") == 0) // <
    temp = "<";
    else if(temp.compare("3d") == 0) // =
        temp = "=";
    else if(temp.compare("2e") == 0) // .
        temp = ".";
    else if(temp.compare("2c") == 0) // ,
        temp = ",";
    else if(temp.compare("2d") == 0)
        temp = "-";*/
    return temp;
}

User Scanner::scan_userA()
{
    User user;
    user.credit = 0;
    controller->clear();
    controller->writeMsg("add User!", 0);
    controller->writeMsg("scan Matrikel-Nr:",1);
    user.matr = scan();
    controller->writeMsg("add User:"+user.matr,0);
    controller->clearLine(1);

    for(int i = 1; i < 4; i++){
        ostringstream text;
        if( i == 1)
        {
            text << "Email:";
        }
        else if( i == 2)
        {
            text << "Name: ";
        }
        else if( i == 3)
        {
            text << "Credit:";
        }
        controller->clearLine(i);
        controller->writeMsgN(text.str(),i);

        ostringstream ttext;
        if(i == 1)
        {

            scan_name(&user.email);
            ttext << "Email:" << user.name;
            user.name = user.email.substr(0, user.email.find("."));
        }
        else if(i == 2)
        {
            controller->writeMsgN(user.name + "?");
            if( !scan_accept())
            {
                controller->clearLine(i);
                controller->writeMsg(text.str(),i);
                scan_name(&user.name);
            }
            ttext << "Name:" << user.name;
        }
        else if(i == 3)
        {
            controller->writeMsgN(user.credit + "");
            if( !scan_accept())
            {
                controller->clearLine(i);
                controller->writeMsg(text.str(),i);
                scan_val(&user.credit);
            }
            ttext << "Credit:" << user.credit;
        }

        controller->clearLine(i);
        controller->writeMsgN(ttext.str(), i);
    }

    return user;
}

User Scanner::scan_user()
{
    User user;

    user.credit = 0;
    controller->clear();
    controller->writeMsg("add User!", 0);
    controller->writeMsg("scan Matrikel-Nr:",1);
    user.matr = scan();
    controller->writeMsg("add User:"+user.matr,0);
    controller->clearLine(1);

    for(int i = 1; i < 4; i++){
        ostringstream text;
        if( i == 1)
        {
            text << "Email:";
        }
        else if( i == 2)
        {
            text << "Name: ";
        }
        else if( i == 3)
        {
            text << "Credit:";
        }
        controller->clearLine(i);
        controller->writeMsgN(text.str(),i);

        ostringstream ttext;
        if(i == 1)
        {

            user.email = scan();
            ttext << "Email:" << user.name;
            user.name = user.email.substr(0, user.email.find("."));
        }
        else if(i == 2)
        {
            controller->writeMsgN(user.name + "?");
            if( !scan_accept())
            {
                controller->clearLine(i);
                controller->writeMsg(text.str(),i);
                user.name = scan();
            }
            ttext << "Name:" << user.name;
        }
        else if(i == 3)
        {
            controller->writeMsgN(user.credit + "");
            if( !scan_accept())
            {
                controller->clearLine(i);
                controller->writeMsg(text.str(),i);
                istringstream i(scan());
                i >> user.credit;
            }
            ttext << "Credit:" << user.credit;
        }

        controller->clearLine(i);
        controller->writeMsg(ttext.str(), i);
    }

    return user;
}

int Scanner::scan_name(string* name, bool putting){

    while(true)
    {
        string c = scan_ASCII();
        if( c.compare("=") == 0){
            return 1;
        }
        *name += c;
        if( putting)
            controller->writeMsg(c);
        cout << *name << endl;
    }
}

int Scanner::scan_val(int *val, bool putting){
    string temp;

    while(true)
    {
        string c = scan_ASCII();
        if( c.compare("=") == 0){
            istringstream i(temp);
            if (!(i >> *val))
                *val = 0;
            return 1;
        }
        temp += c;
        if( putting)
            controller->writeMsg(c);
        cout << temp << endl;
    }
}

bool Scanner::scan_accept()
{
    string c = scan_ASCII();

    return (c.compare("=") == 0);
}

Product Scanner::scan_product()
{
    Product pro;

    controller->clear();
    controller->writeMsg("add Product!", 0);
    controller->writeMsg("scan barcode:",1);
    pro.barcode = scan();
    controller->writeMsg("add Prod:"+pro.barcode,0);
    controller->clearLine(1);

    for(int i = 1; i < 3; i++){
        ostringstream text;
        if( i == 1)
        {
            text << "Name:";
        }
        else if( i == 2)
        {
            text << "Price: ";
        }

        controller->clearLine(i);
        controller->writeMsgN(text.str(),i);

        ostringstream ttext;
        if(i == 1)
        {

            pro.name = scan();
            ttext << "Name:" << pro.name;
        }
        else if(i == 2)
        {
            istringstream i(scan());
            i >> pro.price;
            ttext << "price:" << pro.price;
        }

        controller->clearLine(i);
        controller->writeMsg(ttext.str(), i);
    }

    return pro;
}

#include "Controler.h"


const unsigned char FSControler::rawVid[2] = {USB_CFG_VENDOR_ID};
const unsigned char FSControler::rawPid[2] = {USB_CFG_DEVICE_ID};
char FSControler::vendor[] = {USB_CFG_VENDOR_NAME,0};
char FSControler::product[] = {USB_CFG_DEVICE_NAME,0};

FSControler::FSControler()
{
    currentLine = 0;

    usb_init();

    vid = rawVid[1] * 256 + rawVid[0];
    pid = rawPid[1] * 256 + rawPid[0];
}

FSControler::~FSControler()
{
    usb_close(handle);
}

bool FSControler::init()
{
    if(usbOpenDevice(&handle, vid, vendor, pid, product, NULL, NULL, NULL) != 0)
    {

        cerr << "Could not find USB device \"" << product << "\" with vid=0x" << hex << vid << " pid=0x" << hex << pid << " " << vendor << endl;
        return false;
    }

    return true;
}

void FSControler::writeMsg(string text)
{
    cout << "write Msg" << endl;
    strcpy(buffer, text.c_str());
    cnt = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, FSCONTROL_WRITE, 0, 0, buffer, text.size()+1, 5000);
    if(cnt < 0){
        cerr << "USB error: %" <<  usb_strerror() << endl;
    }
}

void FSControler::writeMsgN(string text)
{
    cout << "write Msg" << endl;
    strcpy(buffer, text.c_str());
    cnt = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, FSCONTROL_SELECT, 0, 0, buffer, text.size()+1, 5000);
    if(cnt < 0){
        cerr << "USB error: %" <<  usb_strerror() << endl;
    }
}

void FSControler::writeMsg(string text, int line)
{
    cout << "write Msg" << endl;
    currentLine = line;
    cnt = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, FSCONTROL_SETY, line, 0, buffer, 0, 5000);
    if(cnt < 0){
        cerr << "USB error: %" <<  usb_strerror() << endl;
    }
    writeMsg(text);
}

void FSControler::writeMsgN(string text, int line)
{
    cout << "write Msg" << endl;
    currentLine = line;
    cnt = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, FSCONTROL_SETY, line, 0, buffer, 0, 5000);
    if(cnt < 0){
        cerr << "USB error: %" <<  usb_strerror() << endl;
    }
    writeMsgN(text); // writeMsgN
}

void FSControler::newLine()
{
    cout << "new Line" << endl;
    currentLine++;
    if( currentLine > 3)
        currentLine = 0;
    cnt = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, FSCONTROL_SETY, currentLine, 0, buffer, 0, 5000);
    if(cnt < 0){
        cerr << "USB error: %" <<  usb_strerror() << endl;
    }
}

void FSControler::displayTime()
{
    cout << "display time" << endl;
    cnt = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, FSCONTROL_DISPLAYTIME, 0, 0, buffer, 0, 5000);
    if(cnt < 0){
        cerr << "USB error: %" <<  usb_strerror() << endl;
    }
}

void FSControler::displayTime(int line)
{
    currentLine = line;
    cnt = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, FSCONTROL_SETY, line, 0, buffer, 0, 5000);
    if(cnt < 0){
        cerr << "USB error: %" <<  usb_strerror() << endl;
    }
    cout << "display time" << endl;
    cnt = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, FSCONTROL_DISPLAYTIME, 0, 0, buffer, 0, 5000);
    if(cnt < 0){
        cerr << "USB error: %" <<  usb_strerror() << endl;
    }
}

void FSControler::update()
{
    cnt = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, FSCONTROL_UPDATE_BUS, 0, 0, buffer, 0, 5000);
    if(cnt < 0){
        cerr << "USB error: %" <<  usb_strerror() << endl;
    }
}

void FSControler::setTime()
{
    cout << "set Time" << endl;
    time_t t = time(0);   // get time now
    struct tm * now = localtime( & t );

    cnt = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, FSCONTROL_SETHR, now->tm_hour, 0, buffer, 0, 5000);
    if(cnt < 0){
        cerr << "USB error: %" <<  usb_strerror() << endl;
    }

    cnt = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, FSCONTROL_SETMI, now->tm_min, 0, buffer, 0, 5000);
    if(cnt < 0){
        cerr << "USB error: %" <<  usb_strerror() << endl;
    }
    cnt = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, FSCONTROL_SETSE, now->tm_sec, 0, buffer, 0, 5000);
    if(cnt < 0){
        cerr << "USB error: %" <<  usb_strerror() << endl;
    }
    cnt = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, FSCONTROL_SETDA, now->tm_mday, 0, buffer, 0, 5000);
    if(cnt < 0){
        cerr << "USB error: %" <<  usb_strerror() << endl;
    }
    cnt = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, FSCONTROL_SETMO, now->tm_mon+1, 0, buffer, 0, 5000);
    if(cnt < 0){
        cerr << "USB error: %" <<  usb_strerror() << endl;
    }
    cnt = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, FSCONTROL_SETYE, 13, 0, buffer, 0, 5000);
    if(cnt < 0){
        cerr << "USB error: %" <<  usb_strerror() << endl;
    }
    cnt = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, FSCONTROL_SETWD, 3, 0, buffer, 0, 5000);
    if(cnt < 0){
        cerr << "USB error: %" <<  usb_strerror() << endl;
    }
    cnt = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, FSCONTROL_SETDATE, 0, 0, buffer, 0, 5000);
    if(cnt < 0){
        cerr << "USB error: %" <<  usb_strerror() << endl;
    }
}

void FSControler::clear()
{
    cout << "clear" << endl;
    cnt = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, FSCONTROL_CLEAR, 0, 0, buffer, 0, 5000);
    if(cnt < 0){
        cerr << "USB error: %" <<  usb_strerror() << endl;
    }
}

void FSControler::clearLine(int line)
{
    writeMsg("                    ",line);
}

void FSControler::showTime()
{
    cout << "show_time" << endl;
    cnt = usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, FSCONTROL_UPDATE_BUS, 0, 0, buffer, 0, 5000);
    if(cnt < 0){
        cerr << "USB error: %" <<  usb_strerror() << endl;
    }
}

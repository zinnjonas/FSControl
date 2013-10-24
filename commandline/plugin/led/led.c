#include "led.h"

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <usb.h>
#include "opendevice.h"
#include "commands.h"
#include "usbconfig.h"

usb_dev_handle      *handle = NULL;
const unsigned char rawVid[2] = {USB_CFG_VENDOR_ID}, rawPid[2] = {USB_CFG_DEVICE_ID};
char                vendor[] = {USB_CFG_VENDOR_NAME, 0}, product[] = {USB_CFG_DEVICE_NAME, 0};
int                 vid, pid, isOn;
char                buffer[4];

bool init_led_controler()
{
    usb_init();
    /*  compute VID/PID from usbconfig.h so that there is a central source of information */
	vid = rawVid[1] * 256 + rawVid[0];
	pid = rawPid[1] * 256 + rawPid[0];
	/*  The following function is in opendevice.c: */
	if(usbOpenDevice(&handle, vid, vendor, pid, product, NULL, NULL, NULL) != 0){
		fprintf(stderr, "Could not find USB device \"%s\" with vid=0x%x pid=0x%x\n", product, vid, pid);
		return false;
	}
	return true;
}

void set_led_color(int r, int g, int b)
{
    usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,RGB_R, r, 0, buffer, sizeof(buffer), 5000);
    usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,RGB_G, g, 0, buffer, sizeof(buffer), 5000);
    usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,RGB_B, b, 0, buffer, sizeof(buffer), 5000);
    usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,SET, 0, 0, buffer, sizeof(buffer), 5000);
}

void set_led_color_on( int r, int g, int b, bool on)
{
    usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,RGB_R, r, 0, buffer, sizeof(buffer), 5000);
    usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,RGB_G, g, 0, buffer, sizeof(buffer), 5000);
    usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,RGB_B, b, 0, buffer, sizeof(buffer), 5000);
    usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,SET, 0, 0, buffer, sizeof(buffer), 5000);
    if( on)
        set_led_on();
    else
        set_led_off();
}

void set_led_on()
{
    usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, ON, 0, 0, buffer, sizeof(buffer), 5000);
}

void set_led_off()
{
    usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, OFF, 0, 0, buffer, sizeof(buffer), 5000);
}

void set_led_command(char* command)
{
    if(strcasecmp(command, "rosa") == 0){
		usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,RGB_R, 0x007f, 0, buffer, sizeof(buffer), 5000);
	    usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,RGB_G, 0x004f, 0, buffer, sizeof(buffer), 5000);
		usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,RGB_B, 0x005f, 0, buffer, sizeof(buffer), 5000);
		usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,SET, 0, 0, buffer, sizeof(buffer), 5000);
	}
	else if(strcasecmp(command, "purple") == 0){
		usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,RGB_R, 0x004f, 0, buffer, sizeof(buffer), 5000);
	    usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,RGB_G, 0x0000, 0, buffer, sizeof(buffer), 5000);
		usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,RGB_B, 0x00ff, 0, buffer, sizeof(buffer), 5000);
		usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,SET, 0, 0, buffer, sizeof(buffer), 5000);
	}
    else if(strcasecmp(command, "pink") == 0){
		usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,PINK, 0, 0, buffer, sizeof(buffer), 5000);
    }
    else if(strcasecmp(command, "rose") == 0){
        usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,ROSE, 0, 0, buffer, sizeof(buffer), 5000);
	}
	else if(strcasecmp(command, "orange") == 0){
		usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,ORANGE, 0, 0, buffer, sizeof(buffer), 5000);
	}
	else if(strcasecmp(command, "gelb") == 0){
		usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,YELLOW, 0, 0, buffer, sizeof(buffer), 5000);
	}
	else if(strcasecmp(command, "turkis") == 0){
        usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,TURKIS, 0, 0, buffer, sizeof(buffer), 5000);
	}
	else	if(strcasecmp(command, "blau") == 0){
		usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,BLUE, 0, 0, buffer, sizeof(buffer), 5000);
	}
	else if(strcasecmp(command, "gruen") == 0){
        usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,GREEN, 0, 0, buffer, sizeof(buffer), 5000);
	}
	else if(strcasecmp(command, "rot") == 0){
		usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT,RED, 0, 0, buffer, sizeof(buffer), 5000);
	}
	else if(strcasecmp(command, "weiss") == 0){
		usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, WHITE, 0, 0, buffer, sizeof(buffer), 5000);
	}
	else if(isOn = (strcasecmp(command, "on") == 0)){
		usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, ON, 0, 0, buffer, sizeof(buffer), 5000);
    }
    else if(isOn = (strcasecmp(command, "off") == 0)){
		usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_OUT, OFF, 0, 0, buffer, sizeof(buffer), 5000);
    }
}

bool get_led_status(int* r, int* g, int* b)
{
    usb_control_msg(handle, USB_TYPE_VENDOR | USB_RECIP_DEVICE | USB_ENDPOINT_IN, STATUS, 0, 0, buffer, sizeof(buffer), 5000);
    *r = (int)buffer[1] & 0xff;
    *g = (int)buffer[2] & 0xff;
    *b = (int)buffer[3] & 0xff;
    return (int)buffer[0] & 0xff;
}


void relese_led_controler()
{
    if( NULL != handle)
    {
        usb_close(handle);
        handle = NULL;
    }
}

unsigned int convertHexString(const char * s) {
 unsigned int result = 0;
 int c ;
 if ('0' == *s && 'x' == *(s+1))
	 s+=2;
  while (*s) {
   result = result << 4;
   if (c=(*s-'0'),(c>=0 && c <=9)) result|=c;
   else if (c=(*s-'A'),(c>=0 && c <=5)) result|=(c+10);
   else if (c=(*s-'a'),(c>=0 && c <=5)) result|=(c+10);
   else break;
   ++s;
  }
 return result;
}


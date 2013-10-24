#ifndef LED_H_
#define LED_H_

#include <stdbool.h>

bool init_led_controler();

void set_led_color(int r, int g, int b);
void set_led_color_on( int r, int g, int b, bool on);
void set_led_on();
void set_led_off();
void set_led_command(char* command);

bool get_led_status(int* r, int* g, int* b);

void relese_led_controler();

unsigned int convertHexStr(const char*);

#endif // LED_H_


#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <linux/fb.h>
#include "framebuffer.h"

//Displays the time on the device using helper functions
void display_time(int hours, int minutes, int seconds, pi_framebuffer_t *dev);

//Displays the colons used to separate the hours, minutes, and seconds (colored white)
void display_colons(pi_framebuffer_t *dev);

//Displays hours on the device in binary (colored blue)
void display_hours(int hours, pi_framebuffer_t *dev);

//Displays minutes on the device in binary (colored yellow)
void display_minutes(int minutes, pi_framebuffer_t *dev);

//Displays seconds on the device in binary (colored red)
void display_seconds(int seconds, pi_framebuffer_t *dev);

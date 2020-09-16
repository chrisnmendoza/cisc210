#include <stdlib.h>
#include <stdio.h>
#include "framebuffer.h"

//draws the colon
void display_colons(pi_framebuffer_t *dev){
    uint16_t white=getColor(255,255,255);
    dev->bitmap->pixel[1][1]=white;
    dev->bitmap->pixel[1][2]=white;
    dev->bitmap->pixel[2][1]=white;
    dev->bitmap->pixel[2][2]=white;

    dev->bitmap->pixel[4][1]=white;
    dev->bitmap->pixel[4][2]=white;
    dev->bitmap->pixel[5][1]=white;
    dev->bitmap->pixel[5][2]=white;

    dev->bitmap->pixel[1][4]=white;
    dev->bitmap->pixel[2][4]=white;
    dev->bitmap->pixel[1][5]=white;
    dev->bitmap->pixel[2][5]=white;

    dev->bitmap->pixel[4][4]=white;
    dev->bitmap->pixel[4][5]=white;
    dev->bitmap->pixel[5][4]=white;
    dev->bitmap->pixel[5][5]=white;
}


//displays the hours
void display_hours(int hours, pi_framebuffer_t *dev){
        uint16_t blue=getColor(0,0,255);
        int i;
        for (i=4;i>=0;i--){
        if ((hours>>(4-i))%2==1){
        dev->bitmap->pixel[4-i][6]=blue;
        }
        }
}


//displays the minutes
void display_minutes(int minutes, pi_framebuffer_t *dev){
        uint16_t yellow=getColor(255,255,0);
        int i;
        for (i=5;i>=0;i--){
        if ((minutes>>(5-i))%2==1){
        dev->bitmap->pixel[5-i][3]=yellow;
        }
        }
}


//displays the seconds
void display_seconds(int seconds, pi_framebuffer_t *dev){
        uint16_t red=getColor(255,0,0);
        int i;
        for (i=5;i>=0;i--){
        if ((seconds>>(5-i))%2==1){
        dev->bitmap->pixel[5-i][0]=red;
        }
        }
}

//displays the time
void display_time(int hours, int minutes, int seconds,pi_framebuffer_t *dev){
        clearBitmap(dev->bitmap,0);
        display_colons(dev);
        display_hours(hours,dev);
        display_minutes(minutes,dev);
        display_seconds(seconds,dev);
}


#include "framebuffer.h"
#include <stdio.h>

int main(void) {
    uint16_t red=getColor(255,0,0);
    pi_framebuffer_t *fb=getFBDevice();
    for(int j=0;j<4;j++)
    {
        fb->bitmap->pixel[j][j]=red;
        fb->bitmap->pixel[7-j][j]=red;
        fb->bitmap->pixel[j][7-j]=red;
        fb->bitmap->pixel[7-j][7-j]=red;
    }
    printf("Hit enter to continue.");
    char garbage; /* Just used so the scanf has something to chew on */
    scanf("%c",&garbage);
    clearBitmap(fb->bitmap,0);
    return 0;
}

#include <stdlib.h>
#include <stdio.h>
#include "framebuffer.h"
#include "display.h"
int main(void){
int currenthour;
int currentminute;
int currentsecond;
int basecase=3;
pi_framebuffer_t *fb=getFBDevice();
while (basecase==3){
basecase=scanf("%i:%i:%i",&currenthour,&currentminute,&currentsecond);
display_time(currenthour,currentminute,currentsecond,fb);
}
clearBitmap(fb->bitmap,0);
return 0;
}


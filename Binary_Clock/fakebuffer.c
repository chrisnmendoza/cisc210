#include "framebuffer.h"
#include <stdint.h>
#include <linux/fb.h>
#include <stdio.h>
#include <stdlib.h>

/*getFBDevice
  returns a pi_framebuffer_t object describing the sense hat frame buffer, or null on failure
  Note: function allocates a pi_framebuffer_t object on success which must be freed with a call to freeFrameBuffer()
*/
pi_framebuffer_t *fakebuffer;
pi_framebuffer_t* getFBDevice() {
    fakebuffer = malloc(sizeof(pi_framebuffer_t));
    fakebuffer->bitmap=calloc(1,sizeof(sense_fb_bitmap_t));
    return fakebuffer;
}

void renderFakebuffer(void) {
    for(int i=0; i<8; i++){
        for(int j=0; j<8; j++){
            uint16_t color=fakebuffer->bitmap->pixel[i][j];
            int blue=(color>>1&0b1111);
            int green=(color>>6&0b1111);
            int red=(color>>12&0b1111);
            printf("%1x%1x%1x ",red,blue,green);
            //printf("%d,%d,%d ",red,blue,green);
        }
        printf("\n");
    }
}

/*freeFrameBuffer
  frees and unmaps a previously allocated frame buffer
*/
void freeFrameBuffer(pi_framebuffer_t* device) {
    free(device->bitmap);
    free(device);
}

/*clearBitmap
  bitmap: a bitmap object to modify
  color: the fill color for the bitmap
  Fills the bitmap with the color
*/
void clearBitmap(sense_fb_bitmap_t* bitmap,uint16_t color){
    for(int i=0;i<8;i++)
        for(int j=0;j<8;j++)
            bitmap->pixel[i][j]=color;
}

/*getColor
  red: the 8 bit red component
  green: the 8 bit green component
  blue: the 8 bit blue component
  returns a 16 bit representation of the 32 bit color specified by the arguments
*/
uint16_t getColor(int red,int green,int blue) {
    red=red>>3;
    green=green>>3;
    blue=blue>>3;
    return red<<11|green<<5|blue;
}

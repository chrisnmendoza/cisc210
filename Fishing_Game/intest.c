#include <signal.h>
#include "sense.h"
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
int running=1;
int y=5;
int x=5;



void castRod(pi_i2c_t *gyro){
        coordinate_t data;
        data.x=0;
        while(data.y>-.5){
        getAccelData(gyro,&data);
        }
        printf("yeehaw");
        while(data.y<.5){
        getAccelData(gyro,&data);
        }
        printf("yoohoo");
}

int main(){
	pi_i2c_t *pi=geti2cDevice();
	castRod(pi);
	return 0;
}

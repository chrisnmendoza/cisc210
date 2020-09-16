#include "sense.h"
#include <linux/input.h>
#include <stdio.h>

int running=1;
pi_i2c_t* gyro=NULL;

void callbackFunc(unsigned int code) {
    if(code == KEY_ENTER) {
        running=0;
    } else if(gyro) {
        coordinate_t data;
        getAccelData(gyro,&data);
        printf("%f %f %f\n",data.x,data.y,data.z);
    }
}

int main(void) {
    pi_joystick_t* joystick=getJoystickDevice();
    gyro=geti2cDevice();
    configureAccelGyro(gyro);
/*
    while(running){
        pollJoystick(joystick,callbackFunc,1000);
    }
*/
	coordinate_t data;
	data.x=0;
	while(data.x>-.5){
	getAccelData(gyro,&data);
	}
	printf("yeehaw");
	while(data.x<.5){
	getAccelData(gyro,&data);
	}
	printf("yoohoo");
    freeJoystick(joystick);
}


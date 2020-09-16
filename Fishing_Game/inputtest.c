#include <stdio.h>
#include <stdlib.h>
#include "sense.h"
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <linux/input.h>
#include "project.h"

int main(){
int *oldPos=malloc(2*sizeof(int));
int *newPos=malloc(2*sizeof(int));
int *fish=malloc(4*sizeof(int));
int *shark=malloc(3*sizeof(int));
int success=0;
fish[0]=5;
fish[1]=1;
fish[2]=6;
fish[3]=2;
shark[0]=5;
shark[1]=5;
shark[2]=0;
printf("Fish is at: (%i,%i)\n",fish[0],fish[1]);
printf("Shark covers a rectangular area with corners: (%i,%i) and (%i,%i)\n",shark[0],shark[1],shark[0]+2,shark[1]-3);
pi_joystick_t *joystick=getJoystickDevice();
pi_i2c_t *pi=geti2cDevice();
int configuration=configureAccelGyro(pi);
getPos(oldPos);
getPos(newPos);
printf("cast rod to continue\n");
castRod(pi);
printf("Reel in the fish or go to the shark's position to stop this test\n");
while(success==0){
	getPos(oldPos);
	pollJoystick(joystick,movePos,0);
	getPos(newPos);
	//printf("%i%i%i%i",oldPos[0],oldPos[1],newPos[0],newPos[1]);
	if(oldPos[0]!=newPos[0] || oldPos[1]!=newPos[1]){
		printf("This is the current position: (%i,%i)\n",newPos[0],newPos[1]);
	}
	if(reel(pi,fish,newPos)!=0){
		printf("caught!\n");
		success=1;
	}
	if(sharkDetect(shark,newPos)!=0){
		printf("you got eaten by the shark!\n");
		success=1;
	}
	usleep(500);

}
free(oldPos);
free(newPos);
free(fish);
free(shark);
freeJoystick(joystick);
freei2cDevice(pi);
return 0;
}

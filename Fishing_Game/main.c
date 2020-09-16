#include <stdio.h>
#include <stdlib.h>
#include "sense.h"
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <linux/input.h>
#include "project.h"

int main(void){
	srand(time(0));
	int score=0;
	int *sharkPos=malloc(10*(sizeof(int)));
	sharkPos[2]=8;
	int *fishPos=malloc(10*(sizeof(int)));
	fishPos[0]=8;
	int *fishBobber=malloc(5*(sizeof(int)));
	int *getPosPtr=malloc(5*(sizeof(int)));
	fishBobber[0]=3;
	fishBobber[1]=4;
	pi_framebuffer_t *fb=malloc(10*(sizeof(pi_framebuffer_t)));
	fb=getFBDevice();
	pi_i2c_t *pi=geti2cDevice();
	pi_joystick_t *joystick=getJoystickDevice();
	int configuration=configureAccelGyro(pi);
	startScreen(fb);
	//printf("casting rod");
	castRod(pi);
	castAnimation(fb);
	//printf("defining more stuff\n");
	int gameOver=0;
	int fishCounter=0;
	int sharkCounter=0;
	int counter=0;
	//printf("going inside while loop\n ");
	while(gameOver==0 && score<5){
		if(sharkPos[2]==8){
			sharkPos=sharkSpawn(fb,sharkPos);
		}
		if(fishPos[0]==8){
			fishPos=fishSpawn(fb,fishPos);
		}
		if(sharkCounter>50){
			sharkPos=sharkMove(fb,sharkPos);
			sharkCounter=0;
		}
		if(fishCounter>250){
			fishPos=fishMove(fb,fishPos);
			fishCounter=0;
		}
		sharkCounter=sharkCounter+1;
		fishCounter=fishCounter+1;
		pollJoystick(joystick,movePos,0);
		fishBobber=rodMove(fb,fishBobber,getPos(getPosPtr));
		gameOver=sharkDetect(sharkPos,fishBobber);
		if(reel(pi,fishPos,fishBobber)!=0){
			score=score+1;
			fishPos=fishSpawn(fb,fishPos);
		}
		usleep(500);
	}
	clearBitmap(fb->bitmap,0);
	if(gameOver==1){
		gameOverScreen(fb);
	}
	else{
		winScreen(fb);
	}
	sleep(2);
	clearBitmap(fb->bitmap,0);
	displayScore(fb,score);
	sleep(3);
	clearBitmap(fb->bitmap,0);
	free(sharkPos);
	free(fishPos);
	free(fishBobber);
	free(getPosPtr);
	freeJoystick(joystick);
	freei2cDevice(pi);
	freeFrameBuffer(fb);
	return 0;
}

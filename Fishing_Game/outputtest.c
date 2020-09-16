#include <stdio.h>
#include <stdlib.h>
#include "sense.h"
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <linux/input.h>
#include "project.h"


int main(){
	int *sharkPos=malloc(2*sizeof(int));
	int *fishPos=malloc(4*sizeof(int));
	int *bobberPos=malloc(2*sizeof(int));
	bobberPos[0]=3;
	bobberPos[1]=5;
	int *newPos=malloc(2*sizeof(int));
	newPos[0]=2;
	newPos[1]=5;
	pi_framebuffer_t *fb=malloc(sizeof(pi_framebuffer_t));
	fb=getFBDevice();
	char *a=malloc(sizeof(char));
	printf("Hit Enter to Initialize startScreen");
	scanf("%c",a);
	startScreen(fb);
	printf("Hit Enter to Initialize castAnimation");
	scanf("%c",a);
	castAnimation(fb);
	printf("Hit Enter to Initialize drawSea");
	scanf("%c",a);
	drawSea(fb);
	printf("Hit Enter to Initialize fishSpawn");
	scanf("%c",a);
	fishPos=fishSpawn(fb,fishPos);
	printf("Hit Enter to Initialize fishMove");
	scanf("%c",a);
	fishPos=fishMove(fb,fishPos);
	printf("Hit Enter to Initialize sharkSpawn");
	scanf("%c",a);
	sharkPos=sharkSpawn(fb,sharkPos);
	printf("Hit Enter to Initialize sharkMove");
	scanf("%c",a);
	sharkPos=sharkMove(fb,sharkPos);
	printf("Hit Enter to Initialize rodMove");
	scanf("%c",a);
	bobberPos=rodMove(fb,bobberPos,bobberPos);
	sleep(1);
	bobberPos=rodMove(fb,bobberPos,newPos);
	printf("Hit Enter to Initialize gameOverScreen");
	scanf("%c",a);
	gameOverScreen(fb);
	printf("Hit Enter to Initialize winScreen");
	scanf("%c",a);
	winScreen(fb);
	printf("Hit Enter to Initialize all possible scores one second after another for displayScore");
	scanf("%c",a);
	int counter;
	for(counter=0;counter<=5;counter++){
		displayScore(fb,counter);
		sleep(1);
	}
	free(sharkPos);
	free(fishPos);
	free(bobberPos);
	free(newPos);
	freeFrameBuffer(fb);
	return 0;
}

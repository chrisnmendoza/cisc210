#include <stdio.h>
#include <stdlib.h>
#include "sense.h"
#include <unistd.h>
#include <time.h>

void startScreen(pi_framebuffer_t *dev){
	uint16_t blue=getColor(0,0,128);
	uint16_t yellow=getColor(203,118,10);
	uint16_t sea=getColor(16,140,145);
	uint16_t bobber=getColor(255,36,0);
	uint16_t lineString=getColor(255,255,255);
	int i;
	clearBitmap(dev->bitmap,0);
	for(i=2;i<=6;i++){
		setPixel(dev->bitmap,0,i,blue);
		setPixel(dev->bitmap,4,i,yellow);
		setPixel(dev->bitmap,7,i,yellow);
	}
	for(i=0;i<=3;i++){
		setPixel(dev->bitmap,i,1,blue);
		setPixel(dev->bitmap,i+4,1,yellow);
		setPixel(dev->bitmap,i+4,6,yellow);
		setPixel(dev->bitmap,i,6,blue);
	}
	for(i=4;i<=6;i++){
		setPixel(dev->bitmap,3,i,blue);
	}
	setPixel(dev->bitmap,2,4,blue);
}


void castAnimation(pi_framebuffer_t *dev){
	uint16_t sea=getColor(16,140,145);
	uint16_t bobber=getColor(255,36,0);
	uint16_t lineString=getColor(255,255,255);
	clearBitmap(dev->bitmap,sea);
	setPixel(dev->bitmap,3,7,bobber);
	usleep(200000);
	int i;
	for(i=6;i>=4;i--){
		setPixel(dev->bitmap,3,i,bobber);
		setPixel(dev->bitmap,3,(i+1),lineString);
		usleep(200000);
	}
	for(i=6;i>=4;i--){
		setPixel(dev->bitmap,3,(i+1),sea);
	}
}



void catchAnimation(pi_framebuffer_t *dev,int success){
	int i;
	uint16_t green=getColor(57,255,20);
	uint16_t red=getColor(255,40,20);
	if(success==1){
		for(i=0;i<=3;i++){
			setPixel(dev->bitmap,i,i+2,green);
		}
		for(i=0;i<=3;i++){
			setPixel(dev->bitmap,i+4,4-i,green);
		}
	}
	else if(success<0){
		for(i=0;i<=5;i++){
			setPixel(dev->bitmap,i+1,i+1,red);
			setPixel(dev->bitmap,i+1,6-i,red);
		}
	}
}



void drawSea(pi_framebuffer_t *dev){
	uint16_t sea=getColor(16,140,145);
	clearBitmap(dev->bitmap,sea);

}
int *fishSpawn(pi_framebuffer_t *dev,int *fishPosition){
	uint16_t fishColor=getColor(255,211,0);
	uint16_t sea=getColor(16,140,145);
	int fishHeadX=abs(rand() % 8);
	int fishHeadY=abs(rand() % 8);
	int fishTailX=8;
	int fishTailY=8;
	if(fishPosition[0]!=8){
		setPixel(dev->bitmap,fishPosition[0],fishPosition[1],sea);
		setPixel(dev->bitmap,fishPosition[2],fishPosition[3],sea);
	}
	while(fishTailX>7 || fishTailY>7){
	fishTailX=abs(fishHeadX+rand() % 3 - 1);
	fishTailY=abs(fishHeadY+rand() % 3 - 1);
	if(fishHeadX==fishTailX && fishHeadY==fishTailY){
	fishTailX=fishTailX+1;
	}
	if(fishTailX<8 && fishTailY<8){
		setPixel(dev->bitmap,fishTailX,fishTailY,fishColor);
	}
	}
	setPixel(dev->bitmap,fishHeadX,fishHeadY,fishColor);
	fishPosition[0]=fishHeadX;
	fishPosition[1]=fishHeadY;
	fishPosition[2]=fishTailX;
	fishPosition[3]=fishTailY;
	return fishPosition;
}

int *fishMove(pi_framebuffer_t *dev,int *newPos){
	uint16_t fishColor=getColor(255,211,0);
	uint16_t sea=getColor(16,140,145);
	setPixel(dev->bitmap,newPos[0],newPos[1],sea);
	setPixel(dev->bitmap,newPos[2],newPos[3],sea);
	int newHeadX=newPos[0];
	int newHeadY=newPos[1];
	int newTailX=newPos[2];
	int newTailY=newPos[3];
	int xMovement=newHeadX-newTailX;
	int yMovement=newHeadY-newTailY;
	newHeadX=newHeadX+xMovement;
	newHeadY=newHeadY+yMovement;
	newTailX=newTailX+xMovement;
	newTailY=newTailY+yMovement;
	if(newHeadX>=0 && newHeadX<8 && newHeadY>=0 && newHeadY<8){
		newPos[0]=newHeadX;
		newPos[1]=newHeadY;
		newPos[2]=newTailX;
		newPos[3]=newTailY;
		setPixel(dev->bitmap,newHeadX,newHeadY,fishColor);
		setPixel(dev->bitmap,newTailX,newTailY,fishColor);
	}
	else{
		newPos[0]=8;
	}
	return newPos;
}

int *sharkSpawn(pi_framebuffer_t *dev, int* sharkVector){
	uint16_t sharkColor=getColor(54,57,59);
	int sharkAxis=rand() % 2;
	int sharkHeadX;
	int sharkHeadY;
	int width;
	if(sharkAxis==0){
		sharkHeadX=abs(rand() % 6);
		sharkHeadY=0;
		sharkVector[0]=sharkHeadX;
		sharkVector[1]=sharkHeadY;
		sharkVector[2]=0;
		for(width=0;width<=2;width++){
			setPixel(dev->bitmap,sharkHeadX+width,sharkHeadY,sharkColor);
		}
	}
	else{
		sharkHeadX=0;
		sharkHeadY=abs(rand() % 6);
		sharkVector[0]=sharkHeadX;
		sharkVector[1]=sharkHeadY;
		sharkVector[2]=1;
		for(width=0;width<=2;width++){
			setPixel(dev->bitmap,sharkHeadX,sharkHeadY+width,sharkColor);
		}
	}
	return sharkVector;
}

int *sharkMove(pi_framebuffer_t *dev,int *sharkVector){
	uint16_t sharkColor=getColor(54,57,59);
	uint16_t sea=getColor(16,140,145);
	int sharkHeadX=sharkVector[0];
	int sharkHeadY=sharkVector[1];
	int sharkDirection=sharkVector[2];
	if(sharkDirection==0){
		sharkHeadY=sharkHeadY+1;
	}
	else if(sharkDirection==1){
		sharkHeadX=sharkHeadX+1;
	}
	int width;
	int length;
	int stopCode=8;
	sharkVector[0]=sharkHeadX;
	sharkVector[1]=sharkHeadY;
	sharkVector[2]=sharkDirection;
	if((sharkHeadX<12) && (sharkHeadY<12) && (sharkHeadX>=0) && (sharkHeadY>=0)){
		for(length=0;length<=4;length++){
		for(width=0;width<=2;width++){
			if(sharkDirection==0){
				if((sharkHeadY-length>=0) && (sharkHeadY-length<=7)){
					setPixel(dev->bitmap,sharkHeadX+width,sharkHeadY-length,sharkColor);
					if(length==4 && sharkHeadY-4>=0){
						setPixel(dev->bitmap,sharkHeadX+width,sharkHeadY-4,sea);
					}
				}
			}
			else if(sharkDirection==1){
				if((sharkHeadX-length>=0) && (sharkHeadX-length<=7)){
					setPixel(dev->bitmap,sharkHeadX-length,sharkHeadY+width,sharkColor);
					if(length==4 && sharkHeadX-4>=0){
						setPixel(dev->bitmap,sharkHeadX-4,sharkHeadY+width,sea);
					}
				}
			}
		}
		}
	}
	else{
		sharkVector[2]=stopCode;
	}
	return sharkVector;
}

int *rodMove(pi_framebuffer_t *dev,int *rodPos,int *newPos){
	uint16_t bobber=getColor(255,36,0);
	uint16_t sea=getColor(16,140,145);
	int oldX=rodPos[0];
	int oldY=rodPos[1];
	if((newPos[0]<=7) && (newPos[0]>=0) && (newPos[1]<=7) && (newPos[1]>=0)){
	rodPos[0]=newPos[0];
	rodPos[1]=newPos[1];
	setPixel(dev->bitmap,oldX,oldY,sea);
	setPixel(dev->bitmap,rodPos[0],rodPos[1],bobber);
	}
	return rodPos;
}


void gameOverScreen(pi_framebuffer_t *dev){
	uint16_t face=getColor(144,14,22);
	uint16_t dead=getColor(54,4,12);
	int point;
	clearBitmap(dev->bitmap,0);
	//makes box
	for(point=0;point<=7;point++){
		setPixel(dev->bitmap,point,0,dead);
		setPixel(dev->bitmap,point,7,dead);
		setPixel(dev->bitmap,0,point,dead);
		setPixel(dev->bitmap,7,point,dead);
	}
	//makes crosses for eyes
	for(point=1;point<=3;point++){
		setPixel(dev->bitmap,point,point,face);
		setPixel(dev->bitmap,point,4-point,face);
		setPixel(dev->bitmap,point+3,point,face);
		setPixel(dev->bitmap,point+3,4-point,face);
	}
	//makes mouth
	setPixel(dev->bitmap,2,6,face);
	setPixel(dev->bitmap,3,5,face);
	setPixel(dev->bitmap,4,5,face);
	setPixel(dev->bitmap,5,6,face);
}

void winScreen(pi_framebuffer_t *dev){
	uint16_t green=getColor(57,255,20);
	int point;
	clearBitmap(dev->bitmap,0);
	for(point=1;point<=3;point++){
		setPixel(dev->bitmap,point,point+2,green);
	}
	for(point=3;point<=6;point++){
		setPixel(dev->bitmap,point,8-point,green);
	}
}



void displayScore(pi_framebuffer_t *dev,int score){
	int point1;
	int point2;
	uint16_t scoreColor=getColor(77,77,255);
	clearBitmap(dev->bitmap,0);
	if(score==0){
		for(point1=1;point1<=6;point1++){
			setPixel(dev->bitmap,point1,1,scoreColor);
			setPixel(dev->bitmap,point1,6,scoreColor);
			setPixel(dev->bitmap,1,point1,scoreColor);
			setPixel(dev->bitmap,6,point1,scoreColor);
		}
	}
	else if(score==1){
		for(point1=1;point1<=6;point1++){
			setPixel(dev->bitmap,4,point1,scoreColor);
		}
	}
	else if(score!=4){
		for(point2=1;point2<=5;point2++){
			for(point1=1;point1<=6;point1++){
				setPixel(dev->bitmap,point1,point2,scoreColor);
			}
			point2=point2+1;
		}
		if(score==2){
			setPixel(dev->bitmap,6,2,scoreColor);
			setPixel(dev->bitmap,1,4,scoreColor);
		}
		else if(score==3){
			setPixel(dev->bitmap,6,2,scoreColor);
			setPixel(dev->bitmap,6,4,scoreColor);
		}
		else if(score==5){
			setPixel(dev->bitmap,1,2,scoreColor);
			setPixel(dev->bitmap,6,4,scoreColor);
		}
	}
	else if(score==4){
		for(point1=1;point1<=5;point1++){
			setPixel(dev->bitmap,6,point1,scoreColor);
		}
		for(point1=1;point1<=3;point1++){
			setPixel(dev->bitmap,1,point1,scoreColor);
		}
		for(point1=2;point1<=5;point1++){
			setPixel(dev->bitmap,point1,3,scoreColor);
		}
	}
}




#include <signal.h>
#include "sense.h"
#include <linux/input.h>
#include <stdio.h>
#include <stdlib.h>
int running=1;
int y=4;
int x=3;

void movePos(unsigned int code){
	if(code == KEY_UP){
		if(y>0){
			y=y-1;
		}
	}
	else if(code == KEY_DOWN){
		if(y<7){
			y=y+1;
		}
	}
	else if(code == KEY_LEFT){
		if(x>0){
			x=x-1;
		}
	}
	else if(code == KEY_RIGHT){
		if(x<7){
			x=x+1;
		}
	}
	else if(code == KEY_ENTER){
		x=x;
		y=y;
	}
	else{
		x=x;
		y=y;
	}
}


int *getPos(int* pos){
	pos[0]=x;
	pos[1]=y;
	return pos;
}


void castRod(pi_i2c_t *gyro){
        coordinate_t data;
        data.y=0;
        while(data.y>-.5){
        getAccelData(gyro,&data);
        }
        while(data.y<.5){
        getAccelData(gyro,&data);
        }
}

int reel(pi_i2c_t *gyro,int *fishPos,int *bobPos){
	int success=0;
	coordinate_t data;
	getAccelData(gyro,&data);
	if(data.y<-.5){
		if(fishPos[0]==bobPos[0] && fishPos[1]==bobPos[1]){
			success=1;
		}
		else if(fishPos[2]==bobPos[0] && fishPos[3]==bobPos[1]){
			success=1;
		}
		else{
			success=0;
		}
	}
	else{
		success=0;
	}
	return success;
}



int sharkDetect(int *shark,int *rod){
        int sharkDirection=shark[2];
        int touching=0;
        if(sharkDirection==1){
                //check dimensions
                if((rod[0]>=shark[0]-3) && (rod[0]<=shark[0]) && (rod[1]<=shark[1]+2) && (rod[1]>=shark[1])){
                        touching=1;
                }
        }
        if(sharkDirection==0){
                //check dimensions
                if((rod[0]<=shark[0]+2) && (rod[0]>=shark[0]) && (rod[1]>=shark[1]-3) && (rod[1]<=shark[1])){
                        touching=1;
                }
        }
        return touching;
}


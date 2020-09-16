#include <stdio.h>
#include <stdlib.h>
#include "sense.h"
#include <unistd.h>
#include <time.h>
#include <signal.h>
#include <linux/input.h>

void startScreen(pi_framebuffer_t *);
void castAnimation(pi_framebuffer_t *);
void catchAnimation(pi_framebuffer_t *, int);
void drawSea(pi_framebuffer_t *);
int *fishSpawn(pi_framebuffer_t *,int *);
int *fishMove(pi_framebuffer_t *,int *);
int *sharkSpawn(pi_framebuffer_t *, int *);
int *sharkMove(pi_framebuffer_t *, int *);
int *rodMove(pi_framebuffer_t *, int *, int *);
int sharkDetect(int *,int *);
void gameOverScreen(pi_framebuffer_t *);
void winScreen(pi_framebuffer_t *);
void displayScore(pi_framebuffer_t *,int);
void movePos(unsigned int);
int *getPos(int *);
void castRod(pi_i2c_t *);
int reel(pi_i2c_t *, int *, int *);

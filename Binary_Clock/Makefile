example: example.o framebuffer.o
	cc -o example example.o framebuffer.o

compile: main.c display.c
	cc -c main.c
	cc -c display.c

all: main.o display.o framebuffer.o
	cc -o clock main.o display.o framebuffer.o

clean: clock display.o main.o
	rm clock
	rm display.o
	rm main.o

run: clock clock.sh
	./clock.sh | ./clock

CFLAGS := -g
INCLUDE := -I ~/include
LDFLAGS := -L ~/lib -lsense -lm


all: project.h output.o input.o main.o
	cc -o project $(INCLUDE) output.o input.o main.o $(LDFLAGS)

clean:
	rm -f *.o project inputtest outputtest


inputtest: project.h inputtest.c input.o
	cc -c $(CFLAGS) inputtest.c $(INCLUDE)
	cc -o inputtest $(INCLUDE) inputtest.o input.o $(LDFLAGS)

outputtest: project.h outputtest.c output.o
	cc -c $(CFLAGS) outputtest.c $(INCLUDE)
	cc -o outputtest $(INCLUDE) outputtest.o output.o $(LDFLAGS)

%.o: %.c
	cc -c $(CFLAGS) $< $(INCLUDE)

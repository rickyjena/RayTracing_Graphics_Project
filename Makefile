GCC = gcc
CFLAGS = -Wall
RM = rm -f

all: raycast

raycast: v3math.c v3math.h raycast.c raycast.h
	$(GCC) $(CFLAGS) raycast_main.c -o raycast -lm

clean:
	$(RM) raycast output.ppm

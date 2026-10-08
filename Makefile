#Makefile
CFLAGS = -m32 -Wall -Wextra -g
soc-inventory: main.c
	gcc $(CFLAGS) main.c -o soc-inventory
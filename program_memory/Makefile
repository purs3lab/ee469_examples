all: a.out

main.o:
	gcc -c main.c -o main.o
math.o:
	gcc -c math.c -o math.o

a.out: main.o math.o
	gcc main.o math.o -o a.out
clean:
	rm main.o math.o a.out

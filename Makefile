all: edgerunner

edgerunner:
	gcc -Wall -lcurses -o edgerunner *.c

clean:
	rm -f edgerunner

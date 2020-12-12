build:
	gcc -o main -g main.c -pthread

run:
	./main

clean:
	rm -rf prog

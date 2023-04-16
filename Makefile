build: # rule for building our project	
	gcc -Wall --std=c99 src/*.c -lSDL2 -o renderer

run: # running our project
	./renderer

clean: # clean the executable
	rm renderer
build: # rule for building our project	
	gcc -Wall --std=c99 src/*.c src/dynamic_array/dynamic_array.c -L/usr/lib/x86_64-linux-gnu -lSDL2 -lm -o renderer

run: # running our project
	./renderer

clean: # clean the executable
	rm renderer
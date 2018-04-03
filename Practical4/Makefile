circuits: circuits.o io.o
	gcc -std=c99 -Wall -Wextra -g circuits.o io.o -o circuits

io.o: io.c gates.h
	 gcc -std=c99 -Wall -Wextra -g io.c -c -o io.o

circuits.o: circuits.c gates.h
	 gcc -std=c99 -Wall -Wextra -g circuits.c -c -o circuits.o

clean:
	rm *.o circuits

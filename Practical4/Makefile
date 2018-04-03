circuits: circuits.o io.o linkedlist.o
	gcc -std=c99 -Wall -Wextra -g circuits.o io.o linkedlist.o -o circuits

io.o: io.c gates.h
	 gcc -std=c99 -Wall -Wextra -g io.c -c -o io.o

circuits.o: circuits.c gates.h
	 gcc -std=c99 -Wall -Wextra -g circuits.c -c -o circuits.o

linkedlist.o: linkedlist.c gates.h
	 gcc -std=c99 -Wall -Wextra -g linkedlist.c -c -o linkedlist.o

clean:
	rm *.o circuits

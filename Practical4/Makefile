circuits: circuits.o io.o linkedlist.o arraylist.o
	gcc -std=c99 -Wall -Wextra -g circuits.o io.o linkedlist.o arraylist.o -o circuits -lm

io.o: io.c gates.h
	 gcc -std=c99 -Wall -Wextra -g io.c -c -o io.o

circuits.o: circuits.c gates.h
	 gcc -std=c99 -Wall -Wextra -g circuits.c -c -o circuits.o

linkedlist.o: linkedlist.c gates.h
	 gcc -std=c99 -Wall -Wextra -g linkedlist.c -c -o linkedlist.o

arraylist.o: arraylist.c gates.h
	 gcc -std=c99 -Wall -Wextra -g arraylist.c -c -o arraylist.o

clean:
	rm -f *.o circuits

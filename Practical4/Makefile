circuits: circuits.o subsets.o
	gcc -std=c99 -Wall -Wextra -g circuits.o subsets.o -o circuits

subsets.o: subsets.c gates.h
	 gcc -std=c99 -Wall -Wextra -g subsets.c -c -o subsets.o

circuits.o: circuits.c gates.h
	 gcc -std=c99 -Wall -Wextra -g circuits.c -c -o circuits.o

clean:
	rm *.o circuits

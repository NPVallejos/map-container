all:	main

run-with-valgrind:
	clear
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./main

run:
	clear
	./main

main:	main.o Map.hpp
	g++ -Wall -Wextra -pedantic main.o -ggdb3 -o main

main.o:	main.cpp Map.hpp
	g++ -Wall -Wextra -pedantic -ggdb3 -c main.cpp
	
clean:
	rm -f *.o main

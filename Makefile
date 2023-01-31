all: prog1 pokemon

prog1:	prog1.o
	g++ -o prog1 prog1.cpp

pokemon: pokemon.o
	g++ -o pokemon pokemon.cpp

clean:
	rm -f prog1.o prog1 pokemon.o pokemon

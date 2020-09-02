game: game.o board.o color.o player.o size.o
	g++ game.o board.o color.o player.o size.o -std=c++17 -o game

game.o: board.hpp
	g++ game.cpp -std=c++17 -c -o game.o

board.o: size.hpp
	g++ board.cpp -std=c++17 -c -o board.o

color.o:
	g++ color.cpp -std=c++17 -c -o color.o

player.o: size.hpp color.hpp
	g++ player.cpp -std=c++17 -c -o player.o

size.o:
	g++ size.cpp -std=c++17 -c -o size.o

clean:
	rm *.o
	
mrproper:
	rm game
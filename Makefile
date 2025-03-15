F = -std=c++20 -Wall -Wextra -Wpedantic -Wfatal-errors
Z = ICS46_hw9.zip
P = graph
Q = ladder

def: $P $Q

graph: src/dijkstras.cpp src/dijkstras_main.cpp src/dijkstras.h
	g++ $F src/dijkstras.cpp src/dijkstras_main.cpp -o graph

ladder: src/ladder.cpp src/ladder_main.cpp src/ladder.h
	g++ $F src/ladder.cpp src/ladder_main.cpp -o ladder

clean:
	/bin/rm -f $P $Q $Z

zip: clean
	zip $Z Makefile src/dijkstras_main.cpp src/dijkstras.h src/dijkstras.cpp src/ladder.cpp src/ladder.h src/ladder_main.cpp small.txt medium.txt large.txt largest.txt words.txt

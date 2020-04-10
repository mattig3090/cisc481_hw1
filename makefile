CC=g++

run: assignment.cpp graph.cpp
	$(CC) -g assignment.cpp graph.cpp -o run -std=c++0x

clean:
	rm -rf run
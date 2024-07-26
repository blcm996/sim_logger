CXX = g++

CFLAGS = -Wall -g -c

logger.o: logger.cpp
	$(CXX) $(CFLAGS) logger.cpp -o logger.o

main.o: main.cpp
	$(CXX) $(CFLAGS) main.cpp -o main.o

Log: logger.o main.o
	$(CXX) logger.o main.o -o Log

.PHONY: clean
clean:
	rm -rf Log *.o

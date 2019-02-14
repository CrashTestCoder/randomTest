CC = gcc
CPP = g++
CFLAGS = -I . -std=c++17 -fconcepts -O3
OBJ =  main.o
DEPS = 

%.o: %.c $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

%.o: %.cpp $(DEPS)
	$(CPP) -c -o $@ $< $(CFLAGS)

randomTest: $(OBJ)
	$(CPP) -o $@ $^ $(CFLAGS)

.PHONY: clean

clean:
	rm -f  main.o

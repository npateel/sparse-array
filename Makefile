
CC = g++

CFLAGS = -std=c++2a -g -Wall -I/home/npateel/include -Iinclude -L/home/npateel/lib

LDFLAGS = -lsdsl -ldivsufsort -ldivsufsort64

TARGET = bin/rank

all: $(TARGET)

$(TARGET): build/rank.o build/main.o
	$(CC) $(CFLAGS) -o rank build/rank.o build/main.o $(LDFLAGS)	
build/%.o: src/%.cpp
	$(CC) $(CFLAGS) $< -c -o $@ $(LDFLAGS)



clean:
	rm -rf *.o $(TARGET)
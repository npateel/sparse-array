
CC = g++

CFLAGS = -std=c++2a -g -Wall -Wno-deprecated-declarations  -I/home/npateel/include -Iinclude -L/home/npateel/lib

LDFLAGS = -lsdsl -ldivsufsort -ldivsufsort64

TARGET = bin/rank

all: $(TARGET)

$(TARGET): build/rank.o build/main.o build/select.o build/sparse-array.o
	$(CC) $(CFLAGS) -o rank build/rank.o build/main.o build/select.o build/sparse-array.o $(LDFLAGS)	
build/%.o: src/%.cpp
	$(CC) $(CFLAGS) $< -c -o $@ $(LDFLAGS)



clean:
	rm -rf build/*.o $(TARGET)

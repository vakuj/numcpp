CC=g++
STD=-std=c++11
CFLAGS=-g -Wall -Wextra -Wconversion -pedantic -D DEBUG
SRC=main.cpp logger.cpp
HDRS=NumCpp.h 
OBJ=main.o 
BIN=main

all:$(BIN)

$(BIN):$(OBJ)
	$(CC) $(STD) $(CFLAGS) $(OBJ) -o $(BIN) 

%.o:%.cpp %.h
	$(CC) -c $(STD) $(CFLAGS) $< -o $@ 

%.o:%.cpp
	$(CC) -c $(STD) $(CFLAGS) $< -o $@ 


clean:
	rm main *.o


CC = g++
CFLAGS = -g -Wall

OBJECTS = chess.o

chess: $(OBJECTS)
	$(CC) $(CFLAGS) -o chess $(OBJECTS)

chess.o: chess.cpp chess.h constants.h
	$(CC) $(CFLAGS) -c chess.cpp

clean:
	rm chess $(OBJECTS)

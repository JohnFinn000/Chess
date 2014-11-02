

CC = g++
CFLAGS = -g -Wall

OBJECTS = chess.o

chess: $(OBJECTS)
	$(CC) $(CFLAGS) -o chess $(OBJECTS)

chess.o: chess.cpp chess.h constants.h
	$(CC) $(CFLAGS) -c chess.cpp

constants.h: constant_generator.cpp
	gcc ${CFLAGS} -c constant_generator.cpp -o constant_generator

clean:
	rm chess $(OBJECTS)

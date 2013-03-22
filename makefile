

CC = g++
CFLAGS = -g -Wall

chess: chess.o
	$(CC) $(CFLAGS) -o chess chess.o

chess.o: chess.cpp chess.h constants.h
	$(CC) $(CFLAGS) -c chess.cpp

clean:
	rm *.o chess

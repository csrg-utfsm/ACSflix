CC=gcc
LFLAGS=-L/usr/local/lib -lzmq
CFLAGS=-Wall

all: sender worker

sender:
	$(CC) $(CFLAGS) -o sender sender.c $(LFLAGS) -pthread

worker:
	$(CC) $(CFLAGS) -o worker worker.c $(LFLAGS)

clean:
	rm -f sender worker *.o
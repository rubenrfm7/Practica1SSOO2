CC = gcc
CFLAGS = -Wall -Wextra -g

SRCS = manager.c pa.c pb.c pc.c pd.c demon.c

all: manager pa pb pc pd demon

manager: manager.c
	$(CC) $(CFLAGS) -o $@ $^

pa: pa.c
	$(CC) $(CFLAGS) -o $@ $^

pb: pb.c
	$(CC) $(CFLAGS) -o $@ $^

pc: pc.c
	$(CC) $(CFLAGS) -o $@ $^

pd: pd.c
	$(CC) $(CFLAGS) -o $@ $^

demon: demon.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f manager pa pb pc pd demon

CC = gcc
OBJECTS = src/kryptonite.c
LIBS = -lssl -lcrypto
CFLAGS = -Wall -Wextra -O2
NAME = kryptonite

kryptonite: $(OBJECTS)
	$(CC) $(CFLAGS) -o $(NAME) $(OBJECTS) $(LIBS)

clean:
	rm $(NAME)

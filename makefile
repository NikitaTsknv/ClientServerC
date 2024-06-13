all: client server

client:
	gcc client.c function.c -W -Wall -Werror -o client

server:
	gcc server.c function.c -W -Wall -Werror -o server -lm

clean:
	rm -rf server client

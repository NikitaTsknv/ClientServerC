#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>

#include "function.h"

#define MATRIX_ROW 6
#define MATRIX_COLUMN 6
#define MATRIX_SIZE (MATRIX_ROW * MATRIX_COLUMN)

int main() {

    int fd = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(34543);
    Inet_pton(AF_INET, "127.0.0.1", &adr.sin_addr);
    Connect(fd, (struct sockaddr *) &adr, sizeof adr);

while (1) {

    double matrix[MATRIX_ROW][MATRIX_COLUMN];
    srand(time(0));
    for (int i = 0; i < MATRIX_ROW; i++) {
	for (int j = 0; j < MATRIX_COLUMN; j++) {
	    matrix[i][j] = (double)rand()/RAND_MAX*(10.0 - 0.01) + 0.01;
	}
    }
    write(fd, matrix, sizeof(double) * MATRIX_SIZE);

    sleep(2);

    }

    close(fd);

    return 0;
}

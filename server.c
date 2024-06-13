#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#include "function.h"

#define MATRIX_ROW 6
#define MATRIX_COLUMN 6
#define MATRIX_SIZE (MATRIX_ROW * MATRIX_COLUMN)
#define BUFFER_AVG_SIZE 5

int main() {

    int server = Socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in adr = {0};
    adr.sin_family = AF_INET;
    adr.sin_port = htons(34543);
    Bind(server, (struct sockaddr *) &adr, sizeof adr);
    Listen(server, 5);
    socklen_t adrlen = sizeof adr;
    int fd = Accept(server, (struct sockaddr *) &adr, &adrlen);
    ssize_t nread;

    double matrix[MATRIX_ROW][MATRIX_COLUMN];
    double arr_avg_det[BUFFER_AVG_SIZE];
    int counter_first_five = 0, index_ring_buffer = 0;
    double det = 0.0, avg_det = 0.0, del_det = 0.0;

while (1) {

    nread = read(fd, matrix, sizeof(double)*MATRIX_SIZE);

    /*for (int i = 0; i < MATRIX_ROW; i++) {
        for (int j = 0; j < MATRIX_COLUMN; j++) {
	    printf("matrix[%d][%d] = %f\n", i, j, matrix[i][j]);
	}
    }*/

    if (nread == -1) {
        perror("Read failed.\n");
        exit(EXIT_FAILURE);
    }
    if (nread == 0) {
        printf("END OF FILE occured.\n");
    }

    det = GaussDet(matrix, MATRIX_ROW);

    printf("\nDet. = %f\n", det);

    if (counter_first_five < BUFFER_AVG_SIZE - 1) {
	arr_avg_det[index_ring_buffer] = det;

	counter_first_five++;
	index_ring_buffer++;

	printf("N/A\n");
    }
    else if (counter_first_five == BUFFER_AVG_SIZE - 1) {
	del_det = arr_avg_det[0];
	arr_avg_det[index_ring_buffer] = det;

	counter_first_five++;
        index_ring_buffer++;

	avg_det = Average(arr_avg_det, BUFFER_AVG_SIZE);

	printf("Avg. det. = %f\n", avg_det);
	printf("Del. det. = %f\n", del_det);
    }
    else {

	if (index_ring_buffer == BUFFER_AVG_SIZE)
	{
	    index_ring_buffer = 0;
	}
	arr_avg_det[index_ring_buffer] = det;

	index_ring_buffer++;

	avg_det = Average(arr_avg_det, BUFFER_AVG_SIZE);

	if (index_ring_buffer == BUFFER_AVG_SIZE) {
            del_det = arr_avg_det[0];
        }
        else {
            del_det = arr_avg_det[index_ring_buffer];
        }

        printf("Avg. det. = %f\n", avg_det);
        printf("Del. det. = %f\n", del_det);

    }

    }

    sleep(15);
    close(fd);
    close(server);
    return 0;
}

#include "function.h"
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <math.h>

int Socket(int domain, int type, int protocol) {
    int res = socket(domain, type, protocol);
    if (res == -1) {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int res = bind(sockfd, addr, addrlen);
    if (res == -1) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
}

void Listen(int sockfd, int backlog) {
    int res = listen(sockfd, backlog);
    if (res == -1) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }
}

int Accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen) {
    int res = accept(sockfd, addr, addrlen);
    if (res == -1) {
        perror("accept failed");
        exit(EXIT_FAILURE);
    }
    return res;
}

void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen) {
    int res = connect(sockfd, addr, addrlen);
    if (res == -1) {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }
}

void Inet_pton(int af, const char *src, void *dst) {
    int res = inet_pton(af, src, dst);
    if (res == 0) {
        printf("inet_pton failed: src does not contain a character"
            " string representing a valid network address in the specified"
            " address family\n");
        exit(EXIT_FAILURE);
    }
    if (res == -1) {
        perror("inet_pton failed");
        exit(EXIT_FAILURE);
    }
}

double GaussDet(double m[][6], int n)
{
    double det = 1;
    for(int i = 0; i < n; ++i)
    {
        double mx = fabs(m[i][i]);
        int idx = i;
        for(int j = i+1; j < n; ++j)
            if (mx < fabs(m[i][j])) mx = fabs(m[i][idx = j]);
        if (idx != i)
        {
            for(int j = i; j < n; ++j)
            {
                double t = m[j][i];
                m[j][i] = m[j][idx];
                m[j][idx] = t;
            }
            det = -det;
        }
        for(int k = i+1; k < n; ++k)
        {
            double t = m[k][i]/m[i][i];

            for(int j = i; j < n; ++j)
                m[k][j] -= m[i][j]*t;
        }
    }
    for(int i = 0; i < n; ++i) det *= m[i][i];
    return det;
}

double Average(double arr[], int size)
{
    double sum = 0.0;
    for (int i = 0; i < size; i++) {
	sum += arr[i];
    }
    return sum / size;
}

#include <arpa/inet.h>
#include <fcntl.h>
#include <iostream>
#include <netinet/in.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fstream>

#define MAX 1024
#define PORT 8080
int main(int argv, char *argc[])
{
    int sockfd;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    const char *server_ip = "127.0.0.1";
    char buf[MAX];
    struct sockaddr_in ser_addr;
    bzero(&ser_addr, sizeof(ser_addr));
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, server_ip, &ser_addr.sin_addr);

    if (NULL == argc[1]) {
        std::cout << "pls enter file name!" << std::endl;
        exit(1);
    }
    connect(sockfd, (struct sockaddr *)&ser_addr, sizeof(ser_addr));

    send(sockfd, argc[1], MAX, 0);
    std::ofstream f_out("out.txt");

    recv(sockfd, buf, MAX, 0);
    f_out.write(buf, strlen(buf));

    close(sockfd);
    f_out.close();
    return 0;
}

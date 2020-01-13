#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <string.h>
#include <fstream>

#define MAX 1024
#define  PORT 8080

int main()
{
    int serfd = socket(AF_INET, SOCK_STREAM, 0);
    int conn;
    char buf[MAX];
    char root[10] = "./";
    struct sockaddr_in ser_addr;
    struct sockaddr_in cli_addr;
    socklen_t len = sizeof (cli_addr);
    ser_addr.sin_family = AF_INET;
    ser_addr.sin_port = htons(PORT);
    ser_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    if(bind(serfd, (struct sockaddr *) &ser_addr, sizeof (ser_addr)) == -1) {
        std::cerr << "bind";
        exit(1);
    }

    if(listen(serfd, 10) == -1) {
        std::cerr << "listen";
        exit(1);
    }

    conn = accept(serfd, (struct sockaddr *) &cli_addr, &len);

    if(conn < 0) {
        std::cerr << "connect";
        exit(1);
    }

    recv(conn, buf, MAX, 0);
    strcat(root, buf);
    memset(buf, 0, MAX);
    std::ifstream f_in(root);

    if(!f_in) {
        std::cerr << "failed to open file!";
        exit(1);
    }

    f_in.seekg(0, f_in.end);
    int length = f_in.tellg();
    f_in.seekg(0, f_in.beg);

    f_in.read(buf, length);
    send(conn, buf, length, 0);

    f_in.close();
    close(conn);
    close(serfd);

    return 0;
}

#include<arpa/inet.h>
#include<cstring>
#include<unistd.h>
#include<iostream>

int main() {
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    struct sockaddr_in ser;
    bzero(&ser, sizeof(ser));
    ser.sin_family = AF_INET;
    ser.sin_addr.s_addr = inet_addr("127.0.0.1");
    ser.sin_port = htons(10000);
    bind(sockfd, (sockaddr*)&ser, sizeof(ser));
    listen(sockfd, 100);
    struct sockaddr_in cli;
    socklen_t len = sizeof(cli);
    bzero(&cli,sizeof(cli));
    int clifd = accept(sockfd,(sockaddr*)&cli, &len);

    while(true) {
        char buf[1024];
        bzero(&buf,sizeof(buf));
        ssize_t size = read(clifd, buf, sizeof(buf));
        if (size > 0) {
            std::cout << " cli: " << clifd << " say: " << buf << std::endl;
            bzero(&buf,sizeof(buf));
            std::cin>>buf;
            write(clifd,buf,sizeof(buf));
        } else if (size == 0) {
            std::cout << " cli not connect " << std::endl;
            close(clifd);
        } else if (size == -1) {
            std::cout << " sock error " << std::endl;
            close(clifd);
        }
    }
    close(sockfd);
    return 0;
}
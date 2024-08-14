#include<iostream>
#include<sys/socket.h>
#include<arpa/inet.h>
#include<cstring>
#include<unistd.h>

int main() {
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in cli;
    bzero(&cli, sizeof(cli));
    cli.sin_family = AF_INET;
    cli.sin_addr.s_addr = inet_addr("127.0.0.1");
    cli.sin_port = htons(10000);

    connect(sockfd,(sockaddr*)&cli,sizeof(cli));

    while(true){
        char buf[1024] = "hello";
        // bzero(&buf,sizeof(buf));
        // std::cin >> buf;

        ssize_t size = write(sockfd, buf, sizeof(buf));
        if (size == -1) {
            std::cout << " write error" << std::endl;
        }
        bzero(&buf,sizeof(buf));
        ssize_t read_size = read(sockfd, buf, sizeof(buf));
        if (size > 0) {
            std::cout << " server say: " << buf << std::endl;
        } else if( size == 0) {
            std::cout << " server not connect " << std::endl;
            break;
        } else if (size == -1) {
            std::cout << " socket err "  << std::endl;
            close(sockfd);
            break;
        }
    }
    close(sockfd);

    return 0;
}
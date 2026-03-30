#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
int main() {
    int tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_socket < 0) {
        perror("socket()");
        goto exit;
    }
    printf("Socket creation succeeded\n");
    
    struct sockaddr_in bind_addr;
    memset(&bind_addr, 0, sizeof(bind_addr));
    bind_addr.sin_port = htons(6969);
    bind_addr.sin_family = AF_INET;
    bind_addr.sin_addr.s_addr = INADDR_ANY;
    int rc = bind(tcp_socket, (const struct sockaddr*)&bind_addr, sizeof(bind_addr));
    if (rc < 0) {
        perror("bind()");
        goto exit;
    }
    printf("Bind succeeded\n");

    rc = listen(tcp_socket, SOMAXCONN);
    if (rc < 0) {
        perror("listen()");
        goto exit;
    }
    printf("Listen succeeded\n");

exit:
    close(tcp_socket);
}
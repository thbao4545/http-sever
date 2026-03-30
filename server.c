#include <sys/socket.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <stdint.h>

typedef int8_t i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

int handle_client(int client_socket) {
    u64 n = 0;
    char buf[100];
    printf("\n----\n");
    for (;;) {
        memset(buf, 0, sizeof(buf));

        n = read(client_socket, buf, sizeof(buf) - 1);
        if (n < 0) {
            perror("read(client)");
            return 1;
        }
        if (n == 0) {
            printf("Connection closed\n");
            return 0;
        }
        printf("%s", buf);
    }
    printf("\n----\n");
}

int main() {
    /* declare */
    i8 rc = 0;
    struct sockaddr_in bind_addr;
    i8 tcp_socket = 0;
    i8 re = 0;
    i8 client_socket = 0;
    
    /* initialize */
    tcp_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (tcp_socket < 0) {
        perror("socket()");
        return 1;
    }
    printf("Socket creation succeeded\n");

    /* setsockopt(tcp_socket, ) */
    memset(&bind_addr, 0, sizeof(bind_addr));
    bind_addr.sin_port = htons(6969);
    bind_addr.sin_family = AF_INET;
    bind_addr.sin_addr.s_addr = INADDR_ANY;
    rc = bind(tcp_socket, (const struct sockaddr*)&bind_addr, sizeof(bind_addr));
    if (rc < 0) {
        perror("bind()");
        re = 1;
        goto exit;
    }
    printf("Bind succeeded\n");

    rc = listen(tcp_socket, SOMAXCONN);
    if (rc < 0) {
        perror("listen()");
        re = 1;
        goto exit;
    }
    printf("Listen succeeded\n");

    for(;;) {
        printf("Waiting for connection\n");
        client_socket = accept(tcp_socket, NULL, NULL);   

        printf("Got a connection\n");
        rc = handle_client(client_socket);

    }
exit:
    close(tcp_socket);
    return re;
}
// 서버 코드: server.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int main() {
    int server_fd, new_sock;
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[1024] = {0};

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd == -1) {
        perror("소켓 생성 실패");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
        perror("바인딩 실패");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("리스닝 실패");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    printf("서버 시작...\n");
    new_sock = accept(server_fd, (struct sockaddr *)&client_addr, &client_len);
    if (new_sock < 0) {
        perror("연결 실패");
        close(server_fd);
        exit(EXIT_FAILURE);
    }

    while (1) {
        read(new_sock, buffer, sizeof(buffer));
        printf("클라이언트: %s\n", buffer);
        send(new_sock, "메시지 수신", strlen("메시지 수신"), 0);
    }

    close(server_fd);
    return 0;
}

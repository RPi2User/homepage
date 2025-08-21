#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main() {
    int server_fd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in addr = {0};
    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(33003);

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 1);
    printf("Listening on port 33003...\n");

    const char *http_response =
        "HTTP/1.1 200 OK\r\n"
        "Content-Type: text/html; charset=utf8\r\n"
        "Content-Length: 116\r\n"
        "\r\n"
            "<html><head><style>\r\n"
            "h1{padding-top: 25%;padding-left: 45%;}"
            "</style></head><body><h1> \r\n"
            "mlem :3\r\n</h1></body></html>";
    
    int response_len = strlen(http_response);
    while (1) {
        int client_fd = accept(server_fd, NULL, NULL);
      
        send(client_fd, http_response, response_len, 0);
        close(client_fd);
    }
    close(server_fd);
    return 0;
}

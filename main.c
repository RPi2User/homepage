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
    addr.sin_port = htons(8080);

    bind(server_fd, (struct sockaddr*)&addr, sizeof(addr));
    listen(server_fd, 1);
    printf("Listening on port 8080...\n");

    while (1) {
        int client_fd = accept(server_fd, NULL, NULL);

        // HTTP-Header und Body
        const char *http_response =
            "HTTP/1.1 200 OK\r\n"
            "Content-Type: text/html; charset=utf8\r\n"
            "Content-Length: 160\r\n"
            "\r\n"
            "<html><head></head><body><h1> \r\n"
			"mlem :3 \r\n"
			"</h1></body></html>";

        send(client_fd, http_response, strlen(http_response), 0);
        close(client_fd);
    }
    close(server_fd);
    return 0;
}

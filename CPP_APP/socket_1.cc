#include <iostream>
#include <sys/socket.h>
#include <sys/types.h>
#include <cstring>
#include <cstdlib>
#include <cstdio>
#include <netinet/in.h>
#include <unistd.h>
#define PORT 9504
using namespace std;

int main () {
	int opt = 1, setopt, bindresult, listening, new_socket;
	struct sockaddr_in saddress, cliaddress;
	socklen_t clilen = sizeof(cliaddress);
	char hello[] = "Hello World";
	int socket_fh = socket(AF_INET, SOCK_STREAM, 0);
	if (socket_fh < 0) {
		perror("socket failed");
		exit(EXIT_FAILURE);
	}
	setopt = setsockopt(socket_fh, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
	if (setopt < 0) {
		perror("setting options failed");
		exit(EXIT_FAILURE);
	}
	memset(&saddress, '\0', sizeof(struct sockaddr_in));
	saddress.sin_family = AF_INET;
	saddress.sin_addr.s_addr = INADDR_ANY;
	saddress.sin_port = htons(PORT);
	bindresult = bind(socket_fh, (struct sockaddr*)&saddress, sizeof(saddress));
	if (bindresult < 0) {
		perror("binding failure");
		exit(EXIT_FAILURE);
	}
	listening = listen(socket_fh, 5);
	if (listening < 0) {
		perror("server does not listen");
		exit(EXIT_FAILURE);
	}
	while(true) {
		new_socket = accept(socket_fh, (struct sockaddr*)&cliaddress, &clilen);
		if (new_socket > 0) {
			char reply[] = "HTTP/1.1 200 OK\r\n"
			"Content-Type: text/html\r\n"
			"Content-Length: 20\r\n"
			"Connection: keep-alive\r\n"
			"Accept-Ranges: bytes\r\n"
			"Connection: close\r\n"
			"\r\n"
			"<h1>Hello World</h1>";
			send(new_socket, reply, strlen(reply), 0);
			close(new_socket);
		} else {
			shutdown(socket_fh, SHUT_RDWR);	
		}
	}
	return 0;
}

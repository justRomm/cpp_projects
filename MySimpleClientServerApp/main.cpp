// g++ (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0

#include <iostream>
#include <sys/stat.h>
#include <sys/socket.h>
#include <unistd.h> 
#include <netdb.h>
#include <string.h>
#include <fstream>

#define PORT 8080


void server() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address = {0};
    int addrlen = sizeof(address);
    const int bufferSize = 1024;
    char buffer[bufferSize] = { 0 };

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cout << "Socket failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = PORT;

    if (bind(server_fd, (struct sockaddr*)&address, sizeof(address)) < 0) {
        std::cout << "Bind failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    if (listen(server_fd, 1) < 0) {
        std::cout << "Listen failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    std::cout << "Waiting for a client..." << std::endl;
    if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
        std::cout << "Acception failed" << std::endl;
        exit(EXIT_FAILURE);
    }

    valread = read(new_socket, buffer, bufferSize);

    std::ofstream fileHandle(buffer);

    while(valread = read(new_socket, buffer, bufferSize)){
        fileHandle.write(buffer, valread);
    }

    fileHandle.close();
    close(server_fd);
    close(new_socket);
}

void client(const char* filename) {
    int client_fd, read_len;
    struct sockaddr_in address;

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cout << "Socket failed";
        exit(EXIT_FAILURE);
    }

    int addrlen = sizeof(address);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = PORT;

    if (connect(client_fd, (struct sockaddr*)&address, addrlen) < 0) {
        std::cout << "Connection failed" << std::endl;
        exit(EXIT_FAILURE);
    }
    send(client_fd, filename, strlen(filename), 0);

    std::ifstream fileHandle(filename);
    std::string line;
    if (fileHandle) {
        while (getline(fileHandle, line)) {
            line += "\n";
            send(client_fd, line.c_str(), strlen(line.c_str()), 0);\
        }
    }
    else {
        printf("Cannot read file");
        exit(EXIT_FAILURE);
    }
    fileHandle.close();
    close(client_fd);
}

int main(int argc, char** argv) {
    if (argc == 2) {
        client(argv[1]);
    }
    else if (argc == 1) {
        server();
    }
    else {
        std::cout << "usage: \n" << argv[0] << " for server;\n" << argv[0] << " filename for clients\n";
    }
	return 0;
}
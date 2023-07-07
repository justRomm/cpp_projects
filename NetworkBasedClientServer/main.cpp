#include <iostream>
#include <sys/stat.h>
#include <netdb.h>
#include <string.h>
#include <fstream>
#include <signal.h>
#include "SocketGuard.hpp"
#define PORT 8080


void server() {
    int server_fd, new_socket, valread;
    struct sockaddr_in address = {0};
    int addrlen = sizeof(address);
    const int bufferSize = 1024;
    char buffer[bufferSize] = { 0 };
    pid_t childpid;

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = PORT;

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cout << "Socket failed\n";
        exit(EXIT_FAILURE);
    }

    SocketGuard serverGuard(&server_fd); // Guarding socket for case, when exception is throwed 

    if (bind(server_fd, (struct sockaddr*)&address, addrlen) < 0) {
        std::cout << "Bind failed\n";
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 1) < 0) {
        std::cout << "Listen failed\n";
        exit(EXIT_FAILURE);
    }

    std::cout << "Server is online now\n";

    while (1) {
 
        // Accept clients 
        if ((new_socket = accept(server_fd, (struct sockaddr*)&address, (socklen_t*)&addrlen)) < 0) {
            std::cout << "Acception failed\n";
            exit(EXIT_FAILURE);
        }
        SocketGuard clientGuard(&new_socket); // Guarding socket for case, when exception is throwed
        // Creates a child process
        if ((childpid = fork()) == 0) {            
            // Reads client's input 
            while(1) {

                valread = read(new_socket, buffer, bufferSize);
                if (valread == -1) {
                    // Terminates child process if user is not active
                    kill(childpid, SIGKILL);
                }
                else if(buffer == std::string("hello")) {
                    // Answering to user
                    std::cout << server_fd << '\n';
                    send(new_socket, "world", strlen("world"), 0);
                }
                else {
                    // Answering to user
                    send(new_socket, buffer, strlen(buffer), 0);
                    memset(buffer, 0, bufferSize);
                }   
            }
        }
    }
}

void client() {
    int client_fd, read_len;
    struct sockaddr_in address;
    int valread;
    const int bufferSize = 1024;
    char buffer[bufferSize] = { 0 };

    int addrlen = sizeof(address);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = PORT;

    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        std::cout << "Socket failed\n";
        exit(EXIT_FAILURE);
    }
    
    if (connect(client_fd, (struct sockaddr*)&address, addrlen) < 0) {
        std::cout << "Connection failed\n";
        exit(EXIT_FAILURE);
    }
    // Reading user's input
    while(1) {
        std::cout << ">> ";
        std::string inp;
        std::getline(std::cin, inp);
        if (inp == "disconnect") {
            // Closing a client file descriptor
            shutdown(client_fd, SHUT_RDWR);
            close(client_fd);
            return;
        }
        else {
            // Forwarding user's input to server
            send(client_fd, inp.c_str(), strlen(inp.c_str()), 0);
            valread = read(client_fd, buffer, bufferSize);
            std::cout << buffer << "\n";
            memset(buffer, 0, bufferSize);
        }
    }
}

int main(int argc, char** argv) {
    // If I get it right, "std::cout<<"" can throw an exception
    // Because of it, program were wrapped in try-catch and SocketGuard class was added.
    try {
    if (argc == 2) {
        if(argv[1] == std::string("server")) {
            server();
        } 
        else if(argv[1] == std::string("client")) {
            client();
        }
        }
        else if (argc == 1) {
            std::cout << "usage: " << argv[0] << " client/server \n";
        }
    }
    catch(std::exception& ex) {
        std::cout << "Exception caught: "<< ex.what() << "\n";
    }
    catch(...) {
        std::cout << "Unknown exception is caught\n";
    } 
	return 0;
}
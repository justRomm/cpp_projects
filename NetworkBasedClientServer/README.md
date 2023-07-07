# Simple Client-Server Program

### This is a simple client-server program written in C++. The program allows communication between a server and multiple clients using sockets.

## Usage:

To compile and run the program, use the following commands:

    $ g++ -o main main.cpp
    $ ./main mode


Or you can use provided makefile:

    $ make
    $ ./main mode

Replace mode with either server or client to start the program in the corresponding mode.

## Server mode:

In server mode, the program acts as a server, listening for incoming client connections and responding to their requests.

To start the program in server mode, use the following command:

    $ ./main server

The server will start listening for client connections and display the message "Server is online now." It will continue running until terminated manually.

## Client Mode:

In client mode, the program acts as a client and allows communication with the server.

To start the program in client mode, use the following command:

    $ ./main client

Once in client mode, you can enter commands or messages to send to the server. To disconnect from the server, type "disconnect" and press Enter.

## Here is an example of how to use the program:

Start the program in server mode:

    $ ./main server

Start the program in client mode (in a separate terminal or on a different machine):

    $ ./main client

On a client side enter "hello" and send to the server:

    $ >> hello

The server will respond with "world".

On a client side enter a random message and send to the server:

    $ >> something good

The server will respond with a copy of this message ("something good" in this example).

To disconnect from the server, type "disconnect" and press Enter.

    $ >> disconnect

The client will close the connection and exit.
## Notes

    The program uses a fixed port number 8080 for communication. Make sure this port is available and not being used by any other application.
    The program supports multiple clients connecting to the server simultaneously.
    The server and client communicate using TCP/IP sockets.
    The server responds with "world" if the client sends "hello" as a message.
    If "disconnect" sent by user, communication stops.
# UDP Message Transmitter and Receiver

This repository contains a pair of C programs, `sender.c` and `receiver.c`, designed to transmit and receive messages over a network using the UDP protocol. These programs can be used for network communication experiments, testing UDP packet transmission, or implementing a simple messaging protocol between systems.

## Project Overview

- **`sender.c`**: Sends a predefined message ("GOOSE message") to a specified IP address and port at regular intervals.
- **`receiver.c`**: Listens for incoming UDP packets on a specified port, then displays the message content and additional metadata upon receiving each message.

## Code Overview

- **sender.c**: 
- Creates a UDP socket and connects to the receiver at the specified IP and port.
- Sends a predefined message ("GOOSE message") every 3 seconds in an infinite loop.
- If the message fails to send, the program outputs an error message.

- **receiver.c**:
- Binds a UDP socket to port 102, listening for any incoming messages.
- Upon receiving a message, it displays:
    - The content of the message
    - The length of the message
    - Error details if a message cannot be received.

## Configuration

- Sender: Update the IP address in sender.c to the receiver's IP address before compiling.
    - server.sin_addr.s_addr = inet_addr("RECEIVER_IP_ADDRESS");
- Port: Both programs use port 102 by default, which is commonly associated with GOOSE messaging in industrial systems. Modify the port if needed in both sender.c and receiver.c.



## Features

- **Simple UDP Communication**: Provides a basic implementation of UDP sockets for network communication.
- **Constant Transmission**: The `sender` program repeatedly sends messages every 3 seconds.
- **Real-Time Message Reception**: The `receiver` program listens continuously for incoming messages and displays them in the console.

## Requirements

- **Operating System**: Both programs are designed for Linux environments.
- **Libraries**: Standard C libraries (`stdio.h`, `stdlib.h`, `string.h`, `arpa/inet.h`, `sys/socket.h`, `unistd.h`, and `errno.h`).

## Acknowledgements

- **This project was developed to demonstrate a basic UDP-based message transmission and reception protocol in C.**

Compile both programs using `gcc`:
```bash
gcc sender.c -o sender
gcc receiver.c -o receiver

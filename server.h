#ifndef SERVER_H
#define SERVER_H

#include <winsock2.h>
#include <iostream>
#include <thread>
#include "game.h"

#pragma comment(lib, "ws2_32.lib")

class Server {
private:
    SOCKET serverSocket;
    SOCKET clientSocket1;
    SOCKET clientSocket2;
    TicTacToe game;
    bool running;
    
    static const int PORT = 5555;
    static const int BUFFER_SIZE = 256;

public:
    Server();
    ~Server();
    
    bool initialize();
    void start();
    void handleClients();
    void sendBoardToClients();
    void receiveMove(SOCKET client);
    void cleanup();
};

#endif

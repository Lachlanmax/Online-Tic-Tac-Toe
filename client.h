#ifndef CLIENT_H
#define CLIENT_H

#include <winsock2.h>
#include <iostream>
#include <string>
#include "game.h"

#pragma comment(lib, "ws2_32.lib")

class Client {
private:
    SOCKET connectSocket;
    TicTacToe game;
    bool isPlayerX;
    
    static const int BUFFER_SIZE = 256;

public:
    Client();
    ~Client();
    
    bool connect(const std::string& serverIP, int port = 5555);
    void play();
    void sendMove(int position);
    void receiveBoard();
    void cleanup();
};

#endif

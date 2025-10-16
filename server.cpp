#include "server.h"

Server::Server() : serverSocket(INVALID_SOCKET), clientSocket1(INVALID_SOCKET), 
                   clientSocket2(INVALID_SOCKET), running(true) {
}

Server::~Server() {
    cleanup();
}

bool Server::initialize() {
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cout << "WSAStartup failed: " << iResult << std::endl;
        return false;
    }

    serverSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (serverSocket == INVALID_SOCKET) {
        std::cout << "socket failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return false;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr("0.0.0.0");
    serverAddr.sin_port = htons(PORT);

    if (bind(serverSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cout << "bind failed with error: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return false;
    }

    if (listen(serverSocket, 2) == SOCKET_ERROR) {
        std::cout << "listen failed with error: " << WSAGetLastError() << std::endl;
        closesocket(serverSocket);
        WSACleanup();
        return false;
    }

    std::cout << "Server initialized on port " << PORT << std::endl;
    return true;
}

void Server::start() {
    std::cout << "Waiting for 2 players to connect..." << std::endl;

    sockaddr_in clientAddr;
    int clientAddrLen = sizeof(clientAddr);

    // Accept first player (X)
    clientSocket1 = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSocket1 == INVALID_SOCKET) {
        std::cout << "accept failed: " << WSAGetLastError() << std::endl;
        return;
    }
    std::cout << "Player X connected from " << inet_ntoa(clientAddr.sin_addr) << std::endl;

    // Send confirmation to first player
    char msg = 1; // Player X
    send(clientSocket1, &msg, 1, 0);

    // Accept second player (O)
    clientSocket2 = accept(serverSocket, (sockaddr*)&clientAddr, &clientAddrLen);
    if (clientSocket2 == INVALID_SOCKET) {
        std::cout << "accept failed: " << WSAGetLastError() << std::endl;
        return;
    }
    std::cout << "Player O connected from " << inet_ntoa(clientAddr.sin_addr) << std::endl;

    // Send confirmation to second player
    msg = 2; // Player O
    send(clientSocket2, &msg, 1, 0);

    std::cout << "Game started!\n" << std::endl;
    game.printBoard();

    handleClients();
}

void Server::handleClients() {
    char buffer[BUFFER_SIZE];
    int recvResult;

    while (running) {
        // Player X's turn
        if (game.getGameState() == WAITING && game.getIsXTurn()) {
            std::cout << "Waiting for Player X move..." << std::endl;
            recvResult = recv(clientSocket1, buffer, BUFFER_SIZE, 0);
            if (recvResult > 0) {
                int position = buffer[0];
                if (game.makeMove(position, true)) {
                    std::cout << "Player X played position " << position << std::endl;
                    game.printBoard();
                    sendBoardToClients();

                    if (game.getGameState() != WAITING) {
                        running = false;
                        break;
                    }
                }
            }
        }

        // Player O's turn
        if (game.getGameState() == WAITING && !game.getIsXTurn()) {
            std::cout << "Waiting for Player O move..." << std::endl;
            recvResult = recv(clientSocket2, buffer, BUFFER_SIZE, 0);
            if (recvResult > 0) {
                int position = buffer[0];
                if (game.makeMove(position, false)) {
                    std::cout << "Player O played position " << position << std::endl;
                    game.printBoard();
                    sendBoardToClients();

                    if (game.getGameState() != WAITING) {
                        running = false;
                        break;
                    }
                }
            }
        }
    }

    // Send final board state
    sendBoardToClients();

    // Announce winner
    GameState state = game.getGameState();
    if (state == X_WON) {
        std::cout << "\n*** Player X WON! ***\n" << std::endl;
    } else if (state == O_WON) {
        std::cout << "\n*** Player O WON! ***\n" << std::endl;
    } else if (state == DRAW) {
        std::cout << "\n*** DRAW! ***\n" << std::endl;
    }
}

void Server::sendBoardToClients() {
    char buffer[BUFFER_SIZE] = {0};
    game.serializeBoard(buffer, BUFFER_SIZE);
    
    send(clientSocket1, buffer, BUFFER_SIZE, 0);
    send(clientSocket2, buffer, BUFFER_SIZE, 0);
}

void Server::cleanup() {
    if (clientSocket1 != INVALID_SOCKET) {
        closesocket(clientSocket1);
    }
    if (clientSocket2 != INVALID_SOCKET) {
        closesocket(clientSocket2);
    }
    if (serverSocket != INVALID_SOCKET) {
        closesocket(serverSocket);
    }
    WSACleanup();
    std::cout << "Server cleanup complete." << std::endl;
}

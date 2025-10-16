#include "client.h"

Client::Client() : connectSocket(INVALID_SOCKET), isPlayerX(false) {
}

Client::~Client() {
    cleanup();
}

bool Client::connect(const std::string& serverIP, int port) {
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != 0) {
        std::cout << "WSAStartup failed: " << iResult << std::endl;
        return false;
    }

    connectSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (connectSocket == INVALID_SOCKET) {
        std::cout << "socket failed with error: " << WSAGetLastError() << std::endl;
        WSACleanup();
        return false;
    }

    sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = inet_addr(serverIP.c_str());
    serverAddr.sin_port = htons(port);

    if (::connect(connectSocket, (sockaddr*)&serverAddr, sizeof(serverAddr)) == SOCKET_ERROR) {
        std::cout << "Unable to connect to server: " << WSAGetLastError() << std::endl;
        closesocket(connectSocket);
        WSACleanup();
        return false;
    }

    std::cout << "Connected to server at " << serverIP << ":" << port << std::endl;

    // Receive player assignment (X=1, O=2)
    char buffer = 0;
    int recvResult = recv(connectSocket, &buffer, 1, 0);
    if (recvResult > 0) {
        isPlayerX = (buffer == 1);
        std::cout << "You are Player " << (isPlayerX ? "X" : "O") << std::endl;
    }

    return true;
}

void Client::play() {
    char buffer[BUFFER_SIZE];

    std::cout << "\nGame started! Positions are numbered 0-8:\n";
    std::cout << "0 | 1 | 2\n---------\n3 | 4 | 5\n---------\n6 | 7 | 8\n" << std::endl;

    while (true) {
        // Receive board state
        receiveBoard();
        game.printBoard();

        GameState state = game.getGameState();
        if (state == X_WON) {
            std::cout << "*** Player X WON! ***" << std::endl;
            break;
        } else if (state == O_WON) {
            std::cout << "*** Player O WON! ***" << std::endl;
            break;
        } else if (state == DRAW) {
            std::cout << "*** DRAW! ***" << std::endl;
            break;
        }

        // Check if it's this player's turn
        bool isXTurn = game.getIsXTurn();
        bool myTurn = (isPlayerX && isXTurn) || (!isPlayerX && !isXTurn);

        if (myTurn) {
            std::cout << "Your turn! Enter position (0-8): ";
            int position;
            std::cin >> position;

            if (game.isValidMove(position)) {
                sendMove(position);
            } else {
                std::cout << "Invalid move! Try again." << std::endl;
            }
        } else {
            std::cout << "Waiting for opponent's move..." << std::endl;
            Sleep(1000); // Wait before checking again
        }
    }
}

void Client::sendMove(int position) {
    char buffer = static_cast<char>(position);
    send(connectSocket, &buffer, 1, 0);
}

void Client::receiveBoard() {
    char buffer[BUFFER_SIZE] = {0};
    recv(connectSocket, buffer, BUFFER_SIZE, 0);
    game.deserializeBoard(buffer, BUFFER_SIZE);
}

void Client::cleanup() {
    if (connectSocket != INVALID_SOCKET) {
        closesocket(connectSocket);
    }
    WSACleanup();
    std::cout << "Client cleanup complete." << std::endl;
}

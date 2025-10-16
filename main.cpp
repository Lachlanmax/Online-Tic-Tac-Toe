#include <iostream>
#include <string>
#include "server.h"
#include "client.h"

int main() {
    int choice;
    
    std::cout << "=== Online Tic Tac Toe (LAN) ===" << std::endl;
    std::cout << "1. Host Game (Server)" << std::endl;
    std::cout << "2. Join Game (Client)" << std::endl;
    std::cout << "Choose an option (1 or 2): ";
    
    std::cin >> choice;
    std::cin.ignore(); // Clear input buffer
    
    if (choice == 1) {
        // Server mode
        Server server;
        if (server.initialize()) {
            server.start();
        }
    } 
    else if (choice == 2) {
        // Client mode
        std::string serverIP;
        std::cout << "Enter server IP address (e.g., 192.168.1.100 or 127.0.0.1 for local): ";
        std::getline(std::cin, serverIP);
        
        Client client;
        if (client.connect(serverIP)) {
            client.play();
        }
    } 
    else {
        std::cout << "Invalid choice!" << std::endl;
        return 1;
    }
    
    std::cout << "Goodbye!" << std::endl;
    return 0;
}

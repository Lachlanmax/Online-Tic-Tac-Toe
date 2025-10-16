# Online Tic-Tac-Toe (C++ LAN Edition)

A multiplayer Tic Tac Toe game implemented in C++ with TCP/IP networking for LAN play.

## Features

- **Multiplayer over LAN**: Two players can play against each other over a local network
- **Server-Client Architecture**: One player hosts as a server, another connects as a client
- **Real-time State Synchronization**: Board state is updated and synchronized between both players
- **Win/Draw Detection**: Automatic detection of wins, losses, and draws
- **Windows Compatible**: Uses Winsock2 for networking

## Building

### Using Visual Studio

1. **Open the Solution**
   - Open `OnlineTicTacToe.sln` in Visual Studio
   - The project is configured for Visual Studio 2022 with v143 toolset

2. **Build the Project**
   - Press `Ctrl + Shift + B` or go to Build → Build Solution
   - The executable will be created in the `x64\Debug\` or `x64\Release\` folder

3. **Run the Project**
   - Press `Ctrl + F5` to run without debugging
   - Or `F5` to run with debugging

## How to Play

1. **Start the Server (Host)**
   - Run the executable and choose option `1` (Host Game)
   - The server will wait for a client to connect
   - The host becomes Player X

2. **Start the Client (Join)**
   - Run the executable and choose option `2` (Join Game)
   - Enter the server's IP address (e.g., 192.168.1.100 for remote, or 127.0.0.1 for local testing)
   - The client becomes Player O

3. **Playing the Game**
   - Board positions are numbered 0-8:
     ```
     0 | 1 | 2
     ---------
     3 | 4 | 5
     ---------
     6 | 7 | 8
     ```
   - Players alternate turns entering positions (0-8)
   - First to get 3 in a row wins!
   - If all 9 positions are filled with no winner, it's a draw

## Network Details

- **Port**: 5555
- **Protocol**: TCP/IP
- **Supported Networks**: Works on any LAN (local network)
- **IP Address**: Server needs to be accessible at its IP address

## Architecture

- **game.h/game.cpp**: Core Tic Tac Toe game logic, board management, win detection
- **server.h/server.cpp**: Server implementation that handles two client connections and game flow
- **client.h/client.cpp**: Client implementation that connects to server and handles user input
- **main.cpp**: Entry point with menu for choosing server or client mode
- **OnlineTicTacToe.sln**: Visual Studio solution file
- **OnlineTicTacToe.vcxproj**: Visual Studio project file

## Requirements

- Windows OS (uses Winsock2)
- Visual Studio 2022 or later
- C++17 language support
